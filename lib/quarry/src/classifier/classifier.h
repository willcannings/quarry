#ifndef __classifier__
#define __classifier__
#include "data_set/data_set.h"
#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace Storage {
  class Binary;
}

namespace Classifier {
  
  class Score {
  public:
    int     category;
    double  score;
    
    Score(int category, double score) : category(category), score(score) {}
    static bool compare (Score a, Score b) {
      return b.score < a.score; // descending
    }
  };
  
  
  class Classifier {
  public:
    DataSet::DataSet *data_set;
    vector<bool> numeric_features;
    vector<bool> nominal_features;
    
    Classifier() {}
    Classifier(DataSet::DataSet *data_set) : data_set(data_set), numeric_features(data_set->features_size(), 0), nominal_features(data_set->features_size(), 0) {
      DataSet::Feature *feature = NULL;
      
      for(unsigned int i = 0; i < data_set->features.size(); i++) {
        feature = data_set->features[i];
        if(typeid(*feature) == typeid(DataSet::NumericFeature))
          numeric_features[i] = true;
        else
          nominal_features[i] = true;
      }
    }
    
    virtual void prepare() {};
    virtual Classifier *clone(DataSet::DataSet *new_data_set) = 0;
    virtual double score(int category, DataSet::Example *example) = 0;
    virtual int classify(DataSet::Example *example);
    virtual vector<Score> *rank(DataSet::Example *example);
    virtual vector<Score> *score_all(DataSet::Example *example);
    virtual void write_binary(Storage::Binary *file) {}
    virtual void read_binary(Storage::Binary *file) {}
    virtual uint32_t mark() = 0;
  };
}

#endif
