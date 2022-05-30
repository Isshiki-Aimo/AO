//
// Created by Aimo on 2022/5/24.
//

#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <iostream>
#include "Information.h"
#include <math.h>
#include "Coordinate.h"
#include "Graph.h"

class Particle {
public:
    int *x; // 粒子的位置
    int *v; // 粒子的速度
    double fitness; // 粒子的适应度

    double Evaluate(int *x)//计算粒子适应值的函数
    {
        double fitnessvalue = 0;
        for (int i = 0; i < CityNum - 1; i++)
            fitnessvalue += Map_City.Distance[x[i] - 1][x[i + 1] - 1];
        fitnessvalue += Map_City.Distance[x[CityNum - 1] - 1][x[0] - 1];
        return fitnessvalue;
    }

//    void Init() {
//        x = new int[CityNum];
//        v = new int[CityNum];
//        int *order = Random_Order(CityNum);
//        for (int i = 0; i < CityNum; i++) {
//            x[i] = order[i];
//            fitness = Evaluate(x,Map_City);
//        }
//        for (int i = 0; i < CityNum; ++i) {
//            v[i] = rand() % 3 - 1;
//        }
//    }

};


#endif //PSO_PARTICLE_H
