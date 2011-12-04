#include "preprocessing/text/text_pipeline.h"
#include "simple_tokeniser.h"

void Preprocessing::Text::SimpleTokeniser::tokenise(char *text) {
  char *start, *end;
  bool intoken = false;
  
  while(*text) {
    if(isalnum(*text)) {
      if(!intoken) {
        intoken = true;
        start = text;
      }
    } else {
      if(intoken) {
        intoken = false;
        *text = 0;
        end = text;
        pipeline->process_token(start, end);
      }
    }
    text++;
  }  
}
