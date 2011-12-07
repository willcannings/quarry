#ifndef __storage_h__
#define __storage_h__
#include "data_set/data_set.h"
#include "model/model.h"

namespace Storage {
  class Storage {
  public:
    // all storage implementations must be able to read and write data sets
    virtual DataSet::DataSet *read() = 0;
    virtual void write(DataSet::DataSet *data_set) = 0;
    
    // some implementations can read and write trained models
    virtual Model::Model *read_model() { return NULL; }
    virtual void write_model(Model::Model *model) {}
  };
}

#endif
