#ifndef __example_h__
#define __example_h__

namespace DataSet {
  class DataSet;
  class Example {
  public:
    Example() {}
    virtual ~Example() {}
    int  category_index(DataSet *data_set);
    virtual double  get_value(int index) { return 0.0; }
    virtual void    set_value(int index, double new_value) {}
    virtual double  euclidean_distance(Example *other_example) { return 0.0; }
    virtual double  cosine_distance(Example *other_example) { return 0.0; }
    virtual bool    dense() { return false; }
    virtual bool    sparse() { return false; }
    virtual void    print() {}
  };
}

#endif
