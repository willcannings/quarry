#ifndef __pos_tag_selector_h__
#define __pos_tag_selector_h__
#include "token_selector.h"

namespace Preprocessing {
  namespace Text {
    
    class POSTagSelector : public TokenSelector {
    public:
      static const uint32_t file_mark = 'post';
      uint32_t mark() { return file_mark; }
      
      bool select(char *start, char *end) {
        return true;
      }
    };
    
  }
}

#endif
