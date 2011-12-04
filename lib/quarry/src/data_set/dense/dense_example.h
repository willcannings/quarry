#include <stdexcept>
#ifndef __dense_data_set_example_h__
#define __dense_data_set_example_h__
#include "dense_data_set.h"
#include <iostream>

namespace DataSet {
  class DenseExample : public Example {
  public:
    double *values;
    
    DenseExample(int size) : Example(size) {
      values = (double *) calloc(size, sizeof(double));
    }
    
    ~DenseExample() {
      free(values);
    }
    
    double get_value(int index) {
      return values[index];
    }
    
    void set_value(int index, double new_value) {
      values[index] = new_value;
    }
    
    double euclidean_distance(Example *other_example) {
      return 0.0;
    }
    
    double cosine_distance(Example *other_example) {
      return 0.0;
    }
    
    void print() {
      for(int i = 0; i < size; i++)
        cout << values[i];
      cout << endl;
    }
  };
}

#endif
