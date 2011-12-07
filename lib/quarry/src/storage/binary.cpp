#include "binary.h"
#include <stdexcept>
#include <vector>

// ------------------------------------------
// integer 'magic marks' are used to identify
// binary files, delineate sections of the
// file, and can be used to test endianess
// ------------------------------------------
static const uint32_t file_mark           = 'quar';
static const uint32_t none_mark           = 'none';
static const uint32_t classifier_mark     = 'clas';
static const uint32_t text_pipeline_mark  = 'texp';


// ------------------------------------------
// low level read and write operations
// ------------------------------------------
void Storage::Binary::write_int(int number) {
  file.write((char *)(&number), sizeof(int));
}

int Storage::Binary::read_int() {
  int value = 0;
  file.read((char *)(&value), sizeof(int));
  return value;
}

void Storage::Binary::write_mark(uint32_t mark) {
  file.write((char *)(&mark), sizeof(uint32_t));
}

uint32_t Storage::Binary::read_mark() {
  uint32_t value = 0;
  file.read((char *)(&value), sizeof(uint32_t));
  return value;
}

void Storage::Binary::write_bool(bool value) {
  char file_value = (value ? 1 : 0);
  file.write(&file_value, 1);
}

bool Storage::Binary::read_bool() {
  char value = 0;
  file.read(&value, 1);
  return value != 0;
}

void Storage::Binary::write_string(string str) {
  file.write(str.c_str(), str.length() + 1);
}

string Storage::Binary::read_string() {
  string str;
  std::getline(file, str, '\0');
  return str;
}


// ------------------------------------------
// data set
// ------------------------------------------
DataSet::DataSet *Storage::Binary::read_data_set() {
  DataSet::DataSet *data_set = NULL;
  bool sparse = read_bool();
  
  // determine the type of data set to create
  if(sparse)
    data_set = new DataSet::SparseDataSet();
  else
    data_set = new DataSet::DenseDataSet();
  
  // initialise the data set
  data_set->name = read_string();
  data_set->category_index = read_int();
  data_set->counted = read_bool();
  data_set->indexed = read_bool();
  
  // initialise the data set's features
  DataSet::NominalFeature *nominal_feature;
  DataSet::NumericFeature *numeric_feature;
  int index = 0, count = 0;
  bool nominal = false;
  string name;
  
  // determine the number of features to read; count caches need to know the number of categories up front
  int num_features = read_int();
  int num_categories = read_int();
  
  for(int i = 0; i < num_features; i++) {
    nominal = read_bool();
    index = read_int();
    name = read_string();
    
    if(nominal) {
      nominal_feature = data_set->new_nominal_feature(name);
      nominal_feature->index = index;
      
      // read the nominal category names
      count = read_int();
      for(int i = 0; i < count; i++)
        nominal_feature->add_value(read_string());
      
      // read cached frequencies and probabilities if present
      if(data_set->counted) {
        nominal_feature->frequencies = *read_vector<int>();
        nominal_feature->probabilities = *read_vector<double>();
        nominal_feature->category_frequencies.resize(num_categories + 1);
        nominal_feature->category_probabilities.resize(num_categories + 1);
        
        for(int i = 1; i <= num_categories; i++)
          nominal_feature->category_frequencies[i] = *read_vector<int>();
        
        for(int i = 1; i <= num_categories; i++)
          nominal_feature->category_probabilities[i] = *read_vector<double>();
      }
      
      // TODO: read cached indexes
      if(data_set->indexed) {
      }
      
    } else {
      numeric_feature = data_set->new_numeric_feature(name);
      numeric_feature->index = index;
      
      // cached counts
      if(data_set->counted) {
        file.read((char *)&(numeric_feature->counts), sizeof(DataSet::NumericFeature::Counts));
        numeric_feature->category_counts = (DataSet::NumericFeature::Counts *) malloc(sizeof(DataSet::NumericFeature::Counts) * (num_categories + 1));
        for(int i = 1; i <= num_categories; i++)
          file.read((char *)&(numeric_feature->category_counts[i]), sizeof(DataSet::NumericFeature::Counts));
      }
      
      // TODO: cached indexes
      if(data_set->indexed) {
      }
    }
  }
  
  // read examples if present
  should_write_examples = read_bool();
  if(should_write_examples) {
    int num_examples = read_int();
    
    if(sparse) {
      DataSet::SparseExample *sparse_example;
      
      for(int i = 0; i < num_examples; i++) {
        // number of non-zero values
        count = read_int();
        
        // construct & read the example
        sparse_example = ((DataSet::SparseDataSet *) data_set)->new_example(count);
        file.read((char *)sparse_example->values, count * sizeof(DataSet::SparseExample::Value));
        sparse_example->size = count;
      }
      
    } else {
      // each dense example stores the same number of values
      count = read_int();
      
      // read each example
      DataSet::DenseExample *dense_example;
      for(int i = 0; i < num_examples; i++) {
        dense_example = ((DataSet::DenseDataSet *) data_set)->new_example();
        file.read((char *)dense_example->values, count * sizeof(double));
      }
    }
  }
  
  return data_set;
}

void Storage::Binary::write_data_set(DataSet::DataSet *data_set) {
  bool sparse = (typeid(*data_set) == typeid(DataSet::SparseDataSet));
  int num_categories = data_set->categories_size();
  int num_features = data_set->features_size();
  int num_examples = data_set->examples_size();

  // data set header
  write_bool(sparse);
  write_string(data_set->name);
  write_int(data_set->category_index);
  write_bool(data_set->counted);
  write_bool(data_set->indexed);
  write_int(num_features);
  write_int(num_categories);
  
  // features
  DataSet::NominalFeature *nominal_feature;
  DataSet::NumericFeature *numeric_feature;
  DataSet::Feature *feature;
  uint32_t count = 0;
  bool nominal;
  
  for(int i = 0; i < num_features; i++) {
    feature = data_set->features[i];
    nominal = (typeid(*feature) == typeid(DataSet::NominalFeature));
    write_bool(nominal);
    write_int(feature->index);
    write_string(feature->name);
    
    if(nominal) {
      nominal_feature = (DataSet::NominalFeature *)feature;
      
      // category names
      count = nominal_feature->names.size();
      write_int(count - 1);
      for(int i = 1; i < count; i++)
        write_string(nominal_feature->names.at(i));
      
      // cached counts
      if(data_set->counted) {
        write_vector<int>(&(nominal_feature->frequencies));
        write_vector<double>(&(nominal_feature->probabilities));
        
        for(int i = 1; i <= num_categories; i++)
          write_vector<int>(&(nominal_feature->category_frequencies.at(i)));
        
        for(int i = 1; i <= num_categories; i++)
          write_vector<double>(&(nominal_feature->category_probabilities.at(i)));
      }
      
      // TODO: cached indexes
      if(data_set->indexed) {
      }
      
    } else {
      numeric_feature = (DataSet::NumericFeature *)feature;
      
      // cached counts
      if(data_set->counted) {
        file.write((const char *)&(numeric_feature->counts), sizeof(DataSet::NumericFeature::Counts));
        for(int i = 1; i <= num_categories; i++)
          file.write((const char *)&(numeric_feature->category_counts[i]), sizeof(DataSet::NumericFeature::Counts));
      }
      
      // TODO: cached indexes
      if(data_set->indexed) {
      }
    }
  }
  
  // examples
  write_bool(should_write_examples);
  if(should_write_examples) {
    write_int(num_examples);
    
    if(sparse) {
      DataSet::SparseExample *example;
      for(int i = 0; i < num_examples; i++) {
        example = (DataSet::SparseExample *) data_set->examples[i];
        count = example->size;
        write_int(count);
        file.write((char *)(example->values), count * sizeof(DataSet::SparseExample::Value));
      }
      
    } else {
      // each dense example stores the same number of values
      count = data_set->examples[0]->size;
      write_int(count);
      
      // write each example
      for(int i = 0; i < num_examples; i++)
        file.write((char *)((DataSet::DenseExample *)data_set->examples[i])->values, count * sizeof(double));
    }
  }
}


// ------------------------------------------
// classifiers
// ------------------------------------------
Classifier::Classifier *Storage::Binary::read_classifier(DataSet::DataSet *data_set) {
  uint32_t mark = read_mark();
  if(mark == none_mark)
    return NULL;
  else if(mark != classifier_mark)
    throw runtime_error("Expected classifier section");
  
  Classifier::Classifier *classifier = NULL;
  uint32_t type = read_mark();
  
  switch(type) {
    case Classifier::NaiveBayesClassifier::file_mark:
      classifier = new Classifier::NaiveBayesClassifier(data_set);
      break;
  }
  
  if(classifier)
    classifier->read_binary(this);
  return classifier;
}

void Storage::Binary::write_classifier(Classifier::Classifier *classifier) {
  if(!classifier) {
    write_mark(none_mark);
  } else {
    write_mark(classifier_mark);
    write_mark(classifier->mark());
    classifier->write_binary(this);
  }
}


// ------------------------------------------
// text pipeline
// ------------------------------------------
Preprocessing::Text::TextPipeline *Storage::Binary::read_text_pipeline() {
  uint32_t mark = read_mark();
  if(mark == none_mark)
    return NULL;
  else if(mark != text_pipeline_mark)
    throw runtime_error("Expected text pipeline section");
  
  Preprocessing::Text::TextPipeline *pipeline = new Preprocessing::Text::TextPipeline();
  
  // tokeniser
  switch(read_mark()) {
    case Preprocessing::Text::SimpleTokeniser::file_mark:
      pipeline->tokeniser = new Preprocessing::Text::SimpleTokeniser(pipeline);
      break;
  }
  
  // inplace processors
  int count = read_int();
  for(int i = 0; i < count; i++) {
    switch(read_mark()) {
      case Preprocessing::Text::Downcase::file_mark:
        pipeline->processors.push_back(new Preprocessing::Text::Downcase());
        break;
      case Preprocessing::Text::PorterStemmer::file_mark:
        pipeline->processors.push_back(new Preprocessing::Text::PorterStemmer());
        break;
    }
  }
  
  // token selectors
  count = read_int();
  for(int i = 0; i < count; i++) {
    switch(read_mark()) {
      case Preprocessing::Text::StopWords::file_mark:
        pipeline->selectors.push_back(new Preprocessing::Text::StopWords());
        break;
      case Preprocessing::Text::POSTagSelector::file_mark:
        pipeline->selectors.push_back(new Preprocessing::Text::POSTagSelector());
        break;
    }
  }
  
  // example generator
  switch(read_mark()) {
    case Preprocessing::Text::TokenCounter::file_mark:
      pipeline->generator = new Preprocessing::Text::TokenCounter();
      break;
  }
  
  return pipeline;
}

void Storage::Binary::write_text_pipeline(Preprocessing::Text::TextPipeline *pipeline) {
  if(!pipeline) {
    write_mark(none_mark);
    return;
  } else {
    write_mark(text_pipeline_mark);
  }
  
  // tokeniser
  write_mark(pipeline->tokeniser->mark());
  
  // inplace processors
  int count = pipeline->processors.size();
  write_int(count);
  for(int i = 0; i < count; i++)
    write_mark(pipeline->processors[i]->mark());
  
  // token selectors
  count = pipeline->selectors.size();
  write_int(count);
  for(int i = 0; i < count; i++)
    write_mark(pipeline->selectors[i]->mark());
  
  // example generator
  write_mark(pipeline->generator->mark());
}


// ------------------------------------------
// helpers
// ------------------------------------------
void Storage::Binary::open_for_reading() {
  // open file
  file.open(path.c_str(), fstream::in | fstream::binary);
  
  // ensure file is ok for reading
  if(!file.good())
    throw runtime_error("Error opening binary file for reading");
  
  // quick sanity check
  if(read_mark() != file_mark)
    throw runtime_error("Binary file mark is invalid");
}

void Storage::Binary::open_for_writing() {
  // open/create file
  file.open(path.c_str(), fstream::out | fstream::binary);
  
  // ensure file is ok for writing
  if(!file.good())
    throw runtime_error("Error opening binary file for writing");
  
  // write the file marker so reads can test the file format
  write_mark(file_mark);
}


// ------------------------------------------
// public read & write methods
// ------------------------------------------
DataSet::DataSet *Storage::Binary::read() {
  open_for_reading();
  DataSet::DataSet *data_set = read_data_set();
  file.close();
  return data_set;
}

void Storage::Binary::write(DataSet::DataSet *data_set) {
  open_for_writing();
  write_data_set(data_set);
  file.close();
}

Model::Model *Storage::Binary::read_model() {
  open_for_reading();
  
  // read the 3 model components
  Model::Model *model  = new Model::Model();
  model->data_set      = read_data_set();
  model->classifier    = read_classifier(model->data_set);
  model->text_pipeline = read_text_pipeline();
  
  file.close();
  return model;
}

void Storage::Binary::write_model(Model::Model *model) {
  open_for_writing();
  
  // write the 3 model components
  write_data_set(model->data_set);
  write_classifier(model->classifier);
  write_text_pipeline(model->text_pipeline);
  
  file.close();
}
