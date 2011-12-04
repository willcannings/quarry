#ifndef __example_preprocessor_h__
#define __example_preprocessor_h__
#include "data_set/example.h"

namespace Preprocessing {
  namespace Examples {
    
    class ExamplePreprocessor {
    public:
      virtual void process(DataSet::Example *example) {}
    };
    
  }
}

#endif
