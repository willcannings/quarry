#ifndef __inplace_processor_h__
#define __inplace_processor_h__

namespace Preprocessing {
  namespace Text {
    
    class InplaceProcessor {
    public:
      InplaceProcessor() {}
      virtual char *process(char *start, char *end) { return end; }
      virtual uint32_t mark() = 0;
    };
    
  }
}

#endif
