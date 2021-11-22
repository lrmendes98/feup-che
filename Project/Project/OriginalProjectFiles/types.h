
#ifndef KNN_TYPES_H
#define KNN_TYPES_H

#include "params.h"

typedef struct {
    DATA_TYPE features[NUM_FEATURES];
    char classification_id;
} Point;

typedef struct {
    char classification_id;
    DATA_TYPE distance;
} BestPoint;

#endif //KNN_TYPES_H
