//
// Created by Aimo on 2022/5/24.
//

#ifndef PSO_GRAPH_H
#define PSO_GRAPH_H
#include "Coordinate.h"
#include "Information.h"
#include <iostream>

using namespace std;


class Graph {
public:
    Coordinate *city[CityNum];
    float Distance[CityNum][CityNum];
    void ComputeDistance();
    void ShowDistance();

};


#endif //PSO_GRAPH_H
