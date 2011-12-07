#include "model.h"

void Model::Model::train(DataSet::Example *example) {
}

void Model::Model::train_text(string text) {
}

DataSet::Example *Model::Model::process_text(string text, bool create_features) {
  return text_pipeline->process_text((DataSet::SparseDataSet *)data_set, (char *)text.c_str(), create_features);
}

void Model::Model::add_text_example(string text, string category) {
  DataSet::Example *example = text_pipeline->process_text((DataSet::SparseDataSet *)data_set, (char *)text.c_str(), true);
  example->set_category_index(data_set, data_set->category_feature()->value_index(category));
}

int Model::Model::classify(DataSet::Example *example) {
  return classifier->classify(example);
}

int Model::Model::classify_text(string text) {
  DataSet::SparseExample *example = text_pipeline->process_text((DataSet::SparseDataSet *)data_set, (char *)text.c_str(), false);
  int category = classifier->classify(example);
  delete example;
  return category;
}

vector<Classifier::Score> *Model::Model::rank(DataSet::Example *example) {
  return classifier->rank(example);
}

vector<Classifier::Score> *Model::Model::rank_text(string text) {
  DataSet::SparseExample *example = text_pipeline->process_text((DataSet::SparseDataSet *)data_set, (char *)text.c_str(), false);
  vector<Classifier::Score> *ranks = classifier->rank(example);
  delete example;
  return ranks;
}
