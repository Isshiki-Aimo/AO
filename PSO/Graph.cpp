//
// Created by Aimo on 2022/5/24.
//

#include "Graph.h"

void Graph::ComputeDistance() {
    for (int i=0;i<CityNum;i++) {
        for (int j=0;j<CityNum;j++) {
            if (i==j) {
                Distance[i][j]=0;
            } else {
                Distance[i][j]=Distance[j][i]=sqrt(pow(City[i].x-City[j].x,2)+pow(City[i].y-City[j].y,2));
            }
        }
    }

}
