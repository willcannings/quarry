#include "sparse_data_set.h"
#include "sparse_example.h"
#include <stdlib.h>

double DataSet::SparseExample::get_value(int feature_index) {
  if(feature_index == 0 && size != 0)
    return values[0].value;
  
  int low = 0;
  int high = size - 1;
  int mid = high / 2;
  
  // branch prediction makes this triple clause if statement faster
  // than a double clause "single comparison" search. precondition
  // loops also seem to be faster than post condition loops in GCC,
  // really don't know why... this implementation ends up being
  // around 30% faster than well known single comparison versions.
  while(low <= high) {
    if(values[mid].index < feature_index) {
      low = mid + 1;
    } else if(values[mid].index > feature_index) {
      high = mid - 1;
    } else {
      return values[mid].value;
    }
    mid = (high + low) / 2;
  }
  
  return 0.0;
}

double DataSet::SparseExample::get_value(string feature_name, SparseDataSet *data_set) {
  return get_value(data_set->get_feature_by_name(feature_name)->index);
}

void DataSet::SparseExample::set_value(int feature_index, double new_value) {
  int i = 0;
  
  for(; i < size; i++) {
    if(values[i].index == feature_index) {
      values[i].value = new_value;
      return;
    } else if(values[i].index > feature_index) {
      break;
    }
  }
  
  if(buffer_size == size)
    values = (Value *) realloc(values, sizeof(Value) * (++buffer_size));
  
  if(i != size)
    memcpy(&values[i + 1], &values[i], (size - i) * sizeof(Value));
  
  values[i].index = feature_index;
  values[i].value = new_value;
  size++;
}

void DataSet::SparseExample::append_value(int feature_index, double new_value) {
  if(buffer_size == size)
    values = (Value *) realloc(values, sizeof(Value) * (++buffer_size));
  values[size].index = feature_index;
  values[size].value = new_value;
  size++;
}

double DataSet::SparseExample::euclidean_distance(Example *other_example) {
  return 0.0;
}

double DataSet::SparseExample::cosine_distance(Example *other_example) {
  return 0.0;
}

void DataSet::SparseExample::print() {
  for(int i = 0; i < size; i++) {
    cout << values[i].index << ":" << values[i].value;
    if(i < (size - 1))
      cout << ",";
  }
  cout << endl;
}
