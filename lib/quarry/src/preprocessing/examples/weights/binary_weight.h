#ifndef __binary_weight_h__
#define __binary_weight_h__
#include "preprocessing/examples/example_preprocessor.h"

namespace Preprocessing {
  namespace Examples {
    
    class BinaryWeight : public ExamplePreprocessor {
      void process(DataSet::Example *example) {
        for(int i = 0; i < example->size; i++) {
          if(example->get_value(i) != 0.0)
            example->set_value(i, 1.0);
        }
      }
    };
    
  }
}

#endif
