#ifndef __binary_h__
#define __binary_h__
#include "storage/storage.h"
#include "data_set/dense/dense_data_set.h"
#include "data_set/sparse/sparse_data_set.h"
#include "classifier/naive_bayes/naive_bayes_classifier.h"
#include <fstream>
using namespace std;

namespace Storage {
  class Binary : public Storage {
    string path;
    fstream file;
    
    // helpers
    void open_for_reading();
    void open_for_writing();
    
    // low level IO
    void write_string(string str);
    string read_string();
    void write_int(int number);
    int read_int();
    void write_mark(uint32_t mark);
    uint32_t read_mark();
    void write_bool(bool value);
    bool read_bool();
    
    // these templated functions are used outside this class,
    // so their definition needs to be in this header file for
    // each version of the function to be generated
    template<class T> vector<T> *read_vector() {
      vector<T> *values = new vector<T>();
      int size = read_int();
      values->reserve(size);
      T value;

      for(int i = 0; i < size; i++) {
        file.read((char *)(&value), sizeof(T));
        values->push_back(value);
      }

      return values;
    }
    
    template<class T> void write_vector(vector<T> *values) {
      uint32_t size = values->size();
      write_int(size);

      for(int i = 0; i < size; i++)
        file.write((char *)(&values->at(i)), sizeof(T));
    }
    
    // serialisation
    DataSet::DataSet *read_data_set();
    void write_data_set(DataSet::DataSet *data_set);
    Classifier::Classifier *read_classifier(DataSet::DataSet *data_set);
    void write_classifier(Classifier::Classifier *classifier);
    Preprocessing::Text::TextPipeline *read_text_pipeline();
    void write_text_pipeline(Preprocessing::Text::TextPipeline *pipeline);
    
  public:
    bool should_write_examples;
    Binary(string path) : path(path), should_write_examples(false) {}
    bool get_write_examples()           { return should_write_examples; }
    void set_write_examples(bool write) { should_write_examples = write;}
    
    DataSet::DataSet *read();
    Model::Model *read_model();
    void write(DataSet::DataSet *data_set);
    void write_model(Model::Model *model);
    
    friend class Preprocessing::Text::TextPipeline;
    friend class Classifier::Classifier;
    friend class Classifier::NaiveBayesClassifier;
  };
}

#endif
