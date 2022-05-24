//
// Created by Aimo on 2022/5/24.
//
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Particle.h"
#include "Graph.h"
#include "Information.h"

using namespace std;

int main() {
    Graph graph;
    int *a = graph.Random_Order(CityNum);
    for (int i = 0; i < CityNum; ++i) {
        cout << a[i] << " ";
    }

    return 0;
}
