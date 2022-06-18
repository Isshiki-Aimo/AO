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
    double Path_Length;//·������
    int Path[20];//·��
    int Visited[City_Num];//���ʹ��ĳ���
    int Location;//��ǰ���ڳ��б��
    int City_Count;//�Ѿ�ȥ���ĳ�������
    int Weight;//���ϵ�������

    void init();

    int ChooseNextCity(Graph g);

    void move(Graph g);

    void Compute_length(Graph g);

    void Search(Graph g);


};


#endif //ACO_ANT_H
