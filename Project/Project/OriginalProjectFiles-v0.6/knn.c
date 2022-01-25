/**
*	k-NN
*
*	Versions 
*	- v0.1, December 2016
*	- v0.2, November 2019
*	- v0.5, November 2021
*	
*	by João MP Cardoso
*	Email: jmpc@fe.up.pt
*	
*	SPeCS, FEUP.DEI, University of Porto, Portugal
*/

#include "types.h"
#include <math.h>

#ifndef NDEBUG
#define NDEBUG // disable assertions
#endif
#include <assert.h>

#include "knn.h"

/*
* Initialize the data structure to store the k best (nearest) points.
*/
void initialize_best(BestPoint_SoA *best_points, int k, int num_features) {
    for (int i = 0; i < k; i++) {
        // BestPoint *bp = &(best_points[i]);
        best_points->distance[i] = MAX_FP_VAL;
		//printf("initialize distance %e\n", bp->distance);
        best_points->classification_id[i] = (CLASS_ID_TYPE) -1; // unknown
    }
}

/*
* Keep the data structure with the k nearest points updated.
* It receives a new Point and updates the k nearest accordingly.
*/
void update_best(DATA_TYPE distance, CLASS_ID_TYPE classID, 
            BestPoint_SoA *restrict best_points, int k) {

    DATA_TYPE max = (DATA_TYPE) 0.0;
    int index = 0;

    //find the worst Point in the best_points, i.e., the point with the longest distance
    for (int i = 0; i < k; i++) {
        if (best_points->distance[i] > max) {
            max = best_points->distance[i];
            index = i;
        }
    }
    // if the Point is better (shorter distance) than the worst one (longest distance) 
	// in the best_points update best_points substituting the worst one
    if (distance < max) {
		best_points->classification_id[index] = classID;
		best_points->distance[index] = distance;
		//printf("update best: %d\n",classID);
    }
}

/*
* Main kNN function.
* It calculates the distances and calculates the nearest k points.
*/
void knn(DATA_TYPE* new_point_features, CLASS_ID_TYPE new_point_classification_id, 
            Known_Points_SoA *restrict known_points_soa, int num_points, 
		    BestPoint_SoA *restrict best_points, int k, int num_features) {

    DATA_TYPE distance = (DATA_TYPE) 0.0;
    DATA_TYPE diff;
    int j;
    
    #pragma omp parallel for \
        private(j,diff) reduction(+:distance)

    // calculate the Euclidean distance between the Point to classify and each one in the model
    // and update the k best points if needed
    for (int i = 0; i < num_points; i++) {
        distance = (DATA_TYPE) 0.0;
        DATA_TYPE* known_point_features = known_points_soa->features[i];
        CLASS_ID_TYPE known_point_classification_id = known_points_soa->classification_id[i];

        // calculate the Euclidean distance
        for (j = 0; j < num_features; j++) {
            diff = (DATA_TYPE) new_point_features[j] - 
                                (DATA_TYPE) known_point_features[j];
            distance += diff * diff;
        }
        distance = sqrt(distance);

        update_best(distance, known_point_classification_id, best_points, k);		
    }
}

/*
*	Classify using the k nearest neighbors identified by the knn
*	function. The classification uses majority voting.
*
*	Note: it assumes that classes are identified from 0 to 
*	num_classes - 1.
*/
CLASS_ID_TYPE classify(int k, BestPoint_SoA *best_points, int num_classes) {

    unsigned CLASS_ID_TYPE histogram[num_classes];  // maximum is the value of k
    for (int i = 0; i < num_classes; i++) {
        histogram[i] = 0;
    }

    //DATA_TYPE min_distance = MAX_FP_VAL;

	// build histogram
    for (int i = 0; i < k; i++) {

        int class_id = best_points->classification_id[i];
        //if (best_points[i].distance < min_distance) {
        //    min_distance = best_points[i].distance;
        //}

		assert(class_id != -1);
		
        histogram[class_id] += 1;
    }

    unsigned CLASS_ID_TYPE max = 0; // maximum is the highest class id +1
    CLASS_ID_TYPE classification_id = 0;
    for (int i = 0; i < num_classes; i++) {

        if (histogram[i] > max) {
            max = histogram[i];
            classification_id = (CLASS_ID_TYPE) i;
        }
    }

    return classification_id;
}

/*
* Classify a given Point (instance).
* It returns the classified class ID.
*/ 
CLASS_ID_TYPE classifyinstance(DATA_TYPE* new_point_features, CLASS_ID_TYPE new_point_classification_id, 
                        int k, BestPoint_SoA *best_points, int num_classes, 
                        Known_Points_SoA *known_points_soa, int num_points, int num_features) {

	// initialize the data structure with the best points
	// this must be done for every new instance to classify
    initialize_best(best_points, k, num_features);

    // classify the Point based on the K nearest points
    knn(new_point_features, new_point_classification_id, known_points_soa, num_points, best_points, k, num_features);
    
	// invoke and return the classification. the classify function could be part of
	// the knn function
	CLASS_ID_TYPE classID = classify(k, best_points, num_classes);
	
	return classID;
}