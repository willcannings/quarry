#ifndef __sparse_data_set_h__
#define __sparse_data_set_h__
#include "data_set/data_set.h"
#include "sparse_example.h"

namespace DataSet {
  class SparseDataSet : public DataSet {
  public:
    SparseDataSet() : DataSet() {}
    SparseDataSet(DataSet *other) : DataSet(other) {}
    
    SparseDataSet *clone_without_examples() {
      return new SparseDataSet(this);
    }
    
    SparseExample *new_example() {
      SparseExample *example = new SparseExample();
      examples.push_back(example);
      return example;
    }
  };
}

#endif
