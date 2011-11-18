#include "sparse_data_set.h"
#include "sparse_example.h"
#include <stdlib.h>

double DataSet::SparseExample::get_value(int feature_index) {
  for(int i = 0; i < count; i++)
    if(values[i].index == feature_index)
      return values[i].value;
  return 0.0;
}

double DataSet::SparseExample::get_value(string feature_name, SparseDataSet *data_set) {
  return get_value(data_set->get_feature_by_name(feature_name)->index);
}

void DataSet::SparseExample::set_value(int feature_index, double new_value) {
  int i = 0;
  
  for(; i < count; i++) {
    if(values[i].index == feature_index) {
      values[i].value = new_value;
      return;
    } else if(values[i].index > feature_index) {
      break;
    }
  }
  
  if(size == count)
    values = (Value *) realloc(values, sizeof(Value) * (++size));
  
  if(i != count)
    memcpy(&values[i + 1], &values[i], (count - i) * sizeof(Value));
  
  values[i].index = feature_index;
  values[i].value = new_value;
  count++;
}

void DataSet::SparseExample::append_value(int feature_index, double new_value) {
  if(size == count)
    values = (Value *) realloc(values, sizeof(Value) * (++size));
  values[count].index = feature_index;
  values[count].value = new_value;
  count++;
}

double DataSet::SparseExample::euclidean_distance(Example *other_example) {
  return 0.0;
}

double DataSet::SparseExample::cosine_distance(Example *other_example) {
  return 0.0;
}
