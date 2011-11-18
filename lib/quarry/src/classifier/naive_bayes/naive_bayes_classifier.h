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
    vector<vector<NumericFeatureCache> > feature_caches;
    
  public:
    NaiveBayesClassifier(DataSet::DataSet *data_set) : Classifier(data_set) {}
    NaiveBayesClassifier(DataSet::DataSet *data_set, vector<DataSet::NumericFeature *> numeric_features, vector<DataSet::NominalFeature *> nominal_features)
      : Classifier(data_set, numeric_features, nominal_features) {}
    NaiveBayesClassifier *clone(DataSet::DataSet *new_data_set);
    
    double score(int category, DataSet::Example *example);
    void prepare();
  };
}

#endif
