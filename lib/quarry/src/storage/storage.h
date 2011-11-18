#ifndef __storage_h__
#define __storage_h__
#include "data_set/data_set.h"

namespace Storage {
  class Storage {
  public:
    virtual DataSet::DataSet *read() = 0;
    virtual void write(DataSet::DataSet *data_set) = 0;
  };
}

#endif
