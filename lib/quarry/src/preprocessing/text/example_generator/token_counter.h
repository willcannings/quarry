#ifndef __token_counter_h__
#define __token_counter_h__
#include "example_generator.h"
#include <map>

namespace Preprocessing {
  namespace Text {
    
    class TokenCounter : public ExampleGenerator {
    public:
      static const uint32_t file_mark = 'tcou';
      uint32_t mark() { return file_mark; }
      
      typedef enum {
        Count,
        Local,
        Binary
      } TokenCounterWeight;
      
      map<string, int> token_counts;
      TokenCounterWeight weight;
      
      TokenCounter(TokenCounterWeight weight = Count) : ExampleGenerator(), token_counts(), weight(weight) {}
      
      DataSet::SparseExample *generate(DataSet::SparseDataSet *data_set, vector<char *> *tokens, bool create_features) {
        int max_count = 0, count = 0;
        double value = 0.0;
        token_counts.clear();
        string token;
        
        // count the number of occurrences of each token
        for(vector<char *>::iterator tokens_it = tokens->begin(); tokens_it != tokens->end(); tokens_it++) {
          token = string(*tokens_it);
          count = ++token_counts[token];
          if(count > max_count)
            max_count = count;
        }
        
        // construct the example
        DataSet::SparseExample *example = data_set->new_example(token_counts.size());
        DataSet::Feature *feature = NULL;
        
        for(map<string, int>::iterator token_counts_it = token_counts.begin(); token_counts_it != token_counts.end(); token_counts_it++) {
          value = token_counts_it->second;
          
          if(weight == Local)
            value = value / max_count;
          else if(weight == Binary)
            value = 1;
          
          if(create_features) {
            example->set_value(data_set->get_or_create_numeric_feature_by_name(token_counts_it->first)->index, value);
          } else {
            feature = data_set->get_feature_by_name(token_counts_it->first);
            if(feature)
              example->set_value(feature->index, value);
          }
        }
        
        return example;
      }
    };
    
  }
}

#endif
