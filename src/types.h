
#ifndef KNN_TYPES_H
#define KNN_TYPES_H

#include "params.h"

typedef struct {
    DATA_TYPE features[NUM_TESTING_SAMPLES*NUM_FEATURES];
	CLASS_ID_TYPE classification_id[NUM_TESTING_SAMPLES];
} Points_SoA;

typedef struct {
    DATA_TYPE features[NUM_TRAINING_SAMPLES*NUM_FEATURES];
	CLASS_ID_TYPE classification_id[NUM_TRAINING_SAMPLES];
} Known_Points_SoA;

typedef struct {
    DATA_TYPE features[NUM_FEATURES];
    CLASS_ID_TYPE classification_id;
} Point;

typedef struct {
    CLASS_ID_TYPE classification_id;
    DATA_TYPE distance;
} BestPoint;

typedef struct {
    CLASS_ID_TYPE classification_id[K];
    DATA_TYPE distance[K];
} BestPoint_SoA;

#endif //KNN_TYPES_H
