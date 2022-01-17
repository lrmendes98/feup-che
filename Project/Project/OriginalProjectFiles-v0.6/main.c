/**
*	FEUP.DEI, v0.6 November 2021
*
*	Scenario A1, WISDM dataset: without using files for input data
*	Files for scenario must be copied from scenario-wisdm/
*	READ 1
*	NUM_TRAINING_SAMPLES 4336
*	NUM_TESTING_SAMPLES 1082
*	NUM_FEATURES 100 
*	NUM_CLASSES 6
*	TIMMING 0 or *1*
*	ACCURACY 0 or *1*
*	NORMALIZE 0 or *1*  // use 1
*	K = 3 or 20
* 	DATA_TYPE = float or double
*
*	Scenario A2, generated dataset: without using files for input data
*	Files for scenario must be copied from scenario-gen100x8x10000/
*	READ 1
*	NUM_TRAINING_SAMPLES 8004
*	NUM_TESTING_SAMPLES 1996
*	NUM_FEATURES 100
*	NUM_CLASSES 8
*	TIMMING 0 or *1*
*	ACCURACY 0 or *1*
*	NORMALIZE 0 or *1* // use 1
*	K = 20
* 	DATA_TYPE = float or double
*
*	Scenario A3, generated dataset: without using files for input data
*	Files for scenario must be copied from scenario-gen100x8x50000/
*	READ 1
*	NUM_TRAINING_SAMPLES 40002
*	NUM_TESTING_SAMPLES 9998
*	NUM_FEATURES 100
*	NUM_CLASSES 8
*	TIMMING 0 or *1*
*	ACCURACY 0 or *1*
*	NORMALIZE 0 or *1* // use 1
*	K = 20
* 	DATA_TYPE = float or double
*
* 	Scenario B: using random data
*	READ 3
*	NUM_TRAINING_SAMPLES *not needed*
*	NUM_TESTING_SAMPLES *not needed*
*	NUM_FEATURES *must be defined* 
*	NUM_CLASSES *name of the file is used to identify a specific configuration*
*	TIMMING 0 or *1*
*	ACCURACY *0* or 1
*	NORMALIZE *0* or 1 // use 1
*
* 	Scenario C: using files for input data
*	READ 2
*	NUM_TRAINING_SAMPLES *not needed*
*	NUM_TESTING_SAMPLES *not needed*
*	NUM_FEATURES 100 
*	NUM_CLASSES *from file*
*	TIMMING 0 or *1*
*	ACCURACY *0* or 1
*	NORMALIZE *0* or 1 // use 1
*
*/

#ifndef TIMMING
	#define TIMMING 1 // 0: without; 1: Linux/Windows, 2: specific timers (not implemented)
#endif

#ifndef READ
	#define READ 1 // 1: all embedded in program; 2: read from .dat; 3: random data
#endif

#ifndef VERIFY
	#define VERIFY 0 	// 0: none verification; 
						// 1: to verify if the results are according to the ones expected
						// only for READ = 1, scenario A1, or READ = 2
#endif

#ifndef ACCURACY
	#define ACCURACY 1 	// 0: no; 1: to report the accuracy of the classification
						// only used for READ = 1 or READ = 2
#endif

#ifndef NORMALIZE
	#define NORMALIZE 1 // 0: nothing; 1: minmax normalization of features
#endif

#include <stdio.h>
#include <omp.h>

#include "params.h"
#include "types.h"
#include "utils.h"
#include "io.h"
#include "knn.h"

#if TIMMING == 1
	#include "timer.h"
#endif


#if READ == 1 // data embedded in program
	
	Point known_points1[NUM_TRAINING_SAMPLES] = {
							#include "train.dat"
						}; //{{{1,2,3,4,5},'a'}};
	Point *known_points = known_points1;
	
	Point new_points1[NUM_TESTING_SAMPLES] = {
						#include "test.dat"
						}; //{{{1,2,3,4,5},'a'}};
	Point *new_points = new_points1;
	
#else // data read from files or randomly initialized
	Point *known_points = NULL; // The points representing the instances in the model
	Point *new_points = NULL; // The points to be classified
#endif

#if defined VERIFY  // verify if classifications are still the original
#if READ == 1
	unsigned char key[NUM_TESTING_SAMPLES] = {
		#if K == 20
			#include "key-READ1-k20.dat"
		#elif K == 3
			#include "key-READ1-k3.dat"
		#endif
	};
#else
	CLASS_ID_TYPE *key = NULL; // The classification key
#endif
#endif


int main(int argc, char **argv) {

    int num_points, num_classes, num_new_points, k;
	
	const int num_features = NUM_FEATURES;
	
	#if READ == 1 // data embedded in program
		printf("Data points initialized with WISDM dataset...\n");
		k = K;
        num_classes = NUM_CLASSES;
        num_points = NUM_TRAINING_SAMPLES;
        num_new_points = NUM_TESTING_SAMPLES;
	#elif READ == 2  // data read from .dat file
		printf("Initializing data points from .dat ...\n");
		read_data(argc, argv, &num_points, &num_classes, &num_new_points, &k, &known_points, 
		&new_points, &key, num_features);
		printf("Initialization done.\n\n");
	#elif READ == 3  // data randomly initialized
		printf("Initializing data points with random data ...\n");
		generate_random_data(argc, argv, &num_points, &num_classes, &num_new_points, &k, 
		&known_points, &new_points, &key, num_features);
		printf("Initialization done.\n\n");
	#endif
	
	#if NORMALIZE == 1 // minmax normalization
		DATA_TYPE min[num_features];		
		DATA_TYPE max[num_features];
		
		// determine min and max from known points
		minmax(min, max, num_points, known_points, num_features); 
		
		// normalize known points
		minmax_normalize(min, max, num_points, known_points, num_features);
		
		// normalize new points
		minmax_normalize(min, max, num_new_points, new_points, num_features);
	#endif
	
    printf("Executing kNN...\n");

	#if TIMMING == 1
		Timer *timer = timer_init();
		timer_start(timer);
	#endif

	BestPoint best_points[k]; // Array with the k nearest points to the Point to classify

	#if ACCURACY == 1 && READ != 3
		int fail = 0; // count the number of test instances incorrectly classified
	#endif
	

	// converter new_points para SoA known_points e new_points
	Known_Points_SoA known_points_soa;
	for (int i = 0; i < NUM_TRAINING_SAMPLES; i++) {
		known_points_soa.features[i] = known_points[i].features;
		known_points_soa.classification_id[i] = known_points[i].classification_id;
	}

	Points_SoA new_points_soa;
	for (int i = 0; i < NUM_TESTING_SAMPLES; i++) {
		new_points_soa.features[i] = new_points[i].features;
		new_points_soa.classification_id[i] = new_points[i].classification_id;
	}



	// loop over the input instances to classify.
	// Note that depending on the application this can be strreaming instances,
	// instances arriving as streaming data, etc.
	// Here assume that the loop below needs run in serial mode and the 
	// value of num_new_point is just to test
    for (int i = 0; i < num_new_points; i++) {

        CLASS_ID_TYPE class = classifyinstance(new_points_soa.features[i], new_points_soa.classification_id[i], 
										k, best_points, num_classes, known_points, &known_points_soa, num_points, num_features);
		//if(i==0) show_point(new_points[i],num_features);
		
		#if ACCURACY == 1 && READ != 3
			if(new_points[i].classification_id != class) fail++;
		#endif
		
		new_points[i].classification_id = class;
		//printf("%d,%d\n",new_points[i].classification_id, class);
		//printf("%d,",class);
		// printf("class id: %d\n",class);
    }
	

	#if TIMMING == 1
		timer_stop(timer);
	#endif
	
    printf("kNN done.\n\n");
	
    printf("kNN: number of classes = %d\n", num_classes);
    printf("kNN: number of training instances = %d\n", num_points);
    printf("kNN: number of features = %d\n", num_features);
    printf("kNN: k = %d\n", k);
	
    printf("kNN: number of classified instances = %d\n", num_new_points);
	
	#if ACCURACY == 1 && READ != 3
		printf("kNN: number of classifications wrong = %d\n", fail);
		printf("kNN: number of classifications right = %d\n", num_new_points-fail);
		printf("kNN: accuracy = %.2f %c\n\n", 100*(float)(num_new_points-fail)/(float) num_new_points, '%');
	#endif

	#if VERIFY == 1 && READ != 3
		verify_results(num_new_points, new_points, key);
	#endif

	#if TIMMING == 1
		const double time = timer_get_s(timer);
		printf("\nTime:  %.4f s\n", time);
		#if READ == 2
			printf("Score: %d\n", get_reference_score(time, num_points));
		#endif
		timer = timer_destroy(timer);
	#endif
	
	#if READ != 1
		free(new_points);
		free(known_points);
	#endif
	
	#if READ == 2 && VERIFY == 1	
		free(key);
	#endif

    return 0;
}