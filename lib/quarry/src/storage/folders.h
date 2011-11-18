#ifndef __folders_h__
#define __folders_h__
#include "data_set/data_set.h"
#include "storage/storage.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

namespace Storage {
  class Folders : public Storage {
  public:
    string  path;    
    Folders(string path) : path(path) {}
    DataSet::DataSet *read();
    void write(DataSet::DataSet *data_set);
  };
}

#endif
