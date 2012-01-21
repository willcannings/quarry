#ifndef __token_selector_h__
#define __token_selector_h__
#include <stdint.h>

namespace Preprocessing {
  namespace Text {
    
    class TokenSelector {
    public:
      virtual ~TokenSelector() {}
      virtual bool select(char *start, char *end) { return true; }
      virtual uint32_t mark() = 0;
    };
    
  }
}

#endif
