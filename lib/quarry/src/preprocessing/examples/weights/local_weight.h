#ifndef __local_weight_h__
#define __local_weight_h__
#include "preprocessing/examples/example_preprocessor.h"

namespace Preprocessing {
  namespace Examples {
    
    class LocalWeight : public ExamplePreprocessor {
      void process(DataSet::Example *example) {
        int max_value = 0;
        double value;
        
        for(int i = 0; i < example->size; i++) {
          value = example->get_value(i);
          if(value > max_value)
            max_value = value;
        }
        
        for(int i = 0; i < example->size; i++) {
          value = example->get_value(i);
          example->set_value(i, value / max_value);
        }
      }
    };
    
  }
}

#endif
