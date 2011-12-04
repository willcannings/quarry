#ifndef __token_counter_h__
#define __token_counter_h__
#include "example_generator.h"
#include <map>

namespace Preprocessing {
  namespace Text {
    
    class TokenCounter : public ExampleGenerator {
    public:
      map<string, int> token_counts;
      TokenCounter() : ExampleGenerator(), token_counts() {}
      
      DataSet::SparseExample *generate(DataSet::SparseDataSet *data_set, vector<char *> *tokens) {
        DataSet::SparseExample *example = data_set->new_example();
        token_counts.clear();
        string token;
        
        // count the number of occurrences of each token
        for(vector<char *>::iterator tokens_it = tokens->begin(); tokens_it != tokens->end(); tokens_it++) {
          token = string(*tokens_it);
          token_counts[token]++;
        }
        
        // construct the example
        DataSet::NominalFeature *categories = data_set->category_feature();
        for(map<string, int>::iterator token_counts_it = token_counts.begin(); token_counts_it != token_counts.end(); token_counts_it++) {
          example->set_value(data_set->get_or_create_numeric_feature_by_name(token_counts_it->first)->index, token_counts_it->second);
        }
        
        return example;
      }
    };
    
  }
}

#endif
