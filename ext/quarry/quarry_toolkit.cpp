#include "rice/Constructor.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Module.hpp"
#include "rice/Array.hpp"
#include "quarry.h"
using namespace Rice;

Object classifier_rank(Object self, Object ex) {
  Classifier::Classifier *classifier = from_ruby<Classifier::Classifier *>(self);
  DataSet::Example *example = from_ruby<DataSet::Example *>(ex);
  Array indexes;
  
  vector<Classifier::Score> *ranked = classifier->rank(example);
  for(unsigned int i = 0; i < ranked->size(); i++)
    indexes.push(ranked->at(i).category);

  delete ranked;
  return indexes;
}

extern "C" {
	
  void Init_quarry_toolkit() {
    Module rb_mQuarry = define_module("Quarry");
    Module rb_mDataSet = define_module_under(rb_mQuarry, "DataSet");
    Module rb_mClassifier = define_module_under(rb_mQuarry, "Classifier");
    
    // storage
    Data_Type<Storage::Storage> rb_cStorage = define_class_under<Storage::Storage>(rb_mQuarry, "ImplStorage");
    
    Data_Type<Storage::ARFF> rb_cARFF = define_class_under<Storage::ARFF, Storage::Storage>(rb_mQuarry, "ImplARFF")
      .define_constructor(Constructor<Storage::ARFF, string>())
      .define_method("read", &Storage::ARFF::read);
    
    
    // data set
    Data_Type<DataSet::Feature> rb_cDataSetFeature = define_class_under<DataSet::Feature>(rb_mDataSet, "ImplFeature")
      .define_method("get_name", &DataSet::Feature::get_name)
      .define_method("set_name", &DataSet::Feature::set_name)
      .define_constructor(Constructor<DataSet::Feature, string, int>());
    
    Data_Type<DataSet::Example> rb_cDataSetExample = define_class_under<DataSet::Example>(rb_mDataSet, "ImplExample")
      .define_method("category_index", &DataSet::Example::category_index)
      .define_method("get_value", &DataSet::Example::get_value)
      .define_method("set_value", &DataSet::Example::set_value)
      .define_constructor(Constructor<DataSet::Example>());
    
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
