#ifndef __sparse_data_set_example_h__
#define __sparse_data_set_example_h__
#include "data_set/example.h"
#include <stdlib.h>

namespace DataSet {
  class SparseDataSet;
  
  class SparseExample : public Example {
    typedef struct {
      int     index;
      double  value;
    } Value;
    
  public:
    Value *values;
    int   size;
    int   count;
    
    SparseExample(int size = 0) : Example(), size(size), count(0) {
      if(size > 0)
        values = (Value *) calloc(sizeof(Value), size);
    }
    
    double get_value(int feature_index);    
    double get_value(string feature_name, SparseDataSet *data_set);
    void set_value(int feature_index, double new_value);
    void append_value(int feature_index, double new_value);
    double euclidean_distance(Example *other_example);
    double cosine_distance(Example *other_example);
    
    bool sparse() {
      return true;
    }
  };
}

#endif
