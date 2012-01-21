#ifndef __stop_words_h__
#define __stop_words_h__
#include "token_selector.h"
#include <tr1/unordered_set>
using namespace std;
using namespace tr1;


namespace Preprocessing {
  namespace Text {
    
    class StopWords : public TokenSelector {
    public:
      static const uint32_t file_mark = 'stop';
      uint32_t mark() { return file_mark; }
      unordered_set<string> stop_words;

      StopWords();
      ~StopWords() {}
      bool select(char *start, char *end);
    };
    
  }
}

#endif
