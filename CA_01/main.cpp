//
// Created by Aimo on 2022/5/18.
//
#include"Chromosome.h"
#include"iostream"
#include "Population.h"
using namespace std;



int main(){
    Population a = Population();
    a.init_population(0);
    a.find_best_chromosome();
    int generation = 0;
    while(generation < Max_Generation){
        a.select();
        a.crossover();
        a.mutation();
        a.find_best_chromosome();
        generation++;
        if (a.compare_fitness(a.best_chromosome,a.Global_best_chromosome)==1){
            a.Global_best_chromosome = a.best_chromosome;
        }
    }
    cout<<"The best chromosome is: "<<a.Global_best_chromosome.value<<endl;
    return 0;

}


