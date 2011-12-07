#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Module.hpp"
#include "rice/Array.hpp"
#include "quarry.h"
using namespace Rice;

Object model_rank(Object self, Object ex) {
  Model::Model *model = from_ruby<Model::Model *>(self);
  DataSet::Example *example = from_ruby<DataSet::Example *>(ex);
  Array indexes;
  
  vector<Classifier::Score> *ranks = model->rank(example);
  for(unsigned int i = 0; i < ranks->size(); i++)
    indexes.push(ranks->at(i).category);

  delete ranks;
  return indexes;
}

Object model_rank_text(Object self, Object text) {
  Model::Model *model = from_ruby<Model::Model *>(self);
  string example_text = from_ruby<string>(text);
  Array indexes;
  
  vector<Classifier::Score> *ranks = model->rank_text(example_text);
  for(unsigned int i = 0; i < ranks->size(); i++)
    indexes.push(ranks->at(i).category);

  delete ranks;
  return indexes;
}


extern "C" {
	
  void Init_quarry_toolkit() {
    Module rb_mQuarry = define_module("Quarry");
    Module rb_mDataSet = define_module_under(rb_mQuarry, "DataSet");
    Module rb_mClassifier = define_module_under(rb_mQuarry, "Classifier");
    Module rb_mPreprocessing = define_module_under(rb_mQuarry, "Preprocessing");
    Module rb_mText = define_module_under(rb_mPreprocessing, "Text");
    
    
    // text pipeline
    rb_mText.define_module_function("standard_pipeline", &Preprocessing::Text::StandardPipeline);
    Data_Type<Preprocessing::Text::TextPipeline> rb_cTextPipeline = define_class_under<Preprocessing::Text::TextPipeline>(rb_mQuarry, "ImplTextPipeline")
      .define_constructor(Constructor<Preprocessing::Text::TextPipeline>())
      .define_method("process_text", &Preprocessing::Text::TextPipeline::process_text);
    
    // storage
    Data_Type<Storage::Storage> rb_cStorage = define_class_under<Storage::Storage>(rb_mQuarry, "ImplStorage");
    
    Data_Type<Storage::ARFF> rb_cARFF = define_class_under<Storage::ARFF, Storage::Storage>(rb_mQuarry, "ImplARFF")
      .define_constructor(Constructor<Storage::ARFF, string>())
      .define_method("read", &Storage::ARFF::read);
    
    Data_Type<Storage::Binary> rb_cBinary = define_class_under<Storage::Binary, Storage::Storage>(rb_mQuarry, "ImplBinary")
      .define_constructor(Constructor<Storage::Binary, string>())
      .define_method("read", &Storage::Binary::read)
      .define_method("write", &Storage::Binary::write)
      .define_method("read_model", &Storage::Binary::read_model)
      .define_method("write_model", &Storage::Binary::write_model)
      .define_method("get_write_examples", &Storage::Binary::get_write_examples)
      .define_method("set_write_examples", &Storage::Binary::set_write_examples);      
    
    Data_Type<Storage::Folders> rb_cFolders = define_class_under<Storage::Folders, Storage::Storage>(rb_mQuarry, "ImplFolders")
      .define_constructor(Constructor<Storage::Folders, string, Preprocessing::Text::TextPipeline *>())
      .define_method("read", &Storage::Folders::read);
    
    
    // model
    Data_Type<Model::Model> rb_cModel = define_class_under<Model::Model>(rb_mQuarry, "ImplModel")
      .define_constructor(Constructor<Model::Model>())
      .define_method("train", &Model::Model::train)
      .define_method("train_text", &Model::Model::train_text)
      .define_method("classify", &Model::Model::classify)
      .define_method("classify_text", &Model::Model::classify_text)
      .define_method("set_data_set", &Model::Model::set_data_set)
      .define_method("get_data_set", &Model::Model::get_data_set)
      .define_method("set_classifier", &Model::Model::set_classifier)
      .define_method("get_classifier", &Model::Model::get_classifier)
      .define_method("set_text_pipeline", &Model::Model::set_text_pipeline)
      .define_method("get_text_pipeline", &Model::Model::get_text_pipeline)
      .define_method("rank", &model_rank)
      .define_method("rank_text", &model_rank_text);
      

    
    // data set
    Data_Type<DataSet::Feature> rb_cDataSetFeature = define_class_under<DataSet::Feature>(rb_mDataSet, "ImplFeature")
      .define_method("get_name", &DataSet::Feature::get_name)
      .define_method("set_name", &DataSet::Feature::set_name)
      .define_constructor(Constructor<DataSet::Feature, string, int>());
    
    Data_Type<DataSet::Example> rb_cDataSetExample = define_class_under<DataSet::Example>(rb_mDataSet, "ImplExample")
      .define_method("category_index", &DataSet::Example::category_index)
      .define_method("get_value", &DataSet::Example::get_value)
      .define_method("set_value", &DataSet::Example::set_value)
      .define_constructor(Constructor<DataSet::Example, int>());
    
    Data_Type<DataSet::DataSet> rb_cDataSet = define_class_under<DataSet::DataSet>(rb_mDataSet, "ImplDataSet")
      .define_constructor(Constructor<DataSet::DataSet>())
      .define_method("get_name", &DataSet::DataSet::get_name)
      .define_method("set_name", &DataSet::DataSet::set_name)
      .define_method("features_size", &DataSet::DataSet::features_size)
      .define_method("examples_size", &DataSet::DataSet::examples_size)
      .define_method("get_feature_by_index", &DataSet::DataSet::get_feature_by_index)
      .define_method("get_feature_by_name", &DataSet::DataSet::get_feature_by_name)
      .define_method("get_example_by_index", &DataSet::DataSet::get_example_by_index)
      .define_method("stratify", &DataSet::DataSet::stratify)
      .define_method("cross_fold_validation", &DataSet::DataSet::cross_fold_validation);


    // abstract classifier
    Data_Type<Classifier::Classifier> rb_cClassifierClassifier = define_class_under<Classifier::Classifier>(rb_mClassifier, "ImplClassifier")
      .define_method("prepare", &Classifier::Classifier::prepare)
      .define_method("classify", &Classifier::Classifier::classify);
      
      
    // bayesian classifiers
    Data_Type<Classifier::NaiveBayesClassifier> rb_cClassifierNaiveBayesClassifier = define_class_under<Classifier::NaiveBayesClassifier, Classifier::Classifier>(rb_mClassifier, "ImplNaiveBayesClassifier")
      .define_constructor(Constructor<Classifier::NaiveBayesClassifier, DataSet::DataSet *>());
    
    
    // confusion matrix
    Data_Type<ConfusionMatrix> rb_cConfusionMatrix = define_class_under<ConfusionMatrix>(rb_mQuarry, "ImplConfusionMatrix")
      .define_constructor(Constructor<ConfusionMatrix, DataSet::DataSet *>())
      .define_method("accuracy", &ConfusionMatrix::accuracy)
      .define_method("error", &ConfusionMatrix::error)
      .define_method("print_summary", &ConfusionMatrix::print_summary)
      .define_method("avg_tp", &ConfusionMatrix::avg_tp)
      .define_method("avg_fp", &ConfusionMatrix::avg_fp)
      .define_method("avg_tn", &ConfusionMatrix::avg_tn)
      .define_method("avg_fn", &ConfusionMatrix::avg_fn)
      .define_method("avg_precision", &ConfusionMatrix::avg_precision)
      .define_method("avg_recall", &ConfusionMatrix::avg_recall)
      .define_method("avg_fscore", &ConfusionMatrix::avg_fscore)
      .define_method("add", &ConfusionMatrix::add)
      .define_method("tp", &ConfusionMatrix::tp)
      .define_method("fp", &ConfusionMatrix::tp)
      .define_method("tn", &ConfusionMatrix::tp)
      .define_method("fn", &ConfusionMatrix::tp)
      .define_method("precision", &ConfusionMatrix::tp)
      .define_method("recall", &ConfusionMatrix::tp)
      .define_method("fscore", &ConfusionMatrix::tp);
  }
}
