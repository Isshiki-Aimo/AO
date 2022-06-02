//
// Created by Aimo on 2022/5/30.
//

#include "PSO.h"

void PSO::Init(int Pop_Size, int itetime, double C1, double C2, double W, Graph Map_City) {
    cout << "start init" << endl;
    Itetime = itetime;
    c1 = C1;
    c2 = C2;
    w = W;
    popsize = Pop_Size;
    oldparticle = new Particle[popsize];
    pbest = new Particle[popsize];
    for (int i = 0; i < popsize; i++) {
        oldparticle[i].Init(Map_City);
        pbest[i].Init(Map_City);
        for (int j = 0; j < CityNum; j++) {
            pbest[i].x[j] = oldparticle[i].x[j];
            pbest[i].fitness = oldparticle[i].fitness;
        }
    }
    gbest.Init(Map_City);
    gbest.fitness = INFINITY;//为全局最优粒子初始化
    for (int i = 0; i < popsize; i++) {
        if (pbest[i].fitness < gbest.fitness) {
            gbest.fitness = pbest[i].fitness;
            for (int j = 0; j < CityNum; j++)
                gbest.x[j] = pbest[i].x[j];
        }
    }
}

void PSO::Show() {
    for (int i = 0; i < popsize; i++) {
        cout << "Particle" << i + 1 << "->";
        oldparticle[i].show();
    }
}

void PSO::PSO_TSP(int Pop_size, int itetime, double C1, double C2, double W, float Vlimitabs, Graph Map_City) {
//    Map_City.ComputeDistance();
    vmax = Vlimitabs;
    vmin = -Vlimitabs;
    Init(Pop_size, itetime, C1, C2, W, Map_City);
    cout << "init：" << endl;
    Show();
    for (int ite = 0; ite < Itetime; ite++) {
        for (int i = 0; i < popsize; i++) {
            //更新粒子速度和位置
            for (int j = 0; j < CityNum; j++) {
                oldparticle[i].v[j] = (int) (w * oldparticle[i].v[j] +
                                             c1 * (rand() % 1000 / (float) (1000)) *
                                             (pbest[i].x[j] - oldparticle[i].x[j]) +
                                             c2 * (rand() % 1000 / (float) (1000)) *
                                             (gbest.x[j] - oldparticle[i].x[j]));
                if (oldparticle[i].v[j] > vmax)//粒子速度越界调整
                    oldparticle[i].v[j] = (int) vmax;
                else if (oldparticle[i].v[j] < vmin)
                    oldparticle[i].v[j] = (int) vmin;
                oldparticle[i].x[j] += oldparticle[i].v[j];
                if (oldparticle[i].x[j] > CityNum)oldparticle[i].x[j] = CityNum;//粒子位置越界调整
                else if (oldparticle[i].x[j] < 1) oldparticle[i].x[j] = 1;
            }
            //粒子位置有效性调整，必须满足解空间的条件
            oldparticle[i].repair(oldparticle[i]);
            oldparticle[i].fitness = oldparticle[i].Evaluate(oldparticle[i].x, Map_City);
            pbest[i].fitness = oldparticle[i].Evaluate(pbest[i].x, Map_City);
            if (oldparticle[i].fitness < pbest[i].fitness) {
                for (int j = 0; j < CityNum; j++)
                    pbest[i].x[j] = oldparticle[i].x[j];
            }//更新单个粒子的历史极值
            for (int j = 0; j < CityNum; j++)
                gbest.x[j] = pbest[i].x[j];//更新全局极值
            for (int k = 0; k < popsize && k != i; k++) {
                if (pbest[k].Evaluate(pbest[k].x, Map_City) < gbest.Evaluate(gbest.x, Map_City)) {
                    for (int j = 0; j < CityNum; j++)
                        gbest.x[j] = pbest[k].x[j];
                    gbest.fitness = gbest.Evaluate(gbest.x, Map_City);
                }
            }
        }
        gbest.show();
    }
}

