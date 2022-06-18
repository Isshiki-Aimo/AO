import numpy as np
from random import *




class Bee:
    def __init__(self, dimension, max_solution, min_solution,class_num):
        self.dimension = dimension  # 解空间的维度
        self.fitness = 0  # 适应度
        self.limit = 0  # 限制值
        self.solution = np.zeros((class_num, self.dimension))  # 解空间
        for i in range(class_num):
            for j in range(self.dimension):
                self.solution[i, j] = random() * (max_solution[i] - min_solution[i]) + min_solution[i]

