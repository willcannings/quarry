#ifndef __tokeniser_h__
#define __tokeniser_h__

namespace Preprocessing {
  namespace Text {
    class TextPipeline;
    
    class Tokeniser {
    public:
      TextPipeline *pipeline;
      Tokeniser(TextPipeline *pipeline) : pipeline(pipeline) {}
      virtual void tokenise(char *text) {}
      virtual uint32_t mark() = 0;
    };
    
  }
}

#endif
