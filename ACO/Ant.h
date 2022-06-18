//
// Created by Aimo on 2022/6/2.
//

#ifndef ACO_ANT_H
#define ACO_ANT_H

#include <valarray>
#include <iostream>
#include "Information.h"
#include "Graph.h"


using namespace std;


class Ant {
public:
    double Path_Length;//路径长度
    int Path[20];//路径
    int Visited[City_Num];//访问过的城市
    int Location;//当前所在城市编号
    int City_Count;//已经去过的城市数量
    int Weight;//蚂蚁的载重量

    void init();

    int ChooseNextCity(Graph g);

    void move(Graph g);

    void Compute_length(Graph g);

    void Search(Graph g);


};


#endif //ACO_ANT_H
