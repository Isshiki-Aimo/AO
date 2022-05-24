//
// Created by Aimo on 2022/5/24.
//

#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <iostream>
#include "Information.h"
#include <math.h>
#include "coordinate.h"
#include "Graph.h"

class Particle {
public:
    int *x; // 粒子的位置
    int *v; // 粒子的速度
    double fitness; // 粒子的适应度

    void Init() {
        x = new int[CityNum];
        v = new int[CityNum];


    }
};


#endif //PSO_PARTICLE_H
