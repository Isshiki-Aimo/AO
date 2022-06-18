//
// Created by Aimo on 2022/6/2.
//

#include <iostream>
#include<random>
#include<ctime>
#include "CVRP.h"

using namespace std;


int main() {
    Graph g{};
    g.Init();
    CVRP cvrp{};
    srand((unsigned) time(NULL));
    cvrp.Init();
    cvrp.Search(g);
}