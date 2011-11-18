#include "quarry.h"
#include <stdexcept>

int main() {
  Storage::ARFF *reader = new Storage::ARFF("/Users/will/Desktop/test_reduced.arff");
  DataSet::DataSet *ds = reader->read();
  Classifier::NaiveBayesClassifier *c = new Classifier::NaiveBayesClassifier(ds);
  ConfusionMatrix *cm = ds->cross_fold_validation(c, 2);
  cm->print_summary();
  return 0;
}
