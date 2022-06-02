//
// Created by Aimo on 2022/5/24.
//
#include <cstdlib>
#include <string>
#include <ctime>
#include "Graph.h"
#include "PSO.h"

using namespace std;

int main() {

    srand(time(NULL));
    Graph graph{};
    graph.ComputeDistance();
    PSO pso;
    pso.PSO_TSP(30, 500, 2, 2, 0.8, 3.0, graph);
    return 0;
}
