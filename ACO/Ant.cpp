//
// Created by Aimo on 2022/6/2.
//

#include "Ant.h"

void Ant::init() {
    for (int &i: Visited) {
        i = 1;//表示最开始所有城市均未访问
    }
    Path_Length = 0;
    Location = 0;//表示从0号地点出发,即配送中心
    City_Count = 0;
    for (int &i: Path) {
        i = -1;
    }
    Visited[Location] = 0;
    City_Count++;
    Path[0] = Location;
    Weight = 0;

}

int Ant::ChooseNextCity(Graph g) {
    int next_city = -1;
    double Total_Pheromone = 0;//信息素总和
    double prob[City_Num];//保存概率
    for (int i = 0; i < City_Num; i++) {
        if (Visited[i] == 1 && g.Distance[Location][i] != 0) {
            prob[i] = pow(g.Pheromone[Location][i], Alpha) * pow(1 / g.Distance[Location][i], Beta);
            Total_Pheromone += prob[i];
        } else {
            prob[i] = 0;
        }
    }

    //轮盘赌选择
    double temp = 0;
    if (Total_Pheromone > 0) {
        temp = (rand() % 100 / 100.0) * Total_Pheromone;
        for (int i = 0; i < City_Num; i++) {
            if (Visited[i] == 1) {
                temp -= prob[i];
                if (temp < 0.0) {
                    next_city = i;
                    break;
                }
            }
        }
    } else {
        cout << "yes";
        return 0;
    }
    return next_city;
}

void Ant::move(Graph g) {
    int next_city = ChooseNextCity(g);
    Weight = Weight + need[next_city];
    if (Weight <= max_v) {
        Path[City_Count] = next_city;
        Visited[next_city] = 0;
        Location = next_city;
        City_Count++;
    }
    if (Weight > max_v) {
        Path[City_Count] = 0;//回到仓库
        Location = 0;
        City_Count++;
        Weight = 0;//装货后接着上路
    }


}

void Ant::Compute_length(Graph g) {
    Path_Length = 0.0;
    for (int i = 1; i < City_Count; i++) {
        Path_Length += g.Distance[Path[i]][Path[i - 1]];
    }
}

void Ant::Search(Graph g) {
    init();//对蚂蚁进行初始化
    bool flag = true;
    do {
        move(g);
        for (int i: Visited) {
            if (i == 1)//表示还有城市没有被访问
            {
                flag = true;
                break;
            }
            flag = false;
        }
    } while (flag);
    Path[City_Count] = 0;
    City_Count++;
    Compute_length(g);
}
