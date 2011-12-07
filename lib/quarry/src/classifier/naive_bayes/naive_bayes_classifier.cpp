#include "naive_bayes_classifier.h"
#include "data_set/data_set.h"
#include "data_set/dense/dense_data_set.h"
#include "storage/binary.h"
#include <math.h>

Classifier::NaiveBayesClassifier *Classifier::NaiveBayesClassifier::clone(DataSet::DataSet *new_data_set) {
  return new NaiveBayesClassifier(new_data_set);
}


void Classifier::NaiveBayesClassifier::prepare() {
  feature_caches.resize(data_set->categories_size() + 1);
  int features_size = data_set->features_size();
  DataSet::NumericFeature *feature = NULL;
  
  data_set->count();
  category_probabilities = data_set->category_feature()->probabilities;
  
  for(int i = 1; i <= data_set->categories_size(); i++) {
    feature_caches[i].resize(features_size);
    
    for(int j = 0; j < features_size; j++) {
      if(!numeric_features[j])
        continue;
      feature = (DataSet::NumericFeature *) data_set->features[j];
      feature_caches[i][j].denom = 2 * feature->category_variance(i);
      feature_caches[i][j].lhs = 1 / sqrt(2 * M_PI * feature->category_variance(i));
    }
  }
}


double Classifier::NaiveBayesClassifier::score(int category, DataSet::Example *example) {
  DataSet::SparseExample *sparse_example = NULL;
  DataSet::SparseExample::Value *sparse_value = NULL;
  DataSet::DenseExample *dense_example = NULL;
  double dense_value = 0.0, probability = 0.0;
  
  if(typeid(*example) == typeid(DataSet::SparseExample)) {
    sparse_example = (DataSet::SparseExample *) example;
    for(int i = 0; i < example->size; i++) {
      sparse_value = &(sparse_example->values[i]);
      if(numeric_features[sparse_value->index])
        score_numeric_feature(sparse_value->index, sparse_value->value, category, &probability);
      else if(sparse_value->index != data_set->category_index)
        score_nominal_feature(sparse_value->index, sparse_value->value, category, &probability);
    }
    
  } else {
    dense_example = (DataSet::DenseExample *) example;
    for(int i = 0; i < example->size; i++) {
      dense_value = dense_example->get_value(i);
      if(numeric_features[i])
        score_numeric_feature(i, dense_value, category, &probability);
      else if(i != data_set->category_index)
        score_nominal_feature(i, dense_value, category, &probability);
    }
  }
  
  return probability * category_probabilities[category];
}

void Classifier::NaiveBayesClassifier::write_binary(Storage::Binary *file) {
  int category_count = feature_caches.size();
  file->write_int(category_count);
  file->write_vector<double>(&category_probabilities);
  
  for(int i = 1; i <= category_count; i++)
    file->write_vector<NumericFeatureCache>(&feature_caches[i]);
}

void Classifier::NaiveBayesClassifier::read_binary(Storage::Binary *file) {
  int category_count = file->read_int();
  feature_caches.resize(category_count + 1);
  category_probabilities = *(file->read_vector<double>());
  
  for(int i = 1; i <= category_count; i++)
    feature_caches[i] = *(file->read_vector<NumericFeatureCache>());
}
