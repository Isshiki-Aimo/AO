//
// Created by Aimo on 2022/5/24.
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <random>
#include <cfloat>

using namespace std;


float vmax = 1, vmin = -1;
#define CityNum 51


float City_x[] = {37, 49, 52, 20, 40, 21,
                  17, 31, 52, 51, 42,
                  31, 5, 12, 36, 52,
                  27, 17, 13, 57, 62,
                  42, 16, 8, 7, 27,
                  30, 43, 58, 58, 37,
                  38, 46, 61, 62, 63,
                  32, 45, 59, 5, 10,
                  21, 5, 30, 39, 32,
                  25, 25, 48, 56, 30};

float City_y[] = {52, 49, 64, 26, 30, 47,
                  63, 62, 33, 21, 41,
                  32, 25, 42, 16, 41,
                  23, 33, 13, 58, 42,
                  57, 57, 52, 38, 68,
                  48, 67, 48, 27, 69,
                  46, 10, 33, 63, 69,
                  22, 35, 15, 6, 17,
                  10, 64, 15, 10, 39,
                  32, 55, 28, 37, 40};

class Coordinate {
public:
    float x;
    float y;

    Coordinate(float x, float y) {
        this->x = x;
        this->y = y;
    };
};

class Graph {
public:
    Coordinate *city[CityNum];
    float Distance[CityNum][CityNum];

    void ComputeDistance() {
        float x, y;
        for (int i = 0; i < CityNum; i++) {
            x = City_x[i];
            y = City_y[i];
            city[i] = new Coordinate(x, y);
        }

        for (int i = 0; i < CityNum; i++) {
            for (int j = 0; j < CityNum; j++) {
                if (i == j) {
                    Distance[i][j] = 0;
                } else {
                    Distance[i][j] = Distance[j][i] = sqrt(
                            pow(city[i]->x - city[j]->x, 2) + pow(city[i]->y - city[j]->y, 2));
                }
            }
        }

    };

    void ShowDistance() {
        for (auto & i : Distance) {
            for (float j : i) {
                cout << j << " ";
            }
            cout << endl;
        }
    };

};

int *Random_Order(int city_num) //随机生成序列
{
    int *order;
    order = new int[city_num];
    int j = 0;
    while (j < city_num) {
        while (true) {
            int flag = -1;
            int temp = rand() % city_num + 1;
            if (j > 0) {
                int k = 0;
                for (; k < j; k++) {
                    if (temp == *(order + k))break;
                }
                if (k == j) {
                    *(order + j) = temp;
                    flag = 1;
                }
            } else {
                *(order + j) = temp;
                flag = 1;
            }
            if (flag == 1)break;
        }
        j++;
    }
    return order;
}


Graph Map_City;

double Evaluate(int *x)//计算粒子适应值的函数
{
    double fitnessvalue = 0;
    for (int i = 0; i < CityNum - 1; i++)
        fitnessvalue += Map_City.Distance[x[i] - 1][x[i + 1] - 1];
    fitnessvalue += Map_City.Distance[x[CityNum - 1] - 1][x[0] - 1];
    return fitnessvalue;
}

class Particle {
public:
    int *x;//粒子的位置
    int *v;//粒子的速度
    double fitness;

    void Init() {
        x = new int[CityNum];
        v = new int[CityNum];
        int *M = Random_Order(CityNum);
        for (int i = 0; i < CityNum; i++)
            x[i] = *(M + i);
        fitness = Evaluate(x);
        for (int i = 0; i < CityNum; i++) {
            v[i] = rand() % 3 - 1;
        }
    }

    void show() {
        for (int i = 0; i < CityNum; i++) {
            if (i == CityNum - 1)
                cout << x[i] << ") = " << fitness << endl;
            else if (i == 0)
                cout << "(" << x[i] << ",";
            else
                cout << x[i] << ",";
        }
    }
};


void repair(Particle p)//修复序列
{
    int route[CityNum];
    bool flag[CityNum];//对应route数组中是否在粒子的位置中存在的数组，参考数组为route
    int tag[CityNum];//对粒子每个元素进行标记的数组,参考数组为粒子位置x
    for (int j = 0; j < CityNum; j++) {
        route[j] = j + 1;
        flag[j] = false;    //是否存在
        tag[j] = 0;
    }
    //首先判断粒子p的位置中是否有某个城市且唯一，若有且唯一，则对应flag的值为true,
    for (int j = 0; j < CityNum; j++) {
        int num = 0;
        for (int k = 0; k < CityNum; k++) {
            if (p.x[k] == route[j]) {
                tag[k] = 1;//说明粒子中的k号元素对应的城市在route中，并且是第一次出现才进行标记
                num++;
                break;
            }
        }
        if (num == 0) flag[j] = false;//粒子路线中没有route[j]这个城市
        else if (num == 1) flag[j] = true;//粒子路线中有route[j]这个城市
    }
    for (int k = 0; k < CityNum; k++) {
        if (!flag[k])//粒子路线中没有route[k]这个城市，需要将这个城市加入到粒子路线中
        {
            int i = 0;
            for (; i < CityNum; i++) {
                if (tag[i] != 1)break;
            }
            p.x[i] = route[k];//对于标记为0的进行替换
            tag[i] = 1;
        }
    }
}


class PSO {
public:
    Particle *oldparticle;
    Particle *pbest, gbest;
    double c1, c2, w;
    int Itetime;
    int popsize;

    void Init(int Pop_Size, int itetime, double C1, double C2, double W) {
        Itetime = itetime;
        c1 = C1;
        c2 = C2;
        w = W;
        popsize = Pop_Size;
        oldparticle = new Particle[popsize];
        pbest = new Particle[popsize];
        for (int i = 0; i < popsize; i++) {
            oldparticle[i].Init();
            pbest[i].Init();
            for (int j = 0; j < CityNum; j++) {
                pbest[i].x[j] = oldparticle[i].x[j];
                pbest[i].fitness = oldparticle[i].fitness;
            }
        }
        gbest.Init();
        gbest.fitness = INFINITY;//为全局最优粒子初始化
        for (int i = 0; i < popsize; i++) {
            if (pbest[i].fitness < gbest.fitness) {
                gbest.fitness = pbest[i].fitness;
                for (int j = 0; j < CityNum; j++)
                    gbest.x[j] = pbest[i].x[j];
            }
        }
    }

    void Show() {
        for (int i = 0; i < popsize; i++) {
            cout << "Particle" << i + 1 << "->";
            oldparticle[i].show();
        }
    }

    void PSO_TSP(int Pop_size, int itetime, double C1, double C2, double W, float Vlimitabs) {
        Map_City.ComputeDistance();
        Map_City.ShowDistance();
        vmax = Vlimitabs;
        vmin = -Vlimitabs;
        Init(Pop_size, itetime, C1, C2, W);
        cout << "初始化后的种群如下：" << endl;
        Show();
        for (int ite = 0; ite < Itetime; ite++) {
            for (int i = 0; i < popsize; i++) {
                //更新粒子速度和位置
                for (int j = 0; j < CityNum; j++) {
                    oldparticle[i].v[j] = (int) (w * oldparticle[i].v[j] +
                                                 c1 * (rand() % 1000 / (float )(1000)) * (pbest[i].x[j] - oldparticle[i].x[j]) +
                                                 c2 * (rand() % 1000 / (float )(1000)) * (gbest.x[j] - oldparticle[i].x[j]));
                    if (oldparticle[i].v[j] > vmax)//粒子速度越界调整
                        oldparticle[i].v[j] = (int) vmax;
                    else if (oldparticle[i].v[j] < vmin)
                        oldparticle[i].v[j] = (int) vmin;
                    oldparticle[i].x[j] += oldparticle[i].v[j];
                    if (oldparticle[i].x[j] > CityNum)oldparticle[i].x[j] = CityNum;//粒子位置越界调整
                    else if (oldparticle[i].x[j] < 1) oldparticle[i].x[j] = 1;
                }
                //粒子位置有效性调整，必须满足解空间的条件
                repair(oldparticle[i]);
                oldparticle[i].fitness = Evaluate(oldparticle[i].x);
                pbest[i].fitness = Evaluate(pbest[i].x);
                if (oldparticle[i].fitness < pbest[i].fitness) {
                    for (int j = 0; j < CityNum; j++)
                        pbest[i].x[j] = oldparticle[i].x[j];
                }//更新单个粒子的历史极值
                for (int j = 0; j < CityNum; j++)
                    gbest.x[j] = pbest[i].x[j];//更新全局极值
                for (int k = 0; k < popsize && k != i; k++) {
                    if (Evaluate(pbest[k].x) < Evaluate(gbest.x)) {
                        for (int j = 0; j < CityNum; j++)
                            gbest.x[j] = pbest[k].x[j];
                        gbest.fitness = Evaluate(gbest.x);
                    }
                }
            }
            gbest.show();
        }
    }
};

PSO pso;

int main() {
    pso.PSO_TSP(30, 500, 2, 2, 0.8, 3.0);
    return 0;
}
