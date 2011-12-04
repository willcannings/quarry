#ifndef __pos_tag_selector_h__
#define __pos_tag_selector_h__
#include "token_selector.h"

namespace Preprocessing {
  namespace Text {
    
    class POSTagSelector : public TokenSelector {
    public:
      bool select(char *start, char *end) {
        return true;
      }
    };
    
  }
}

#endif
