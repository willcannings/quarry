#ifndef __folders_h__
#define __folders_h__
#include "preprocessing/text/text_pipeline.h"
#include "data_set/data_set.h"
#include "storage/storage.h"
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

namespace Storage {
  class Folders : public Storage {
    void load_directory(string path, DataSet::SparseDataSet *data_set, int category_index);
    
  public:
    string path;
    Preprocessing::Text::TextPipeline *pipeline;
    
    Folders(string path, Preprocessing::Text::TextPipeline *pipeline) : path(path), pipeline(pipeline) {}
    DataSet::DataSet *read();
    void write(DataSet::DataSet *data_set);
  };
}

#endif
