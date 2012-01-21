#ifndef __nominal_feature_h__
#define __nominal_feature_h__
#include "data_set/example.h"
#include "data_set/feature.h"
#include <vector>
#include <map>
#include <iostream>

namespace DataSet {
  class DataSet;
  
  class NominalFeature : public Feature {
  public:
    NominalFeature(string name, int index) : Feature(name, index), names(1, "") {}
    NominalFeature(NominalFeature *other) : Feature(other->name, other->index), indexes(other->indexes), names(other->names) {}
    
    ~NominalFeature() {}
    
    NominalFeature *clone() {
      return new NominalFeature(this);
    }
    
    void reset() {
      frequencies.clear();
      probabilities.clear();
      category_frequencies.clear();
      category_probabilities.clear();
      examples_with_value.clear();
    }
    
    void print();
    
    // nominal values are referenced by index in examples
    // (e.g "CategoryA" -> 2; would be stored as 2 in an example)
    map<string, int>  indexes;
    vector<string>    names;
    void add_value(string name) {
      int index = indexes.size() + 1;
      indexes[name] = index;
      names.push_back(name);
    }
    
    int value_index(string name) {
      int index = indexes[name];
      if(index == 0) {
        index = indexes.size();
        indexes[name] = index;
        names.push_back(name);
      }
      return index;
    }
    
    // counts
    void prepare_for_counting(DataSet *data_set);
    void count_example(double value, int category_index);
    void finalise_counting(DataSet *data_set);
    
    // counts for this feature over the entire data set
    vector<int>     frequencies;
    vector<double>  probabilities;
    int    value_frequency(int index)   { return frequencies[index]; }
    double value_probability(int index) { return probabilities[index]; }
    
    // counts for this feature per category
    vector<vector<int> >    category_frequencies;
    vector<vector<double> > category_probabilities;
    int    category_value_frequency(int category, int index)   { return category_frequencies[category][index]; }
    double category_value_probability(int category, int index) { return category_probabilities[category][index]; }
    
    // indexes
    void prepare_for_indexing(DataSet *data_set);
    void index_example(double value, Example *example);
    void finalise_indexing(DataSet *data_set);
    vector<vector<Example *> > examples_with_value;
  };
}

#endif
