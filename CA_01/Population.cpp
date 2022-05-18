//
// Created by Aimo on 2022/5/18.
//

#include <cstdlib>
#include "Population.h"
#include "iostream"

using namespace std;

void Population::compute_fitness() {
    for (int i = 0; i < pop_size; i++) {
        population[i].value = 0;
        population[i].weight = 0;
        for (int j = 0; j < Gene_num; j++) {
            population[i].weight += Goods_weight[j] * population[i].gene[j];
            population[i].value += Goods_value[j] * population[i].gene[j];
        }
        if (population[i].weight > Max_Weight) {
            repair_chromosome(population[i]);
        }
    }
}

void Population::repair_chromosome(Chromosome &c) {
    //拿出
    for (int j = 0; j < Gene_num; j++) {
        if (c.gene[Chr_index[j]] == 1) {
            c.gene[Chr_index[j]] = 0;
            c.value -= Goods_value[Chr_index[j]];
            c.weight -= Goods_weight[Chr_index[j]];
        }
        if (c.weight <= Max_Weight) {
            break;
        }
    }
    //放入
    for (int j = Gene_num; j > 0; j--) {
        if (c.gene[Chr_index[j - 1]] == 0) {
            c.gene[Chr_index[j - 1]] = 1;
            c.value += Goods_value[Chr_index[j - 1]];
            c.weight += Goods_weight[Chr_index[j - 1]];
        }
        if (c.weight <= Max_Weight) {
            continue;
        } else {
            c.gene[Chr_index[j - 1]] = 0;
            c.value -= Goods_value[Chr_index[j - 1]];
            c.weight -= Goods_weight[Chr_index[j - 1]];
        }
    }
}

void Population::init_population(int seed) {
    compute_value_rate();
    sort_by_value_rate();
    srand(seed);
    for (int i = 0; i < pop_size; i++) {
        for (int j = 0; j < Gene_num; j++) {
            population[i].gene[j] = rand() % 2;
        }
    }
    cout << "init_population" << endl;
    compute_fitness();
}

void Population::select() {
    int i, count;
    double p, sum = 0.0;
    double cfitnes[pop_size];
    for (i = 0; i < pop_size; i++) {
        sum += population[i].value;
    }
    //选择概率
    for (i = 0; i < pop_size; i++) {
        cfitnes[i] = population[i].value / sum;
    }
    //累计概率
    for (i = 1; i < pop_size; i++) {
        cfitnes[i] += cfitnes[i - 1];
    }
    for (i = 0; i < pop_size; i++) {
        p = (rand() % 1000) / 1000.0;//随机生成0-1之间的数
        count = 0;
        while (p > cfitnes[count]) {
            count++;
        }
        child[i] = population[count];
    }
    for (i = 0; i < pop_size; i++) {
        population[i] = child[i];
    }
}

int Population::compare_fitness(Chromosome &c1, Chromosome &c2) {
    if (c1.value > c2.value) {
        return 1;
    } else if (c1.value < c2.value) {
        return -1;
    } else {
        return 0;
    }
}

void Population::crossover() {
    int i;
    for (i = 0; i < pop_size; i++) {
        int p = rand() % pop_size;
        int q = rand() % pop_size;
        if (rand() % 100 < Pc) {
            int cross_point1 = rand() % Gene_num;
            int cross_point2 = rand() % Gene_num;
            if (cross_point1 > cross_point2) {
                swap(cross_point1, cross_point2);
            }
            for (int l = cross_point1; l <= cross_point2; l++) {
                swap(population[p].gene[l], population[q].gene[l]);
            }
        }
    }
    compute_fitness();
}

void Population::mutation() {
    int i = 0;
    for (i = 0; i < pop_size; i++) {
        if (rand() % 100 < Pm) {
            int m = rand() % Gene_num;
            population[i].gene[m] = 1 - population[i].gene[m];
        }
    }
    compute_fitness();
}

void Population::find_best_chromosome() {
    int i = 0;
    best_chromosome = population[0];
    for (i = 1; i < pop_size; i++) {
        if (compare_fitness(population[i], best_chromosome) == 1) {
            best_chromosome = population[i];
        }
    }
    cout << "best_value:" << best_chromosome.value << endl;
    cout << "best_weight:" << best_chromosome.weight << endl;
}

void Population::compute_value_rate() {
    for (int i = 0; i < Good_Num; i++) {
        Goods_value_rate[i] = (float) Goods_value[i] / (float) Goods_weight[i];
    }
}

void Population::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void Population::sort_by_value_rate() {
    for (int i = 0; i < Good_Num; ++i) {
        Chr_index[i] = i;
    }
    for (int i = 0; i < Good_Num - 1; ++i) {
        for (int j = i + 1; j < Good_Num; ++j) {
            if (Goods_value_rate[i] > Goods_value_rate[j]) {
                float temp_value = Goods_value_rate[i];
                Goods_value_rate[i] = Goods_value_rate[j];
                Goods_value_rate[j] = temp_value;
                swap(Chr_index[i], Chr_index[j]);
            }
        }
    }
}


