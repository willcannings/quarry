#ifndef __downcase_h__
#define __dowmcase_h__
#include "inplace_processor.h"
#include <cctype>

namespace Preprocessing {
  namespace Text {
    
    class Downcase : public InplaceProcessor {
    public:
      char *process(char *start, char *end) {
        while(start != end) {
          *start = tolower(*start);
          start++;
        }
        return end;
      }
    };
    
  }
}

#endif
