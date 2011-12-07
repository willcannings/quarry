#ifndef __sparse_data_set_example_h__
#define __sparse_data_set_example_h__
#include "data_set/example.h"
#include <stdlib.h>
#include <string>
using namespace std;

namespace DataSet {
  class SparseDataSet;
  
  class SparseExample : public Example {
  public:
    typedef struct {
      int     index;
      double  value;
    } Value;
    
    Value *values;
    int   buffer_size;
    
    SparseExample(int buffer_size = 0) : Example(0), buffer_size(buffer_size) {
      if(buffer_size > 0)
        values = (Value *) calloc(sizeof(Value), buffer_size);
      else
        values = NULL;
    }
    
    double get_value(int feature_index);    
    double get_value(string feature_name, SparseDataSet *data_set);
    void set_value(int feature_index, double new_value);
    void append_value(int feature_index, double new_value);
    double euclidean_distance(Example *other_example);
    double cosine_distance(Example *other_example);
    void print();
  };
}

#endif
