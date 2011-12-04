#include "quarry.h"
#include <stdexcept>
#include <cstring>

int main() {
  /*Storage::ARFF *reader = new Storage::ARFF("/Users/will/Desktop/classifier/src/categories_100.arff");
  DataSet::DataSet *ds = reader->read();
  Classifier::NaiveBayesClassifier *c = new Classifier::NaiveBayesClassifier(ds);
  ConfusionMatrix *cm = ds->cross_fold_validation(c, 2);
  cm->print_summary();*/
  
  DataSet::SparseDataSet *data_set = new DataSet::SparseDataSet();
  DataSet::NominalFeature *categories = data_set->new_nominal_feature("Category");
  data_set->set_category_index(0);
  
  Preprocessing::Text::TextPipeline *pipeline = Preprocessing::Text::StandardPipeline(data_set);
  
  char *text = "hello world foo bar hello test yes.";
  char *sample = (char *) malloc(strlen(text) + 1);
  strcpy(sample, text);
  
  DataSet::SparseExample *example = pipeline->process_text(sample);
  data_set->category_feature()->print();
  example->print();
  
  return 0;
}
