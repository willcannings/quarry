#ifndef __numeric_feature_h__
#define __numeric_feature_h__
#include "data_set/example.h"
#include "data_set/feature.h"
#include <iostream>

namespace DataSet {
  class DataSet;
  
  class NumericFeature : public Feature {
  public:
    NumericFeature(string name, int index) : Feature(name, index), category_counts(NULL), non_zero_examples() {
      reset();
    }
    
    NumericFeature *clone() {
      return new NumericFeature(name, index);
    }

    void reset() {
      memset(&counts, 0, sizeof(Counts));
      if(category_counts != NULL)
        free(category_counts);
      category_counts = NULL;
      non_zero_examples.clear();
    }
    
    void prepare_for_counting(DataSet *data_set);
    void count_example(double value, int category_index);
    void finalise_counting(DataSet *data_set);

    void prepare_for_indexing(DataSet *data_set);
    void index_example(double value, Example *example);
    void finalise_indexing(DataSet *data_set);
    
    // counts
    typedef struct {
      int    non_zero_count;
      double sum;
      double sq_sum;
      double min;
      double max;
      double mean;
      double variance;
    } Counts;
    
    // counts for this feature over the entire data set
    Counts counts;
    int    non_zero_count()                   { return counts.non_zero_count; }
    double sum()                              { return counts.sum; }
    double sq_sum()                           { return counts.sq_sum; }
    double min()                              { return counts.min; }
    double max()                              { return counts.max; }
    double mean()                             { return counts.mean; }
    double variance()                         { return counts.variance; }
    
    // counts for this feature per category
    Counts *category_counts;
    int    category_non_zero_count(int index) { return category_counts[index].non_zero_count; }
    double category_sum(int index)            { return category_counts[index].sum; }
    double category_sq_sum(int index)         { return category_counts[index].sq_sum; }
    double category_min(int index)            { return category_counts[index].min; }
    double category_max(int index)            { return category_counts[index].max; }
    double category_mean(int index)           { return category_counts[index].mean; }
    double category_variance(int index)       { return category_counts[index].variance; }
    
    void print(DataSet *data_set);
    
    void print_counts(Counts *c) {
      cout << c->non_zero_count << ";" << c->sum << ";" << c->sq_sum << ";" << c->min << ";" << c->max << ";" << c->mean << ";" << c->variance << endl;
    }
    
    // indexes
    vector<Example *> non_zero_examples;
  };
}

#endif
