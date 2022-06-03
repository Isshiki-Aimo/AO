//
// Created by Aimo on 2022/6/2.
//

#include "CVRP.h"

void CVRP::Init() {
    best_ant.Path_Length = INFINITY;
}

void CVRP::Update(Graph g) {
    double temp[City_Num][City_Num];
    int m = 0;
    int n = 0;
    for (auto &i: temp) {
        for (double &j: i) {
            j = 0;
        }
    }
    for (auto &ant: ants) {
        for (int j = 1; j < ant.City_Count; j++) {
            m = ant.Path[j];
            n = ant.Path[j - 1];
            temp[n][m] = temp[n][m] + Q / ant.Path_Length;
            temp[m][n] = temp[n][m];
        }

    }
    for (int i = 0; i < City_Num; i++) {
        for (int j = 0; j < City_Num; j++) {
            g.Pheromone[i][j] = g.Pheromone[i][j] * Theta + temp[i][j];
        }
    }
}

void CVRP::Search(Graph g) {
    for (int i = 0; i < item; i++) {
        //蚂蚁移动
        for (auto &ant: ants) {
            ant.Search(g);
        }
        //更新全局最优值
        for (auto &ant: ants) {
            if (ant.Path_Length < best_ant.Path_Length) {
                best_ant = ant;
            }
        }
        //更新信息素
        Update(g);
        cout << "第"<<i+1<<"次迭代，最优路径长度为：" << best_ant.Path_Length << endl;
    }

    for (int i: best_ant.Path) {
        if (i != -1)
            cout << i << "  ";
    }

    cout << endl;
    cout << "the shortest length is  " << best_ant.Path_Length << endl;
}


