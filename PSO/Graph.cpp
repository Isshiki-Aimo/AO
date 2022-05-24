//
// Created by Aimo on 2022/5/24.
//

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

int *Graph::Random_Order(int city_num) {
    int *order;
    order = new int[city_num];
    int j = 0;
    while (j < city_num) {
        while (true) {
            int flag = -1;
            int temp = rand() % city_num + 1;
            if (j > 0) {
                int k = 0;
                for (; k < j; k++) {
                    if (temp == *(order + k))break;
                }
                if (k == j) {
                    *(order + j) = temp;
                    flag = 1;
                }
            } else {
                *(order + j) = temp;
                flag = 1;
            }
            if (flag == 1)break;
        }
        j++;
    }
    return order;
}


