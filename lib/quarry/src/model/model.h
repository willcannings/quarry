#ifndef __model_h__
#define __model_h__
#include "data_set/data_set.h"
#include "data_set/example.h"
#include "classifier/classifier.h"
#include "preprocessing/text/text_pipeline.h"

namespace Model {
  class Model {
  public:
    DataSet::DataSet *data_set;
    Classifier::Classifier *classifier;
    Preprocessing::Text::TextPipeline *text_pipeline;
    
    Model() : data_set(NULL), classifier(NULL), text_pipeline(NULL) {}
    
    void train(DataSet::Example *example);
    void train_text(string text);
    DataSet::Example *process_text(string text, bool create_features);
    void add_text_example(string text, string category);
    int classify(DataSet::Example *example);
    int classify_text(string text);
    vector<Classifier::Score> *rank(DataSet::Example *example);
    vector<Classifier::Score> *rank_text(string example);
    
    void set_data_set(DataSet::DataSet *ds) {
      data_set = ds;
    }
    
    DataSet::DataSet *get_data_set() {
      return data_set;
    }
    
    void set_classifier(Classifier::Classifier *c) {
      classifier = c;
    }
    
    Classifier::Classifier *get_classifier() {
      return classifier;
    }
    
    void set_text_pipeline(Preprocessing::Text::TextPipeline *pipeline) {
      text_pipeline = pipeline;
    }
    
    Preprocessing::Text::TextPipeline *get_text_pipeline() {
      return text_pipeline;
    }
  };
}

#endif
