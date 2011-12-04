#ifndef __token_selector_h__
#define __token_selector_h__

namespace Preprocessing {
  namespace Text {
    
    class TokenSelector {
    public:
      virtual bool select(char *start, char *end) { return true; }
    };
    
  }
}

#endif
