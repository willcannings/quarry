#include "folders.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

static void *file_data = NULL;
static int file_data_size = 0;

void traverse(string path, DataSet::DataSet *data_set) {
  DIR *dir = opendir(path.c_str());
  struct dirent *dp;
  char *name;
  string newpath;
  struct stat info;
  FILE *file;
  int file_length;
  
  while(dp = readdir(dir)) {
    name = dp->d_name;
    
    if(name[0] != '.') {
      newpath = path + "/" + name;
      stat(newpath.c_str(), &info);
      
      if(info.st_mode & S_IFDIR) {
        // traverse directories
        traverse(newpath, data_set);
      
      } else {
        // determine if the file_data buffer is large enough to hold this file
        file = fopen(newpath.c_str(), "rb");
        fseek(file, 0, SEEK_END);
        file_length = ftell(file) + 1;
        rewind(file);
        
        if(file_data_size < file_length) {
          if(file_data != NULL)
            free(file_data);
          file_data = malloc(file_length);
          file_data_size = file_length;
        }
        
        fread(file_data, 1, file_length, file);
        fclose(file);
        
        hash_set((void *)name, strlen(name), file_data, file_length);
        
        if(((++file_count) % 10000) == 0)
          printf("processed: %i\n", file_count);
      }
    }
  }
  
  //if(file_data)
  //  free(file_data);
  closedir(dir);
  
}



void load_directory(string path, DataSet::DataSet *data_set) {
  
}


S_ISREG



DataSet::DataSet *Storage::Folders::read() {
  DataSet::DataSet *data_set = new DataSet::DataSet();
  DataSet::Example *example = NULL;
  return data_set;
}

void Storage::Folders::write(DataSet::DataSet *data_set) {
}
