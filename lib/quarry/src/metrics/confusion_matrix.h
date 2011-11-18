#ifndef __confusion_matrix__
#define __confusion_matrix__
#include "data_set/data_set.h"
#include <vector>
#include <valarray>
#include <iostream>
#include <iomanip>
using namespace std;

namespace DataSet {
  class Category;
}

class ConfusionMatrix {
public:
  static const string average_row_name;
  DataSet::DataSet        *data_set;
  vector<valarray<int> >  counts;
  int                     correct;
  int                     incorrect;
  
  ConfusionMatrix(DataSet::DataSet *data_set);
  void merge(ConfusionMatrix *other) {
    incorrect += other->incorrect;
    correct += other->correct;
    
    for(unsigned int i = 0; i < counts.size(); i++)
      counts[i] += other->counts[i];
  }
  
  void add(int predicted, int actual);
  double accuracy();
  double error();
  int tp(int category);
  int fp(int category);
  int tn(int category);
  int fn(int category);
  double precision(int category);
  double recall(int category);
  double fscore(int category);
  void print_summary();
  
  // averages
  double avg_tp() {
    return apply<int>(&ConfusionMatrix::tp);
  }
  
  double avg_fp() {
    return apply<int>(&ConfusionMatrix::fp);
  }
  
  double avg_tn() {
    return apply<int>(&ConfusionMatrix::tn);
  }
  
  double avg_fn() {
    return apply<int>(&ConfusionMatrix::fn);
  }
  
  double avg_precision() {
    return apply<double>(&ConfusionMatrix::precision);
  }
  
  double avg_recall() {
    return apply<double>(&ConfusionMatrix::recall);
  }
  
  double avg_fscore() {
    return apply<double>(&ConfusionMatrix::fscore);
  }
  
protected:
  template <class T, class Function>
  double apply(Function func) {
    T result = 0.0;
    for(int category = 1; category <= data_set->categories_size(); category++)
      result += (this->*func)(category);
    return result / ((double)counts.size());
  }
};

#endif
