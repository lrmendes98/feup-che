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

#ifndef KNN_H
#define KNN_H

#include "params.h"
#include "types.h"

void initialize_best(BestPoint *best_points, int k,  int num_features);

void update_best(DATA_TYPE distance, CLASS_ID_TYPE classID, 
				BestPoint *best_points, int k);


void knn(Point new_point, Point *known_points, int num_points, BestPoint *best_points, 
		int k,  int num_features);

CLASS_ID_TYPE classify(int k, BestPoint *best_points, int num_classes);

CLASS_ID_TYPE classifyinstance(Point new_point, int k, BestPoint *best_points, 
						int num_classes, Point *known_points, int num_points,
						int num_features);

#endif
