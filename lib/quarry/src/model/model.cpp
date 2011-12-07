#include "model.h"

void Model::Model::train(DataSet::Example *example) {
}

void Model::Model::train_text(string text) {
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
