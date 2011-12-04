#ifndef __text_pipeline_h__
#define __text_pipeline_h__
#include "data_set/sparse/sparse_example.h"
#include "example_generator/example_generator.h"
#include "example_generator/token_counter.h"
#include "inplace_processor/inplace_processor.h"
#include "inplace_processor/downcase.h"
#include "inplace_processor/porter_stemmer.h"
#include "token_selector/token_selector.h"
#include "token_selector/stop_words.h"
#include "tokeniser/tokeniser.h"
#include "tokeniser/simple_tokeniser.h"
#include <vector>

namespace Preprocessing {
  namespace Text {
    class Tokeniser;
    
    class TextPipeline {
    public:
      Tokeniser *tokeniser;
      vector<InplaceProcessor *> processors;
      vector<TokenSelector *> selectors;
      ExampleGenerator *generator;
      vector<char *> tokens;
      
      TextPipeline() : processors(), selectors(), tokens() {}      
      DataSet::SparseExample *process_text(char *text);
      void process_token(char *start, char *end);
    };
    
    TextPipeline *StandardPipeline(DataSet::SparseDataSet *data_set) {
      TextPipeline *pipeline = new TextPipeline();
      pipeline->tokeniser = new SimpleTokeniser(pipeline);
      pipeline->processors.push_back(new Downcase());
      pipeline->processors.push_back(new PorterStemmer());
      pipeline->selectors.push_back(new StopWords());
      pipeline->generator = new TokenCounter(data_set);
      return pipeline;
    }
    
  }
}

#endif
