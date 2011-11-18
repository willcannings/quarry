#ifndef __dense_data_set_h__
#define __dense_data_set_h__
#include "dense_example.h"

namespace DataSet {
  class DenseDataSet : public DataSet {
  public:
    DenseDataSet() : DataSet() {}
    DenseDataSet(DataSet *other) : DataSet(other) {}
    
    DenseDataSet *clone_without_examples() {
      return new DenseDataSet(this);
    }
    
    DenseExample *new_example() {
      DenseExample *example = new DenseExample(features.size());
      examples.push_back(example);
      return example;
    }
  };
}

#endif
