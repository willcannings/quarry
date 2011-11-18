#ifndef __arff_h__
#define __arff_h__
#include "data_set/data_set.h"
#include "data_set/dense/dense_data_set.h"
#include "storage/storage.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

namespace Storage {
  class ARFF : public Storage {
    typedef enum {
      relation,
      attributes,
      data
    } State;
    
  public:
    string  path;
    ARFF(string path) : path(path) {}
    DataSet::DataSet *read();
    void write(DataSet::DataSet *data_set);
  };
}

#endif
