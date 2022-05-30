//
// Created by Aimo on 2022/5/30.
//

#ifndef PSO_PSO_H
#define PSO_PSO_H

#include "Particle.h"


class PSO {
public:
    Particle *oldparticle;
    Particle *pbest, gbest;
    double c1, c2, w;
    int Itetime;
    int popsize;
    float vmax = 1, vmin = -1;

    void Init(int Pop_Size, int itetime, double C1, double C2, double W, Graph Map_City);

    void Show();

    void PSO_TSP(int Pop_size, int itetime, double C1, double C2, double W, float Vlimitabs, Graph Map_City);

};


#endif //PSO_PSO_H
