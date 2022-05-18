//
// Created by Aimo on 2022/5/18.
//

#ifndef GA_01_POPULATION_H
#define GA_01_POPULATION_H
#include "Chromosome.h"

class Population {
public:
    float Goods_value_rate[Good_Num];
    int Chr_index[Good_Num];
    Chromosome population[pop_size];    // 种群
    Chromosome child[pop_size];         // 子代
    Chromosome best_chromosome;         // 最优个体
    Chromosome Global_best_chromosome;  // 全局最优个体
    void compute_fitness();             // 计算适应度
    void repair_chromosome(Chromosome &c); // 修复突变
    void init_population(int seed);     // 初始化种群
    void select();                      // 选择
    int compare_fitness(Chromosome &c1, Chromosome &c2);    // 比较适应度
    void crossover();                   // 交叉
    void mutation();                    // 变异
    void find_best_chromosome();        // 找到最优个体
    void compute_value_rate();          // 计算商品价值比例
    void swap(int &a, int &b);          // 交换
    void sort_by_value_rate();          // 按价值比例排序

};


#endif //GA_01_POPULATION_H
