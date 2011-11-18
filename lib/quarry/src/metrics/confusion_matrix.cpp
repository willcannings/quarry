#include "confusion_matrix.h"
#include <iostream>
const string ConfusionMatrix::average_row_name = "Average";

// TODO: CM should reference a classifier, not a data set

ConfusionMatrix::ConfusionMatrix(DataSet::DataSet *data_set) : incorrect(0), correct(0), data_set(data_set) {
  int count = data_set->categories_size();
  counts.reserve(count);
  for(int i = 0; i < count; i++)
    counts.push_back(valarray<int>(0, count));
}

void ConfusionMatrix::add(int predicted, int actual) {
  // category indexes are 1 based
  counts[predicted - 1][actual - 1] += 1;
  if(predicted == actual)
    correct++;
  else
    incorrect++;
}

double ConfusionMatrix::accuracy() {
  return ((double)correct) / (correct + incorrect);
}

double ConfusionMatrix::error() {
  return ((double)incorrect) / (correct + incorrect);
}

// true positive
int ConfusionMatrix::tp(int category) {
  return counts[category - 1][category - 1];
}

// false positive
int ConfusionMatrix::fp(int category) {
  return counts[category - 1].sum() - tp(category);
}

// true negative
int ConfusionMatrix::tn(int category) {
  int sum = 0, count = data_set->categories_size();
  for(int i = 1; i <= count; i++)
    for(int j = 1; j <= count; j++)
      if(i != category && j != category)
        sum += counts[i - 1][j - 1];
  return sum;
}

// false negative
int ConfusionMatrix::fn(int category) {
  int sum = 0, count = data_set->categories_size();
  for(int i = 1; i <= count; i++)
    if(i != category)
      sum += counts[i - 1][category - 1];
  return sum;
}

double ConfusionMatrix::precision(int category) {
  int denom = tp(category) + fp(category);
  if(denom == 0)
    return 0.0;
  return ((double)tp(category)) / denom;
}

double ConfusionMatrix::recall(int category) {
  int denom = tp(category) + fn(category);
  if(denom == 0)
    return 0.0;
  return ((double)tp(category)) / denom;
}

double ConfusionMatrix::fscore(int category) {
  double p = precision(category);
  double r = recall(category);
  if((p + r) == 0.0)
    return 0.0;
  return (2 * p * r) / (p + r);
}

void ConfusionMatrix::print_summary() {
  // overall counts and summary
  cout.precision(4);
  cout << "== Summary ==" << endl;
  cout << setw(23) <<"Correctly classified:" << setw(12) << right << correct << setw(10) << right << accuracy() * 100 << "%" << endl;
  cout << setw(23) << "Incorrectly classified:" << setw(12) << right << incorrect << setw(10) << right << error() * 100 << "%" << endl;
  cout << setw(23) << "Total classifications:" << setw(12) << right << correct + incorrect << endl << endl;
  
  // determine the width of the left (category name) column
  int max_name_length = 0;
  for(int category = 1; category <= data_set->categories_size(); category++)
    if(data_set->category_feature()->names[category].length() > max_name_length)
      max_name_length = data_set->category_feature()->names[category].length();
  if(average_row_name.length() > max_name_length)
    max_name_length = average_row_name.length();
  max_name_length += 1;
  
  // detailed category information
  cout << "== Category Performance ==" << endl;
  cout << setw(max_name_length) << "";
  cout << setw(9) << right << "True +";
  cout << setw(9) << right << "False +";
  cout << setw(9) << right << "True -";
  cout << setw(9) << right << "False -";
  cout << setw(9) << right << "Precis.";
  cout << setw(9) << right << "Recall";
  cout << setw(9) << right << "F-score" << endl;
  
  for(int category = 1; category <= data_set->categories_size(); category++) {
    cout << setw(max_name_length) << data_set->category_feature()->names[category];
    cout << setw(9) << tp(category);
    cout << setw(9) << fp(category);
    cout << setw(9) << tn(category);
    cout << setw(9) << fn(category);
    cout << setw(8) << precision(category) * 100 << "%";
    cout << setw(8) << recall(category) * 100 << "%";
    cout << setw(8) << fscore(category) * 100 << "%" << endl;
  }
  
  cout << setw(max_name_length) << average_row_name;
  cout << setw(9) << avg_tp();
  cout << setw(9) << avg_fp();
  cout << setw(9) << avg_tn();
  cout << setw(9) << avg_fn();
  cout << setw(8) << avg_precision() * 100 << "%";
  cout << setw(8) << avg_recall() * 100 << "%";
  cout << setw(8) << avg_fscore() * 100 << "%" << endl;
}
