#ifndef __data_set_h__
#define __data_set_h__
#include <tr1/unordered_map>
#include <vector>
#include <string>
#include "example.h"
#include "feature.h"
#include "features/numeric_feature.h"
#include "features/nominal_feature.h"
using namespace std;

namespace Classifier { class Classifier; }
class ConfusionMatrix;

namespace DataSet {
  class DataSet {
    virtual void perform_count() {}
    virtual void perform_index() {}
  public:
    DataSet() : category_index(-1), counted(false), indexed(false) {}
    DataSet(DataSet *other) : name(other->name), category_index(other->category_index), counted(false), indexed(false) {
      Feature *feature = NULL;
      for(unsigned int i = 0; i < other->features.size(); i++) {
        feature = other->features[i]->clone();
        feature_names[feature->name] = feature;
        features.push_back(feature);
      }
    }
    
    virtual ~DataSet() {
      for(unsigned int i = 0; i < features.size(); i++)
        delete features[i];
      for(unsigned int i = 0; i < examples.size(); i++)
        delete examples[i];
    }

    virtual DataSet *clone_without_examples() { return NULL; }
    
    tr1::unordered_map<string, Feature *> feature_names;
    vector<Feature *>   features;
    vector<Example *>   examples;
    string              name;
    int                 category_index;
    bool                counted;
    bool                indexed;
    
    NumericFeature  *new_numeric_feature(string name);
    NominalFeature  *new_nominal_feature(string name);
    virtual Example *new_example(bool add_to_data_set = true) { return NULL; }
    
    void count();
    void index();
    
    vector<vector<Example *> > *stratify(int number_of_folds);
    ConfusionMatrix *cross_fold_validation(Classifier::Classifier *classifier, int number_of_folds);
    
    string  get_name()                    { return name; }
    void    set_name(string new_name)     { name = new_name; }
    int     get_category_index()          { return category_index; }
    int     features_size()               { return features.size(); }
    int     examples_size()               { return examples.size(); }
    int     categories_size()             { return ((NominalFeature *)features[category_index])->indexes.size(); }
    NominalFeature *category_feature()    { return (NominalFeature *)features[category_index]; }
    void    set_category_index(int index);
    
    Feature  *get_feature_by_name(string name)  { return feature_names[name]; }
    Feature  *get_feature_by_index(int index)   { return features[index]; }
    Example  *get_example_by_index(int index)   { return examples[index]; }
    
    NumericFeature *get_or_create_numeric_feature_by_name(string name)  {
      NumericFeature *feature = (NumericFeature *)feature_names[name];
      if(feature == NULL)
        feature = new_numeric_feature(name);
      return feature;
    }
    
    NominalFeature *get_or_create_nominal_feature_by_name(string name)  {
      NominalFeature *feature = (NominalFeature *)feature_names[name];
      if(feature == NULL)
        feature = new_nominal_feature(name);
      return feature;
    }
  };
}

#endif
