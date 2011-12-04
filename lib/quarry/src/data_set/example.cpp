#include "data_set.h"
#include "example.h"

int DataSet::Example::category_index(DataSet *data_set) {
  return (int)get_value(data_set->category_index);
}

void DataSet::Example::set_category_index(DataSet *data_set, int index) {
  set_value(data_set->category_index, index);
}
