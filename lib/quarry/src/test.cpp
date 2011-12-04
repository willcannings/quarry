#include "quarry.h"
#include <stdexcept>

int main() {
  /*Storage::ARFF *reader = new Storage::ARFF("/Users/will/Desktop/classifier/src/categories_100.arff");
  DataSet::DataSet *ds = reader->read();
  Classifier::NaiveBayesClassifier *c = new Classifier::NaiveBayesClassifier(ds);
  ConfusionMatrix *cm = ds->cross_fold_validation(c, 2);
  cm->print_summary();*/
  
  DataSet::SparseDataSet *data_set = new DataSet::SparseDataSet();
  Preprocessing::Text::TextPipeline *pipeline = Preprocessing::Text::StandardPipeline(data_set);
  
  return 0;
}
