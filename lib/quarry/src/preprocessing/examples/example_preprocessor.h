#ifndef __example_preprocessor_h__
#define __example_preprocessor_h__
#include "data_set/example.h"

namespace Preprocessing {
  namespace Examples {
    
    class ExamplePreprocessor {
    public:
      virtual void process(DataSet::Example *example) {}
      void process_data_set(DataSet::DataSet *data_set) {
        for(vector<DataSet::Example *>::iterator example = data_set->examples.begin(); example != data_set->examples.end(); example++)
          process(*example);
      }
    };
    
  }
}

#endif
