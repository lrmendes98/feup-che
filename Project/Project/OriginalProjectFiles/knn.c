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
*	SPeCS, FEUP.DEI, Porto, Portugal
*/

#include "params.h"
#include "types.h"
#include "knn.h"

#include <math.h>
#include <float.h>

/*
* Initialize the data structure to store the k best (nearest) points.
*/
void initialize_best(BestPoint *best_points, int k,  int num_features) {

    for (int i = 0; i < k; i++) {
        BestPoint *bp = &(best_points[i]);
        bp->distance = MAXFPVALUE;
        /*Point *x = &(bp->point);
        for (int j = 0; j < num_features; j++) {
            x->features[j] = 0;
        }
        x->classification_id = -1; // unknown */
		bp->classification_id = -1; // unknown
    }
}

/*
* Keep the data structure with the k nearest points updated.
* It receives a new Point and updates the k nearest accordingly.
*/
void update_best(DATA_TYPE distance, char classID, BestPoint *best_points, int k) {

    DATA_TYPE max = (DATA_TYPE) 0;
    int index = 0;

    //find the worst Point in the best_points
    for (int i = 0; i < k; i++) {
        if (best_points[i].distance > max) {
            max = best_points[i].distance;
            index = i;
        }
    }
    // if the Point is better (shorter distance) than the worst one (longer distance) in the best_points
    // update best_points substituting the worst one
    if (distance < max) {
        //copy(&best_points[index], current_point, distance, num_features);
		best_points[index].classification_id = classID;
		best_points[index].distance = distance;
    }
}

/*
* Main kNN function.
* It calculates the distances and calculates the nearest k points.
*/
void knn(Point new_point, Point *known_points, int num_points, 
		BestPoint *best_points, int k,  int num_features) {

    // calculate the Euclidean distance between the Point to classify and each one in the model
    // and update the k best points if needed
    for (int i = 0; i < num_points; i++) {
        DATA_TYPE distance = (DATA_TYPE) 0;

        // calculate the Euclidean distance
        for (int j = 0; j < num_features; j++) {
            DATA_TYPE diff = (DATA_TYPE) new_point.features[j] - (DATA_TYPE) known_points[i].features[j];
            distance += diff * diff;
        }
        distance = sqrt(distance);

        // maintains the k best points updated
        update_best(distance, known_points[i].classification_id, best_points, k);
    }
}

/*
*	Classify using the k nearest neighbors identified by the knn
*	function. The classification uses majority voting.
*
*	Note: it assumes that classes are identified from 0 to 
*	num_classes - 1.
*/
char classify(int k, BestPoint *best_points, int num_classes) {

    unsigned char histogram[num_classes];
    for (int i = 0; i < num_classes; i++) {
        histogram[i] = 0;
    }



    //DATA_TYPE min_distance = MAXFPVALUE;

	// build histogram
    for (int i = 0; i < k; i++) {

        BestPoint p = best_points[i];
        //if (best_points[i].distance < min_distance) {
        //    min_distance = best_points[i].distance;
        //}

        // SEGFAULT with float
        char aux = p.classification_id;
        unsigned int aux_casted = (unsigned int) aux;
        histogram[(unsigned int) p.classification_id] += 1;
    }

    unsigned char max = 0;
    char classification_id = 0;
    for (int i = 0; i < num_classes; i++) {

        if (histogram[i] > max) {
            max = histogram[i];
            classification_id = (char) i;
        }
    }

    return classification_id;
}

/*
* Classify a given Point (instance).
* It returns the classified class ID.
*/ 
char classifyinstance(Point new_point, int k, BestPoint *best_points, 
						int num_classes, Point *known_points, int num_points, int num_features) {

		// initialize the data structure with the best points
		// this must be done for every new instance to classify
        initialize_best(best_points, k, num_features);

        // classify the Point based on the K nearest points
        knn(new_point, known_points, num_points, best_points, k, num_features);
        return classify(k, best_points, num_classes);
}