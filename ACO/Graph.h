//
// Created by Aimo on 2022/6/2.
//

#ifndef ACO_GRAPH_H
#define ACO_GRAPH_H

#include "Information.h"


class Graph {
public:

    double Distance[City_Num][City_Num];//�������
    double Pheromone[City_Num][City_Num];//��Ϣ�ؾ���
    void Init();
};


#endif //ACO_GRAPH_H
