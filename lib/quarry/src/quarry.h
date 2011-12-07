#include "data_set/data_set.h"
#include "data_set/dense/dense_data_set.h"
#include "data_set/sparse/sparse_data_set.h"
#include "data_set/example.h"
#include "data_set/dense/dense_example.h"
#include "data_set/sparse/sparse_example.h"
#include "data_set/feature.h"
#include "data_set/features/nominal_feature.h"
#include "data_set/features/numeric_feature.h"

#include "classifier/classifier.h"
#include "classifier/naive_bayes/naive_bayes_classifier.h"

#include "metrics/confusion_matrix.h"

#include "preprocessing/text/text_pipeline.h"
#include "preprocessing/examples/example_preprocessor.h"
#include "preprocessing/examples/weights/binary_weight.h"
#include "preprocessing/examples/weights/local_weight.h"

#include "model/model.h"

#include "storage/storage.h"
#include "storage/arff.h"
#include "storage/folders.h"
#include "storage/binary.h"

// function to show to mkmf this library exists
void mkmf_marker();
