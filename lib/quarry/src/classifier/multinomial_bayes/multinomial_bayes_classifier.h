#ifndef __multinomial_bayes_classifier_h__
#define __multinomial_bayes_classifier_h__
#include "classifier/classifier.h"
#include <vector>

namespace Classifier {
  class MultinomialBayesClassifier : public Classifier {
    vector<vector<double> > numeric_feature_probabilities;
    vector<vector<vector<double> > > nominal_feature_probabilities;
    
  public:
    MultinomialBayesClassifier(DataSet::DataSet *data_set) : Classifier(data_set) {}
    double score(DataSet::Category *category, DataSet::Example *example);
    void prepare();
  };
}

#endif
