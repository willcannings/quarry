#ifndef __stop_words_h__
#define __stop_words_h__
#include "token_selector.h"

namespace Preprocessing {
  namespace Text {
    
    class StopWords : public TokenSelector {
    public:
      StopWords();
      bool select(char *start, char *end);
    };
    
  }
}

#endif
