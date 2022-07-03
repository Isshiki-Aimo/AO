import math
import random

import matplotlib.pyplot as plt
import numpy as np


class GA(object):
    def __init__(self, population_size, chromosome_length, pm):
        self.population_size = population_size
        self.chromosome_length = chromosome_length
        self.pm = pm

    # 初始化种群
    def species_origin(self):
        population = [[]]  # 二维列表，包含染色体和基因
        for i in range(self.population_size):
            temporary = []  # 染色体寄存器
            for j in range(self.chromosome_length):
                temporary.append(random.randint(0, 1))  # 生成基因
            population.append(temporary)
        return population[1:]

    # 种群解码，用于适应度判断
    def translation(self, population):
        chromosome_d_list = []
        for i in range(len(population)):
            chromosome_value_d = 0
            for j in range(len(population[0])):
                chromosome_value_d += population[i][j] * (math.pow(2, len(population[0]) - j - 1))
            chromosome_d_list.append(chromosome_value_d)
        return chromosome_d_list

    # 适应度计算
    def function(self, population, lower_bound, upper_bound):
        all_fitness_list = []  # 创建所有染色体适应度列表
        fv_list = self.translation(population)
        for i in range(len(fv_list)):
            x = int(lower_bound + fv_list[i] * (upper_bound - lower_bound) / (math.pow(2, self.chromosome_length) - 1))
            y = 15 * x - x * x
            all_fitness_list.append(y)
        return all_fitness_list

    def positive_fitness(self, all_fitness_list):
        pf = []
        for i in range(len(all_fitness_list)):
            if all_fitness_list[i] > 0:
                pf.append(all_fitness_list[i])
        return pf

    def positive_chromosome(self, all_fitness_list, population):
        positive_chromosome_list = []
        for i in range(len(all_fitness_list)):
            if all_fitness_list[i] > 0:
                positive_chromosome_list.append(population[i])
        return positive_chromosome_list

    def pf_sum(self, pf):
        pf_total = 0
        for i in range(len(pf)):
            pf_total += pf[i]
        return pf_total

    def pf_float(self, pf_total, pf):
        pf_float = []
        for i in range(len(pf)):  # 正适应度除以适应度总数，转化为小数
            pf_float.append(pf[i] / pf_total)
        return pf_float

    def pf_div(self, pf_float):
        pft_div = []
        for j in range(len(pf_float)):  # 将适应度转化为轮盘赌的概率
            if j == 0:
                pft_div.append(pf_float[j])
            else:
                pft_div.append(pf_float[j] + pft_div[j - 1])
        return pft_div

    # 选择
    def selection(self, pcl, pft_div):
        selected_pop = []
        select_float = []
        for i in range(len(pcl)):
            select_float.append(random.random())
        for i in range(len(pcl)):
            j = 0
            while j < len(pcl):
                if select_float[i] <= pft_div[j]:
                    selected_pop.append(pcl[j])
                    break
                else:
                    j += 1
        return selected_pop

    # 交叉
    def crossover(self, selected_pop, population):  # 单点交叉
        new_pop = [[]]
        for i in range(len(population)):
            cpoint = random.randint(0, len(selected_pop[0]) - 1)  # 随机生成截取点 #
            while True:
                spoint1 = random.randint(0, len(selected_pop) - 1)
                spoint2 = random.randint(0, len(selected_pop) - 1)
                if spoint1 == spoint2:
                    continue
                else:
                    break
            temp = []  # 染色体片段暂时存储器
            temp.extend(selected_pop[spoint1][0:cpoint])  # 第i个染色体0~截取点阶段的基因存储于temp中
            temp.extend(selected_pop[spoint2][cpoint:len(selected_pop[0])])  # 第i+1个染色体截取点~末端阶段的基因存储于temp中
            new_pop.append(temp)
        return new_pop[1:]

    # 变异
    def mutation(self, new_pop):
        for i in range(len(new_pop)):
            mpoint = random.randint(0, len(new_pop[0]) - 1)
            prandom = random.random()
            if prandom <= self.pm:
                if new_pop[i][mpoint] == 1:
                    new_pop[i][mpoint] = 0
                else:
                    new_pop[i][mpoint] = 1
        next_pop = new_pop
        return next_pop

    # 二进制转十进制
    def b2d(self, value_b):
        pf_d = []
        for i in range(len(value_b)):
            value_d = 0
            for j in range(len(value_b[0])):
                value_d += value_b[i][j] * math.pow(2, len(value_b[0]) - 1 - j)
            pf_d.append(value_d)
        return pf_d

    # 可视化
    def plot(self, pcl_d_list, pf, lower_bound, upper_bound, generation, iteration):
        px = []
        for i in range(len(pcl_d_list)):
            pxt = lower_bound + pcl_d_list[i] * (upper_bound - lower_bound) / (math.pow(2, self.chromosome_length) - 1)
            px.append(pxt)
        py = pf
        sca = plt.scatter(px, py, s=200, lw=0, c='red', alpha=0.5)
        plt.pause(0.05)
        print('px', len(px))
        j = generation
        if j < iteration - 1:
            if 'sca' in locals():
                sca.remove()

    def main(self, iteration):
        population = self.species_origin()
        results = []
        for i in range(iteration):
            self.translation(population)
            all_fitness_list = self.function(population, 0, 2 * math.pi)
            pf = self.positive_fitness(all_fitness_list)
            pcl = self.positive_chromosome(all_fitness_list, population)
            self.plot(self.translation(pcl), pf, 0, 2 * np.pi, i, iteration)
            pf_total = self.pf_sum(pf)
            pf_float = self.pf_float(pf_total, pf)
            pft_div = self.pf_div(pf_float)
            selected_pop = self.selection(pcl, pft_div)
            new_pop = self.crossover(selected_pop, population)
            next_pop = self.mutation(new_pop)
            population = next_pop
            results.append(pf_total)
            print('The', i, 'generation pf:', pf, )

        plt.ioff()
        plt.show()


if __name__ == '__main__':
    ga = GA(100, 4, 0.01)
    plt.ion()
    x = np.linspace(0, 15, 15)
    Fx = 15 * x - x * x
    plt.plot(x, Fx)
    plt.grid()
    ga.main(100)
