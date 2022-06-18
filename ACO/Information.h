//
// Created by Aimo on 2022/6/2.
//

#ifndef ACO_INFORMATION_H
#define ACO_INFORMATION_H

const int City_Num = 11;//城市数目
const int Alpha = 1;
const int Beta = 5;
const int Q = 100;//表示蚂蚁循环一次所释放的信息素总量
const double Theta = 0.2;//表示信息素的衰减率
const int Ant_num = 50;//蚂蚁数量
const int item = 1000;//迭代次数
const int max_v = 120;//最大容量
const double Correction_X[City_Num] = {40, 25, 15, 10, 5, 0, 44, 35, 95, 85, 65};//城市的横坐标
const double Correction_Y[City_Num] = {50, 85, 75, 35, 35, 40, 5, 5, 30, 35, 85};//城市的纵坐标
const int need[City_Num] = {0, 20, 20, 20, 10, 20, 20, 20, 30, 30, 40};//储存每个城市的需求量


#endif //ACO_INFORMATION_H
