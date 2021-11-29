#ifndef KNN_PARAMS_H //KNN_PARAMS_H
#define KNN_PARAMS_H

#include <float.h>

#define NUM_TRAINING_SAMPLES 8004

#define NUM_TESTING_SAMPLES 1996

#define NUM_FEATURES 100

#define NUM_CLASSES 8

#define K 20 //20 // 3 or 20 for READ = 1 (some authors consider K=sqrt(NUM_TRAINING_INSTANCES) = 65

#define DT 1 // 1: double; 2: float; 3: not used for know

#if DT == 1	//double
	#define DATA_TYPE double
	#define MAX_FP_VAL DBL_MAX
	#define MIN_FP_VAL -DBL_MAX
#elif DT == 2 //float
	#define DATA_TYPE float
	#define MAX_FP_VAL FLT_MAX
	#define MIN_FP_VAL -FLT_MAX
#else
	#define DATA_TYPE unknown
	#define MAX_FP_VAL unknown
	#define MIN_FP_VAL unknown
#endif

#if NUM_CLASSES > 128
	#define CLASS_ID_TYPE short // consider 0..32767 classes and -1 for unknown
#else
	#define CLASS_ID_TYPE char // consider 0..127 classes and -1 for unknown
#endif


#endif //KNN_PARAMS_H