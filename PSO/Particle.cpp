//
// Created by Aimo on 2022/5/24.
//

#include <fstream>
#include <cstdlib>
#include "Particle.h"

using namespace std;

double Particle::Evaluate(int *x, Graph Map_City) {
    {
        double fitnessvalue = 0;
        for (int i = 0; i < CityNum - 1; i++)
            fitnessvalue += Map_City.Distance[x[i] - 1][x[i + 1] - 1];
        fitnessvalue += Map_City.Distance[x[CityNum - 1] - 1][x[0] - 1];
        return fitnessvalue;
    }
}

void Particle::Init(Graph Map_City) {
    x = new int[CityNum];
    v = new int[CityNum];
    int *order = Random_Order(CityNum);
    for (int i = 0; i < CityNum; i++) {
        x[i] = order[i];
        fitness = Evaluate(x, Map_City);
    }
    for (int i = 0; i < CityNum; ++i) {
        v[i] = rand() % 3 - 1;
    }

}

void Particle::show() {
    for (int i = 0; i < CityNum; i++) {
        if (i == CityNum - 1)
            cout << x[i] << ") = " << fitness << endl;
        else if (i == 0)
            cout << "(" << x[i] << ",";
        else
            cout << x[i] << ",";
    }
}

void Particle::repair(Particle p) {
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
