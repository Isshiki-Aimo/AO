//
// Created by Aimo on 2022/6/2.
//

#ifndef ACO_CVRP_H
#define ACO_CVRP_H
#include "Ant.h"


class CVRP//容量受限的车辆路径问题
{
public:
    Ant ants[Ant_num];
    Ant best_ant;//记录最优的蚂蚁
    void Init();

    void Update(Graph g);

    void Search(Graph g);

};
#endif //ACO_CVRP_H
