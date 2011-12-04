#include "quarry.h"
#include <stdexcept>
#include <cstring>

int main() {
  /*Storage::ARFF *reader = new Storage::ARFF("/Users/will/Desktop/classifier/src/categories_100.arff");
  DataSet::DataSet *ds = reader->read();
  Classifier::NaiveBayesClassifier *c = new Classifier::NaiveBayesClassifier(ds);
  ConfusionMatrix *cm = ds->cross_fold_validation(c, 2);
  cm->print_summary();*/
  
  Preprocessing::Text::TextPipeline *pipeline = Preprocessing::Text::StandardPipeline();
  Storage::Folders *reader = new Storage::Folders("/Users/will/dev/classifier/small", pipeline);
  DataSet::DataSet *data_set = reader->read();
  
  //Preprocessing::Examples::LocalWeight *lw = new Preprocessing::Examples::LocalWeight();
  //lw->process_data_set(data_set);
  
  data_set->category_feature()->print();
  cout << "Examples: " << data_set->examples_size() << ", features: " << data_set->features_size() << endl;
  data_set->examples[1]->print();
  
  Classifier::NaiveBayesClassifier *c = new Classifier::NaiveBayesClassifier(data_set);
  ConfusionMatrix *cm = data_set->cross_fold_validation(c, 5);
  cm->print_summary();
  
  return 0;
}
