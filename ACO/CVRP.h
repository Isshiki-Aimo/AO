//
// Created by Aimo on 2022/6/2.
//

#ifndef ACO_CVRP_H
#define ACO_CVRP_H
#include "Ant.h"


class CVRP//�������޵ĳ���·������
{
public:
    Ant ants[Ant_num];
    Ant best_ant;//��¼���ŵ�����
    void Init();

    void Update(Graph g);

    void Search(Graph g);

};
#endif //ACO_CVRP_H
