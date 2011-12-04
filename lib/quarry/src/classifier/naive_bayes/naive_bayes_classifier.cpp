#include "naive_bayes_classifier.h"
#include "data_set/data_set.h"
#include "data_set/dense/dense_data_set.h"
#include <math.h>

Classifier::NaiveBayesClassifier *Classifier::NaiveBayesClassifier::clone(DataSet::DataSet *new_data_set) {
  return new NaiveBayesClassifier(new_data_set, numeric_features, nominal_features);
}


void Classifier::NaiveBayesClassifier::prepare() {
  feature_caches.resize(data_set->categories_size() + 1);
  int feature_count = numeric_features.size();
  DataSet::NumericFeature *feature = NULL;
  
  data_set->count();
  
  for(int i = 1; i <= data_set->categories_size(); i++) {
    feature_caches[i].resize(feature_count);
    
    for(int j = 0; j < numeric_features.size(); j++) {
      feature = numeric_features[j];
      feature_caches[i][j].denom = 2 * feature->category_variance(i);
      feature_caches[i][j].lhs = 1 / sqrt(2 * M_PI * feature->category_variance(i));
    }
  }
}


double Classifier::NaiveBayesClassifier::score(int category, DataSet::Example *example) {
  double probability = 1.0, numerator = 0.0, value = 0.0;
  DataSet::NumericFeature *numeric_feature = NULL;
  DataSet::NominalFeature *nominal_feature = NULL;
  int feature_index = 0;
  
  // score numeric features with a standard distribution PDF
  for(int i = 0; i < numeric_features.size(); i++) {
    numeric_feature = numeric_features[i];
    feature_index = numeric_feature->index;
    value = example->get_value(feature_index);
    
    // (1 / sqrt(2PI * var)) * e^(-((value - mean) ^ 2) / (2 * var))
    if(feature_caches[category][feature_index].denom != 0.0) {
      numerator = -1 * pow(value - numeric_feature->category_mean(category), 2);
      probability *= (feature_caches[category][feature_index].lhs * exp(numerator / feature_caches[category][feature_index].denom));
    }
  }
  
  // score nominal features
  for(int i = 0; i < nominal_features.size(); i++) {
    nominal_feature = nominal_features[i];
    if(nominal_feature->index == data_set->category_index)
      continue;
    value = example->get_value(nominal_feature->index);
    probability *= nominal_feature->category_value_probability(category, (int)value);
  }
  
  return probability;
}
