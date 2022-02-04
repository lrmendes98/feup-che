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

void initialize_best(BestPoint_SoA *best_points, int k,  int num_features);

void update_best(DATA_TYPE distance, CLASS_ID_TYPE classID, 
				BestPoint_SoA *best_points, int k);


void knn(DATA_TYPE* new_point_features, CLASS_ID_TYPE new_point_classification_id, 
		Known_Points_SoA *known_points_soa, int num_points, 
		BestPoint_SoA *best_points, int k,  int num_features);

CLASS_ID_TYPE classify(int k, BestPoint_SoA *best_points, int num_classes);

CLASS_ID_TYPE classifyinstance(DATA_TYPE* new_point_features, 
						CLASS_ID_TYPE new_point_classification_id,
						BestPoint_SoA *best_points, int num_classes, 
						Known_Points_SoA *known_points_soa, int num_points, 
						int num_features);

#endif
