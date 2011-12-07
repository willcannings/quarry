#include "data_set/data_set.h"
#include "data_set/example.h"
#include "numeric_feature.h"
#include "stdlib.h"

void DataSet::NumericFeature::prepare_for_counting(DataSet *data_set) {
  category_counts = (Counts *) calloc(sizeof(Counts), data_set->categories_size() + 1);
}

void DataSet::NumericFeature::count_example(double value, int category_index) {
  // non zero count
  if(value != 0.0) {
    counts.non_zero_count++;
    category_counts[category_index].non_zero_count++;
  }
  
  // minima
  if(value < counts.min)
    counts.min = value;
  if(value < category_counts[category_index].min)
    category_counts[category_index].min = value;

  // maxima
  if(value > counts.max)
    counts.max = value;
  if(value > category_counts[category_index].max)
    category_counts[category_index].max = value;
  
  // sum
  counts.sum += value;
  category_counts[category_index].sum += value;
  
  // squared sum
  counts.sq_sum += (value * value);
  category_counts[category_index].sq_sum += (value * value);
}

void DataSet::NumericFeature::finalise_counting(DataSet *data_set) {
  int categories_count = data_set->categories_size();
  int examples_count = data_set->examples.size();
  
  // mean
  counts.mean = counts.sum / examples_count;
  for(int i = 1; i <= categories_count; i++)
    category_counts[i].mean = category_counts[i].sum / data_set->category_feature()->value_frequency(i);
  
  // variance
  counts.variance = (counts.sq_sum / examples_count) - (counts.mean * counts.mean);
  for(int i = 1; i <= categories_count; i++)
    category_counts[i].variance = (category_counts[i].sq_sum / data_set->category_feature()->value_frequency(i)) - (category_counts[i].mean * category_counts[i].mean);
}

void DataSet::NumericFeature::prepare_for_indexing(DataSet *data_set) {}

void DataSet::NumericFeature::index_example(double value, Example *example) {
  if(value != 0.0)
    non_zero_examples.push_back(example);
}

void DataSet::NumericFeature::finalise_indexing(DataSet *data_set) {}

void DataSet::NumericFeature::print(DataSet::DataSet *data_set) {
  cout << "F" << index << ", " << name << endl;
  print_counts(&counts);
  for(int i = 0; i < (data_set->categories_size() + 1); i++) {
    cout << "C" << i << ":";
    print_counts(&(category_counts[i]));
  }
}
