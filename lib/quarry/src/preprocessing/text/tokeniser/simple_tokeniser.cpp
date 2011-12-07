#include "preprocessing/text/text_pipeline.h"
#include "simple_tokeniser.h"

void Preprocessing::Text::SimpleTokeniser::tokenise(char *text) {
  char *start, *end;
  bool intoken = false;
  bool active  = true;
  
  // to simplify the code, the while condition is not while(*text),
  // because the if(intoken) block needs to run when *text == 0 at
  // the end of the string.
  while(active) {
    active = *text;
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
