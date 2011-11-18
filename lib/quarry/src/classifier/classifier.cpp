#include "classifier.h"

int Classifier::Classifier::classify(DataSet::Example *example) {
  double max_score = 0.0, category_score = 0.0;
  int max_category = 1;

  for(int category = 1; category <= data_set->categories_size(); category++) {
    category_score = score(category, example);
    if(category_score > max_score) {
      max_score = category_score;
      max_category = category;
    }
  }
  
  return max_category;
}

vector<Classifier::Score> *Classifier::Classifier::rank(DataSet::Example *example) {
  vector<Score> *scores = score_all(example);
  sort(scores->begin(), scores->end(), Score::compare);
  return scores;
}

vector<Classifier::Score> *Classifier::Classifier::score_all(DataSet::Example *example) {
  vector<Score> *scores = new vector<Score>();
  scores->reserve(data_set->categories_size());
  
  for(int category = 1; category <= data_set->categories_size(); category++)
    scores->push_back(Score(category, score(category, example)));
  
  return scores;
}
