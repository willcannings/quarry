#include "multinomial_bayes_classifier.h"
#include "data_set/data_set.h"
#include <math.h>

double Classifier::MultinomialBayesClassifier::score(DataSet::Category *category, DataSet::Example *example) {

}

void Classifier::MultinomialBayesClassifier::prepare() {
  numeric_feature_probabilities.resize(data_set->categories_size() + 1);
  nominal_feature_probabilities.resize(data_set->categories_size() + 1);
  DataSet::NumericFeature *numeric_feature = NULL;
  DataSet::NominalFeature *nominal_feature = NULL;
  int feature_count = data_set->features.size();
  double category_sum = 0.0;
  
  data_set->count();
  
  // determine the category probabilities for each feature
  for(int i = 1; i <= data_set->categories_size(); i++) {
    numeric_feature_probabilities[i].reserve(feature_count);
    nominal_feature_probabilities[i].reserve(feature_count);
    
    // sum the counts of each numeric feature for this category
    category_sum = 0.0
    for(int j = 0; j < numeric_features.size(); j++)
      category_sum += numeric_features[j]->category_sum(i);
    category_sum += numeric_features.size();
    
    // weight each numeric feature only by the number of other numeric features; nominal features are handled separately
    for(int j = 0; j < numeric_features.size(); j++)
      numeric_feature_probabilities[i][j] = (1.0 + numeric_features[j]->category_sum(i)) / (category_sum);
    
    // each value of a nominal feature is treated as if it were another feature in itself
    for(int j = 0; j < nominal_features.size(); j++) {
      nominal_feature = nominal_features[j];
      nominal_feature_probabilities[j].resize(nominal_feature->values.size());
    }
  }
}
