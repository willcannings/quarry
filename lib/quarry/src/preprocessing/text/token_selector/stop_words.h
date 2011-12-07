#ifndef __stop_words_h__
#define __stop_words_h__
#include "token_selector.h"

namespace Preprocessing {
  namespace Text {
    
    class StopWords : public TokenSelector {
    public:
      static const uint32_t file_mark = 'stop';
      uint32_t mark() { return file_mark; }

      StopWords();
      bool select(char *start, char *end);
    };
    
  }
}

#endif
