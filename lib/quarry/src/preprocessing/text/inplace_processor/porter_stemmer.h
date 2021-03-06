#ifndef __porter_stemmer_h__
#define __porter_stemmer_h__
#include "inplace_processor.h"

// from porter_stemmer_original.c
extern "C" {
  struct stemmer;
  extern struct stemmer * create_stemmer(void);
  extern void free_stemmer(struct stemmer * z);
  extern int stem(struct stemmer * z, char * b, int k);
}

namespace Preprocessing {
  namespace Text {
    
    class PorterStemmer : public InplaceProcessor {
    public:
      static const uint32_t file_mark = 'port';
      uint32_t mark() { return file_mark; }
      
      struct stemmer *stemm;
      PorterStemmer() : InplaceProcessor() {
        stemm = create_stemmer();
      }
      
      ~PorterStemmer() {
        free_stemmer(stemm);
      }
      
      char *process(char *start, char *end) {
        int length = end - start;
        int new_length = stem(stemm, start, end - start - 1);
        
        for(int i = new_length + 1; i <= length; i++)
          start[i] = 0;
        
        return start + new_length;
      }
    };
    
  }
}

#endif
