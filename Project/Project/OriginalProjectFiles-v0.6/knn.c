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

#include <math.h>

#ifndef NDEBUG
#define NDEBUG // disable assertions
#endif
#include <assert.h>

#include "knn.h"

/*
* Initialize the data structure to store the k best (nearest) points.
*/
void initialize_best(BestPoint *best_points) {

    for (int i = 0; i < 3; i++) {
        BestPoint *bp = &(best_points[i]);
        bp->distance = MAX_FP_VAL;
		//printf("initialize distance %e\n", bp->distance);
        bp->classification_id = (CLASS_ID_TYPE) -1; // unknown
    }
}

/*
* Keep the data structure with the k nearest points updated.
* It receives a new Point and updates the k nearest accordingly.
*/
void update_best(DATA_TYPE distance, CLASS_ID_TYPE classID, BestPoint *best_points) {

   if (distance < (DATA_TYPE)best_points[2].distance) {
        if (distance < best_points[1].distance) {
            if (distance < best_points[0].distance) {
                best_points[2].distance = best_points[1].distance;
                best_points[2].classification_id = best_points[1].classification_id;
                best_points[1].distance = best_points[0].distance;
                best_points[1].classification_id = best_points[0].classification_id;
                best_points[0].distance = distance;
                best_points[0].classification_id = classID;

            }
            else {
                best_points[2].distance = best_points[1].distance;
                best_points[2].classification_id = best_points[1].classification_id;
                best_points[1].distance = distance;
                best_points[1].classification_id = classID;
            }
        }
        else {
            best_points[2].distance = distance;
            best_points[2].classification_id = classID;
        }
    }
}

/*
* Main kNN function.
* It calculates the distances and calculates the nearest k points.
*/
void knn(Point new_point, Point *known_points, int num_points, 
		BestPoint *best_points, int num_features) {

    // calculate the Euclidean distance between the Point to classify and each one in the model
    // and update the k best points if needed
    for (int i = 0; i < num_points; i++) {
        DATA_TYPE distance = (DATA_TYPE) 0.0;

        // calculate the Euclidean distance
        for (int j = 0; j < num_features; j++) {
            DATA_TYPE diff = (DATA_TYPE) new_point.features[j] - (DATA_TYPE) known_points[i].features[j];
            distance += diff * diff;
        }
        //distance = sqrtf(distance);

        update_best(distance, known_points[i].classification_id, best_points);
    }
}

/*
*	Classify using the k nearest neighbors identified by the knn
*	function. The classification uses majority voting.
*/
CLASS_ID_TYPE classify(BestPoint *best_points) {

    if (best_points[1].classification_id == best_points[2].classification_id) return best_points[1].classification_id;
    else return best_points[0].classification_id;

}


/*
* Classify a given Point (instance).
* It returns the classified class ID.
*/ 
CLASS_ID_TYPE classifyinstance(Point new_point, BestPoint *best_points, 
						 Point *known_points, int num_points, int num_features) {

    // printf("Number of features: %d", num_features);
	// initialize the data structure with the best points
	// this must be done for every new instance to classify
    initialize_best(best_points);

    // classify the Point based on the K nearest points
    knn(new_point, known_points, num_points, best_points, num_features);
    
	// invoke and return the classification. the classify function could be part of
	// the knn function
	CLASS_ID_TYPE classID = classify(best_points);
	
	return classID;
}