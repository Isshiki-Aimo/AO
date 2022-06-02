//
// Created by Aimo on 2022/6/2.
//

#include <valarray>
#include "Graph.h"

void Graph::Init() {
    for (int i = 0; i < City_Num; i++) {
        for (int j = 0; j < City_Num; j++) {
            Distance[i][j] = sqrt(pow(Correction_X[i] - Correction_X[j], 2) + pow(Correction_Y[i] - Correction_Y[j], 2));
            Pheromone[i][j] = 1.0;
        }
    }
}
