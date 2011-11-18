#include "arff.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

#define BUFFER_SIZE             (10 * 1024)
#define RELATION_PREFIX         "@relation "
#define RELATION_PREFIX_LENGTH  10
#define ATTRIBUTE_PREFIX        "@attribute "
#define ATTRIBUTE_PREFIX_LENGTH  11
#define DATA_PREFIX             "@data"
#define DATA_PREFIX_LENGTH      5
#define NUMERIC_TYPE            "numeric"
#define NUMERIC_TYPE_LENGTH     7


// skip whitespace and other delimiters
#define skip_delimiters(conditions) \
  while(conditions)\
    (*str)++;

#define skip_only_whitespace()                      skip_delimiters((isspace(**str)))
#define skip_whitespace_and_nominal_list_markers()  skip_delimiters((isspace(**str) || (**str == ',') || (**str == '}')))
#define skip_whitespace_and_example_list_markers()  skip_delimiters((isspace(**str) || (**str == ',') || (**str == '}')))


// move the character position until the end of a token
#define tokenise_while(conditions) \
  while(**str && (conditions))\
    (*str)++;\
  if(**str) {\
    **str = 0;\
    (*str)++;\
  }

#define tokenise_space()    tokenise_while(!isspace(**str))
#define tokenise_quote()    tokenise_while((**str != '"' || (*(*str - 1) != '\\')))
#define tokenise_value()    tokenise_while(!isspace(**str) && (**str != ','))
#define tokenise_nominal()  tokenise_while(!isspace(**str) && (**str != ',') && (**str != '}'))


// determine whether the token is quote delimited or otherwise,
// and cleanup whitespace etc. at the end
#define tokenise(tokeniser, skipper) \
  char *start;\
  if(**str == '"') {\
    start = ++*str;\
    tokenise_quote();\
  } else {\
    start = *str;\
    tokeniser();\
  }\
  skipper();\
  return start;

inline char *tokenise_attribute_name(char **str) {
  tokenise(tokenise_space, skip_only_whitespace);
}

inline char *tokenise_nominal_value(char **str) {
  tokenise(tokenise_nominal, skip_whitespace_and_nominal_list_markers);
}

inline char *tokenise_example_value(char **str) {
  tokenise(tokenise_value, skip_whitespace_and_example_list_markers);
}

// downcase and compare two strings of a known length
inline bool matches(char *buffer, char *compare_to, int length) {
  while(length--)
    if(tolower(*(buffer++)) != *(compare_to++))
      return false;
  return true;
}

inline void skip_whitespace(char **str) {
  skip_only_whitespace();
}



DataSet::DataSet *Storage::ARFF::read() {
  DataSet::DenseDataSet *data_set = new DataSet::DenseDataSet();
  DataSet::NominalFeature *feature = NULL;
  DataSet::DenseExample *example = NULL;
  State state = relation;
  vector<bool> numeric_feature;
  char buffer[BUFFER_SIZE];
  char *line, *name, *value;
  string value_str;
  int value_index;
  fstream file;
  
  file.open(path.c_str(), fstream::in);
  
  while(file.good()) {
    file.getline(buffer, BUFFER_SIZE);
    
    switch(*buffer) {
      // blank line
      case '\0':
        break;
      
      // comments start with percent
      case '%':
        break;
      
      // transitioning states, or adding a new feature
      case '@':
        switch(state) {
          case relation:
            if(!matches(buffer, RELATION_PREFIX, RELATION_PREFIX_LENGTH))
              throw runtime_error("Expected relation declaration");
            line = buffer + RELATION_PREFIX_LENGTH;
            skip_whitespace(&line);
            data_set->name = line;
            state = attributes;
            break;
            
          case attributes:
            // check if this is an attribute declaration
            if(matches(buffer, ATTRIBUTE_PREFIX, ATTRIBUTE_PREFIX_LENGTH)) {
              line = buffer + ATTRIBUTE_PREFIX_LENGTH;
              skip_whitespace(&line);
              
              // extract the attribute's name
              name = tokenise_attribute_name(&line);
              if(!*line)
                throw runtime_error("Unexpected end of line");
              
              // add a numeric attribute
              if(matches(line, NUMERIC_TYPE, NUMERIC_TYPE_LENGTH)) {
                data_set->new_numeric_feature(name);
                numeric_feature.push_back(true);
              
              // add a nominal attribute  
              } else if(*line == '{') {
                feature = data_set->new_nominal_feature(name);
                numeric_feature.push_back(false);
                line++;
                
                while(*line) {
                  value_str = tokenise_nominal_value(&line);
                  feature->add_value(value_str);
                }
              
              // other attribute types aren't supported
              } else {
                throw runtime_error("Unknown attribute type - only numeric and nominal attributes are supported");
              }
              
            // otherwise could be the start of the data section
            } else {
              if(matches(buffer, DATA_PREFIX, DATA_PREFIX_LENGTH))
                state = data;
              else
                throw runtime_error("Expected attribute or data declaration");
            }
            break;
            
          case data:
            throw runtime_error("Unexpected declaration line, currently in data section");
        }
        break;
      
      // adding data
      default:
        if(state != data)
          throw runtime_error("Expected data section");
        
        example = data_set->new_example();
        value_index = 0;
        line = buffer;        
        
        while(*line) {
          value = tokenise_example_value(&line);
          if(numeric_feature[value_index]) {
            example->set_value(value_index, atof(value));
          } else {
            value_str = value;
            feature = (DataSet::NominalFeature *)data_set->features[value_index];
            example->set_value(value_index, feature->indexes[value_str]);
          }
          value_index++;
        }
    }
  }
  
  data_set->set_category_index(data_set->features.size() - 1);
  file.close();
  return data_set;
}

void Storage::ARFF::write(DataSet::DataSet *data_set) {
}
