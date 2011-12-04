#ifndef __example_generator_h__
#define __example_generator_h__
#include "data_set/sparse/sparse_data_set.h"
#include "data_set/sparse/sparse_example.h"

namespace Preprocessing {
  namespace Text {
    
    class ExampleGenerator {
    public:
      DataSet::SparseDataSet *data_set;
      ExampleGenerator(DataSet::SparseDataSet *data_set) : data_set(data_set) {}
      virtual DataSet::SparseExample *generate(vector<char *> *tokens) { return NULL; }
    };
    
  }
}

#endif
