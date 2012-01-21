#ifndef __example_generator_h__
#define __example_generator_h__
#include "data_set/sparse/sparse_data_set.h"
#include "data_set/sparse/sparse_example.h"

namespace Preprocessing {
  namespace Text {
    
    class ExampleGenerator {
    public:
      ExampleGenerator() {}
      virtual ~ExampleGenerator() {}
      virtual DataSet::SparseExample *generate(DataSet::SparseDataSet *data_set, vector<char *> *tokens, bool create_features) { return NULL; }
      virtual uint32_t mark() = 0;
    };
    
  }
}

#endif
