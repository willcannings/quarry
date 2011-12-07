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
#include "token_selector/pos_tag_selector.h"
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
      
      TextPipeline() : tokeniser(NULL), processors(), selectors(), generator(NULL), tokens() {}      
      DataSet::SparseExample *process_text(DataSet::SparseDataSet *data_set, char *text);
      void process_token(char *start, char *end);
    };
    
    TextPipeline *StandardPipeline();
  }
}

#endif
