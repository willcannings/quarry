#ifndef __naive_bayes_classifier_h__
#define __naive_bayes_classifier_h__
#include "classifier/classifier.h"
#include <vector>

namespace Classifier {
  class NaiveBayesClassifier : public Classifier {
    typedef struct {
      double  denom;
      double  lhs;
    } NumericFeatureCache;
    vector<vector<NumericFeatureCache> > feature_caches; // features_caches[category_index][numeric_feature]
    vector<double> category_probabilities;
    
    // (1 / sqrt(2PI * var)) * e^(-((value - mean) ^ 2) / (2 * var))
    void score_numeric_feature(int index, double value, int category, double *probability) {
      DataSet::NumericFeature *numeric_feature = (DataSet::NumericFeature *) data_set->features[index];
      if(feature_caches[category][index].denom != 0.0) {
        double numerator = -1 * pow(value - numeric_feature->category_mean(category), 2);
        if(*probability == 0.0)
          *probability = 1.0;
        *probability = *probability * (feature_caches[category][index].lhs * exp(numerator / feature_caches[category][index].denom));
      }
    }
    
    void score_nominal_feature(int index, double value, int category, double *probability) {
      DataSet::NominalFeature *nominal_feature = (DataSet::NominalFeature *) data_set->features[index];
      *probability = *probability * nominal_feature->category_value_probability(category, (int)value);
    }
    
  public:
    static const uint32_t file_mark = 'naiv';
    NaiveBayesClassifier(DataSet::DataSet *data_set) : Classifier(data_set) {}
    NaiveBayesClassifier *clone(DataSet::DataSet *new_data_set);
    
    double score(int category, DataSet::Example *example);
    void prepare();
    void write_binary(Storage::Binary *file);
    void read_binary(Storage::Binary *file);
    uint32_t mark() { return file_mark; }
    
    void print() {
      cout << "NB:" << endl;
      for(unsigned int i = 0; i < feature_caches.size(); i++) {
        for(unsigned int j = 0; j < feature_caches[i].size(); j++)
          cout << "C" << i << "F" << j << ":" << feature_caches[i][j].denom << ", l:" << feature_caches[i][j].lhs << endl;
      }
    }
  };
}

#endif
