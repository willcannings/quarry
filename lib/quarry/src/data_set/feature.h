#ifndef __feature_h__
#define __feature_h__
#include <string>
using namespace std;

namespace DataSet {
  class DataSet;
  
  class Feature {
  public:
    string  name;
    int     index;
    
    string  get_name()                  { return name; }
    int     get_index()                 { return index; }
    void    set_name(string new_name)   { name = new_name; }
    void    set_index(int new_index)    { index = new_index; }
    
    Feature(string name, int index) : name(name), index(index) {}
    virtual ~Feature() {}
    virtual Feature *clone() { return NULL; }
    virtual void reset() {}
    virtual void print() {}

    // counting
    virtual void prepare_for_counting(DataSet *data_set) {}
    virtual void count_example(double value, int category_index) {}
    virtual void finalise_counting(DataSet *data_set) {}
    
    // indexing
    virtual void prepare_for_indexing(DataSet *data_set) {}
    virtual void index_example(double value, Example *example) {}
    virtual void finalise_indexing(DataSet *data_set) {}
  };
}

#endif
