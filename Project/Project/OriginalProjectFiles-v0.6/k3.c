CLASS_ID_TYPE classify_k3(int k, BestPoint *best_points, int num_classes) {

    if (best_points[1].classification_id == best_points[2].classification_id) return best_points[1].classification_id;
    else return best_points[0].classification_id;

}


void update_best(DATA_TYPE distance, CLASS_ID_TYPE classID, BestPoint *best_points) {

    DATA_TYPE max = (DATA_TYPE) 0.0;
    int index = 0;


    if (distance > best_points[2].distance) {
        if (distance > best_points[1].distance)){
            if (distance > best_points[0].distance)){
                best_points[2].distance = best_points[1].distance;
                best_points[1].distance = best_points[0].distance;
                best_points[0].distance = distance;

            }
            else {
                best_points[2].distance = best_points[1].distance;
                best_points[1].distance = distance;
            }
        }
        else {
            best_points[2].distance = distance;
        }
    }
    else return;
}