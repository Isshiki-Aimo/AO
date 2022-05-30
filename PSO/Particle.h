//
// Created by Aimo on 2022/5/24.
//

#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <iostream>
#include <cmath>
#include "Graph.h"

class Particle {
public:
    int *x; // 粒子的位置
    int *v; // 粒子的速度
    double fitness; // 粒子的适应度


    double Evaluate(int *x, Graph Map_City);//计算粒子适应值的函数


    void Init(Graph Map_City);

    void show();

    void repair(Particle p);//修复序列


};


#endif //PSO_PARTICLE_H
