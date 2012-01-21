#ifndef __dense_data_set_h__
#define __dense_data_set_h__
#include "dense_example.h"

namespace DataSet {
  class DenseDataSet : public DataSet {
    void perform_count() {
      int example_category_index = 0;
      double value = 0.0;
      
      for(vector<Example *>::iterator example = examples.begin(); example < examples.end(); example++) {
        example_category_index = (int)((*example)->get_value(category_index));
        for(unsigned int i = 0; i < features.size(); i++) {
          value = (*example)->get_value(i);
          features[i]->count_example(value, example_category_index);
        }
      }
    }
    
    void perform_index() {
    }
    
  public:
    DenseDataSet() : DataSet() {}
    DenseDataSet(DataSet *other) : DataSet(other) {}
    
    DenseDataSet *clone_without_examples() {
      return new DenseDataSet(this);
    }
    
    DenseExample *new_example(bool add_to_data_set = true) {
      DenseExample *example = new DenseExample(features.size());
      if(add_to_data_set)
        examples.push_back(example);
      return example;
    }
  };
}

#endif
