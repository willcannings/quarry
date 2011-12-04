#include "text_pipeline.h"

DataSet::SparseExample *Preprocessing::Text::TextPipeline::process_text(char *text) {
  tokens.clear();
  tokeniser->tokenise(text);
  return generator->generate(&tokens);
}

void Preprocessing::Text::TextPipeline::process_token(char *start, char *end) {
  for(int i = 0; i < processors.size(); i++)
    processors[i]->process(start, end);
  
  for(int i = 0; i < selectors.size(); i++)
    if(!selectors[i]->select(start, end))
      return;
  
  tokens.push_back(start);
}

Preprocessing::Text::TextPipeline *Preprocessing::Text::StandardPipeline(DataSet::SparseDataSet *data_set) {
  TextPipeline *pipeline = new TextPipeline();
  pipeline->tokeniser = new SimpleTokeniser(pipeline);
  pipeline->processors.push_back(new Downcase());
  pipeline->processors.push_back(new PorterStemmer());
  pipeline->selectors.push_back(new StopWords());
  pipeline->generator = new TokenCounter(data_set);
  return pipeline;
}