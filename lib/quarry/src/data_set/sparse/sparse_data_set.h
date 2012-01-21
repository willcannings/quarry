#ifndef __sparse_data_set_h__
#define __sparse_data_set_h__
#include "data_set/data_set.h"
#include "sparse_example.h"

namespace DataSet {
  class SparseDataSet : public DataSet {
    void perform_count() {
      int example_category_index = 0;
      SparseExample::Value *value;
      
      for(vector<Example *>::iterator example = examples.begin(); example < examples.end(); example++) {
        example_category_index = (int)((*example)->get_value(category_index));
        for(int i = 0; i < (*example)->size; i++) {
          value = &(((SparseExample *)(*example))->values[i]);
          features[value->index]->count_example(value->value, example_category_index);
        }
      }
    }
    
    void perform_index() {
    }
    
  public:
    SparseDataSet() : DataSet() {}
    SparseDataSet(DataSet *other) : DataSet(other) {}
    
    SparseDataSet *clone_without_examples() {
      return new SparseDataSet(this);
    }
    
    SparseExample *new_example(int buffer_size = 0, bool add_to_data_set = true) {
      SparseExample *example = new SparseExample(buffer_size);
      if(add_to_data_set)
        examples.push_back(example);
      return example;
    }
  };
}

#endif
