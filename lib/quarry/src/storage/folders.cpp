#include "folders.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

static char *file_data = NULL;
static int file_data_size = 0;


void Storage::Folders::load_directory(string path, DataSet::SparseDataSet *data_set, int category_index) {
  DataSet::SparseExample *example;
  DIR *dir = opendir(path.c_str());
  struct dirent *dp;
  char *name;
  string newpath;
  struct stat info;
  FILE *file;
  int file_length;
  
  while((dp = readdir(dir))) {
    // ignore files starting with a dot
    name = dp->d_name;
    if(*name == '.')
      continue;
    
    // ensure this is a file, not a folder
    newpath = path + "/" + name;
    stat(newpath.c_str(), &info);
    if(info.st_mode & S_IFDIR)
      continue;
    
    // determine if the file_data buffer is large enough to hold this file 
    file = fopen(newpath.c_str(), "rb");
    fseek(file, 0, SEEK_END);
    file_length = ftell(file) + 1;
    rewind(file);
    
    if(file_data_size < file_length) {
      if(file_data != NULL)
        free(file_data);
      file_data = (char *)malloc(file_length);
      file_data_size = file_length;
    }
    
    // read into the buffer
    fread(file_data, 1, file_length - 1, file);
    file_data[file_length] = 0;
    fclose(file);
    
    // insert a new example into the dataset
    example = pipeline->process_text(data_set, file_data);
    example->set_category_index(data_set, category_index);
  }
  
  closedir(dir);
}

DataSet::DataSet *Storage::Folders::read() {
  DataSet::SparseDataSet *data_set = new DataSet::SparseDataSet();
  DIR *dir = opendir(path.c_str());
  struct dirent *dp;
  char *name;
  string newpath;
  struct stat info;
  
  // create an initial feature "Category"
  DataSet::NominalFeature *categories = data_set->new_nominal_feature("Category");
  data_set->set_category_index(0);
  int category_index = 0;
  
  while((dp = readdir(dir))) {
    // ignore files starting with a dot
    name = dp->d_name;
    if(*name == '.')
      continue;
    
    // ensure this is a folder
    newpath = path + "/" + name;
    stat(newpath.c_str(), &info);
    if(info.st_mode & S_IFDIR) {
      category_index = categories->value_index(string(name));
      load_directory(newpath, data_set, category_index);
    }
  }
  
  return data_set;
}

void Storage::Folders::write(DataSet::DataSet *data_set) {
}
