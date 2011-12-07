#ifndef __simple_tokeniser_h__
#define __simple_tokeniser_h__
#include "tokeniser.h"

namespace Preprocessing {
  namespace Text {
    
    class SimpleTokeniser : public Tokeniser {
    public:
      static const uint32_t file_mark = 'simt';
      uint32_t mark() { return file_mark; }
      
      SimpleTokeniser(TextPipeline *pipeline) : Tokeniser(pipeline) {}
      void tokenise(char *text);
    };
    
  }
}

#endif
