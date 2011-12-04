#include "text_pipeline.h"

namespace Preprocessing { namespace Text; }

SparseExample *TextPipeline::process_text(char *text) {
  tokens.clear();
  tokeniser.tokenise(this, text);
  return generator.generate(&tokens);
}

void TextPipeline::process_token(char *start, char *end) {
  for(int i = 0; i < processors.size(); i++)
    processors[i].process(start, end);
  
  for(int i = 0; i < selectors.size(); i++)
    if(!selectors[i].select(start, end))
      return;
  
  tokens.push_back(start);
}
