#ifndef __token_counter_h__
#define __token_counter_h__
#include "example_generator.h"
#include <map>

namespace Preprocessing {
  namespace Text {
    
    class TokenCounter : public ExampleGenerator {
    public:
      map<string, int> token_counts;
      TokenCounter(DataSet::SparseDataSet *data_set) : ExampleGenerator(data_set), token_counts() {}
      
      DataSet::SparseExample *generate(vector<char *> *tokens) {
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
          example->set_value(categories->value_index(token_counts_it->first), token_counts_it->second);
        }
        
        return example;
      }
    };
    
  }
}

#endif
