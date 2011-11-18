#ifndef __classifier__
#define __classifier__
#include "data_set/data_set.h"
#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace Classifier {
  
  class Score {
  public:
    int     category;
    double  score;
    
    Score(int category, double score) : category(category), score(score) {}
    
    static bool compare (Score a, Score b) {
      return a.score < b.score;
    }
  };
  
  
  class Classifier {
  public:
    DataSet::DataSet *data_set;
    vector<DataSet::NumericFeature *> numeric_features;
    vector<DataSet::NominalFeature *> nominal_features;
    
    Classifier(DataSet::DataSet *data_set) : data_set(data_set) {
      DataSet::Feature *feature = NULL; 

      for(unsigned int i = 0; i < data_set->features.size(); i++) {
        feature = data_set->features[i];
        if(typeid(*feature) == typeid(DataSet::NumericFeature))
          numeric_features.push_back((DataSet::NumericFeature *)feature);
        else
          nominal_features.push_back((DataSet::NominalFeature *)feature);
      }
    }
    
    Classifier(DataSet::DataSet *data_set, vector<DataSet::NumericFeature *> num_features, vector<DataSet::NominalFeature *> nom_features) : data_set(data_set), numeric_features(), nominal_features() {
      // when constructed as a clone of a previous classifier, features in
      // numeric_features and nominal_features are references to features
      // in the previous data set.
      numeric_features.reserve(num_features.size());
      nominal_features.reserve(nom_features.size());
      
      for(int i = 0; i < num_features.size(); i++)
        numeric_features.push_back((DataSet::NumericFeature *)data_set->features[num_features[i]->index]);
      
      for(int i = 0; i < nom_features.size(); i++)
        nominal_features.push_back((DataSet::NominalFeature *)data_set->features[nom_features[i]->index]);
    }
    
    virtual void prepare() {};
    virtual Classifier *clone(DataSet::DataSet *new_data_set) = 0;
    virtual double score(int category, DataSet::Example *example) = 0;
    virtual int classify(DataSet::Example *example);
    virtual vector<Score> *rank(DataSet::Example *example);
    virtual vector<Score> *score_all(DataSet::Example *example);
  };
}

#endif
