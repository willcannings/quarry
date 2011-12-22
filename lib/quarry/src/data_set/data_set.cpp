#include <iostream>
#include "data_set.h"
#include "classifier/classifier.h"
#include "metrics/confusion_matrix.h"
#include "dense/dense_data_set.h"
#include "dense/dense_example.h"
#include "sparse/sparse_data_set.h"
#include "sparse/sparse_example.h"

DataSet::NominalFeature *DataSet::DataSet::new_nominal_feature(string name) {
  NominalFeature *feature = new NominalFeature(name, features.size());
  feature_names[name] = feature;
  features.push_back(feature);
  return feature;
}


DataSet::NumericFeature *DataSet::DataSet::new_numeric_feature(string name) {
  NumericFeature *feature = new NumericFeature(name, features.size());
  feature_names[name] = feature;
  features.push_back(feature);
  return feature;
}


void DataSet::DataSet::set_category_index(int index) {
  category_index = index;
  for(vector<Feature *>::iterator feature = features.begin(); feature < features.end(); feature++)
    (*feature)->reset();
  counted = false;
  indexed = false;
}


void DataSet::DataSet::count() {
  if(counted)
    return;
  
  // initialise each feature for counting
  for(vector<Feature *>::iterator feature = features.begin(); feature < features.end(); feature++)
    (*feature)->prepare_for_counting(this);
  
  // implementation optimised count
  perform_count();
  
  // calculate and finalise counts
  for(vector<Feature *>::iterator feature = features.begin(); feature < features.end(); feature++)
    (*feature)->finalise_counting(this);

  counted = true;
}


void DataSet::DataSet::index() {
  if(indexed)
    return;
  
  // initialise each feature for indexing
  for(vector<Feature *>::iterator feature = features.begin(); feature < features.end(); feature++)
    (*feature)->prepare_for_indexing(this);
  
  // index
  for(vector<Example *>::iterator example = examples.begin(); example < examples.end(); example++) {
    for(int i = 0; i < features.size(); i++)
      features[i]->index_example((*example)->get_value(i), *example);
  }
  
  // finalise indexing
  for(vector<Feature *>::iterator feature = features.begin(); feature < features.end(); feature++)
    (*feature)->finalise_indexing(this);
  
  indexed = true;
}


// TODO: this isn't really stratification; categories should be proportionally represented
vector<vector<DataSet::Example *> > *DataSet::DataSet::stratify(int number_of_folds) {
  int examples_per_fold = examples.size() / number_of_folds;
  vector<vector<Example *> > *folds = new vector<vector<Example *> >();
  folds->resize(number_of_folds);
  Example *example;
  
  for(int fold = 0; fold < number_of_folds; fold++) {
    (*folds)[fold].resize(examples_per_fold);
    for(int i = 0; i < examples_per_fold; i++) {
      (*folds)[fold][i] = examples[fold + (i * number_of_folds)];
    }
  }
  
  return folds;
}


ConfusionMatrix *DataSet::DataSet::cross_fold_validation(Classifier::Classifier *classifier, int number_of_folds) {
  vector<vector<Example *> > *folds = stratify(number_of_folds);
  ConfusionMatrix *overall_matrix = new ConfusionMatrix(this);
  Classifier::Classifier *test_classifier = NULL;
  ConfusionMatrix *result = NULL;
  DataSet *test_set = NULL;
  Example *example = NULL;
  int predicted = 0;
  
  int examples_per_fold = examples.size() / number_of_folds;
  int examples_per_test = examples_per_fold * (number_of_folds - 1);
  
  for(int fold = 0; fold < number_of_folds; fold++) {
    cout << "Running fold " << fold << endl;
    test_set = clone_without_examples();
    test_set->examples.reserve(examples_per_test);
    for(int i = 0; i < number_of_folds; i++) {
      if(i != fold)
        test_set->examples.insert(test_set->examples.begin() + (examples_per_fold * (i > fold ? i - 1 : i)), (*folds)[i].begin(), (*folds)[i].end());
    }
    
    test_classifier = classifier->clone(test_set);
    result = new ConfusionMatrix(test_set);
    test_classifier->prepare();
    
    for(int i = 0; i < examples_per_fold; i++) {
      example = (*folds)[fold][i];
      predicted = test_classifier->classify(example);
      result->add(predicted, (int)example->get_value(category_index));
    }
    
    overall_matrix->merge(result);
    delete test_classifier;
    delete test_set;
    delete result;
  }
  
  return overall_matrix;
}
