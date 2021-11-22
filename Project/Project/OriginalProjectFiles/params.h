#ifndef NUM_TRAINING_SAMPLES
	#define NUM_TRAINING_SAMPLES 4336
#endif

#ifndef NUM_TESTING_SAMPLES
	#define NUM_TESTING_SAMPLES 1082
#endif

#ifndef NUM_FEATURES
	#define NUM_FEATURES 43 //100 for READ = 2 //43 for READ = 1
#endif

#ifndef NUM_CLASSES
	#define NUM_CLASSES 6
#endif

#ifndef K
	#define K 20 // 3 or 4 for READ = 1
#endif

#ifndef DATA_TYPE
	#define DATA_TYPE double
#endif

#if DATA_TYPE == double
	#define MAXFPVALUE DBL_MAX
	#define MINFPVALUE DBL_MIN
#else
	#define MAXFPVALUE FLT_MAX
	#define MINFPVALUE FLT_MIN
#endif

