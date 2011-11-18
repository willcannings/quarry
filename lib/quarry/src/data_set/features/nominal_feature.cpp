#include "nominal_feature.h"
#include "data_set/data_set.h"
#include "data_set/example.h"


void DataSet::NominalFeature::prepare_for_counting(DataSet *data_set) {
  int categories_count = data_set->categories_size();
  int values_count = names.size();
  
  category_frequencies.resize(categories_count + 1);
  category_probabilities.resize(categories_count + 1);
  probabilities.resize(values_count);
  frequencies.resize(values_count);
  
  for(int i = 1; i <= categories_count; i++) {
    category_frequencies[i].resize(values_count);
    category_probabilities[i].resize(values_count);
  }
}

void DataSet::NominalFeature::count_example(double value, int category_index) {
  frequencies[(int)value] += 1;
  category_frequencies[category_index][(int)value] += 1;
}

void DataSet::NominalFeature::finalise_counting(DataSet *data_set) {
  int categories_count = data_set->categories_size();
  int examples_count = data_set->examples.size();
  int values_count = names.size();
  
  // overall value probabilities
  for(int i = 0; i < values_count; i++)
    probabilities[i] = ((double)frequencies[i] + 1) / examples_count;
  
  // value probabilities per category
  if(index != data_set->category_index) {
    for(int i = 1; i <= categories_count; i++) {
      for(int j = 0; j < values_count; j++)
        category_probabilities[i][j] = ((double)category_frequencies[i][j] + 1) / data_set->category_feature()->value_frequency(i);
    }
  }
}

void DataSet::NominalFeature::prepare_for_indexing(DataSet *data_set) {
  examples_with_value.resize(names.size());
}

void DataSet::NominalFeature::index_example(double value, Example *example) {
  examples_with_value[(int)value].push_back(example);
}

void DataSet::NominalFeature::finalise_indexing(DataSet *data_set) {}
