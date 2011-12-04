#ifndef __simple_tokeniser_h__
#define __simple_tokeniser_h__
#include "tokeniser.h"

namespace Preprocessing {
  namespace Text {
    
    class SimpleTokeniser : public Tokeniser {
    public:
      SimpleTokeniser(TextPipeline *pipeline) : Tokeniser(pipeline) {}
      void tokenise(char *text);
    };
    
  }
}

#endif
