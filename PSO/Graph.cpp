//
// Created by Aimo on 2022/5/24.
//

#include <valarray>
#include "Graph.h"

void Graph::ComputeDistance() {
    float x, y;
    for (int i = 0; i < CityNum; i++) {
        x = City_x[i];
        y = City_y[i];
        city[i] = new Coordinate(x, y);
    }

    for (int i = 0; i < CityNum; i++) {
        for (int j = 0; j < CityNum; j++) {
            if (i == j) {
                Distance[i][j] = 0;
            } else {
                Distance[i][j] = Distance[j][i] = sqrt(
                        pow(city[i]->x - city[j]->x, 2) + pow(city[i]->y - city[j]->y, 2));
            }
        }
    }

}

void Graph::ShowDistance() {
    for (int i = 0; i < CityNum; i++) {
        for (int j = 0; j < CityNum; j++) {
            cout << Distance[i][j] << " ";
        }
        cout << endl;
    }
}




