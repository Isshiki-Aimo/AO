from Bee import *
from my_kmeans import *
import matplotlib.pyplot as plt

class Colony:
    def __init__(self, pop_size, dimension, max_iter, limit, class_num, max_solution, min_solution, matrix_data):
        """
        :param pop_size:种群大小
        :param dimension:解空间维度
        :param max_iter:最大迭代次数
        :param limit:限制值
        :param class_num:类别数
        """
        self.Nectar = []
        self.employed_bees = []
        self.onlooker_bees = []
        self.selected_prob = []
        self.pop_size = pop_size
        self.dimension = dimension
        self.max_iter = max_iter
        self.limit = limit
        self.class_num = class_num
        self.max_solution = max_solution
        self.min_solution = min_solution
        self.best_nectar = None
        self.matrix_data = matrix_data

        for i in range(self.pop_size):
            # 初始化蜜源
            self.Nectar.append(Bee(self.dimension, self.max_solution, self.min_solution, self.class_num))
            value = self.compute_fitness(self.Nectar[i])
            self.Nectar[i].fitness = value
            # 初始化蜜蜂
            self.employed_bees.append(Bee(self.dimension, self.max_solution, self.min_solution, self.class_num))
            value = self.compute_fitness(self.employed_bees[i])
            self.employed_bees[i].fitness = value
            self.onlooker_bees.append(Bee(self.dimension, self.max_solution, self.min_solution, self.class_num))
            value = self.compute_fitness(self.onlooker_bees[i])
            self.onlooker_bees[i].fitness = value
            # 初始化选择概率
            self.selected_prob.append(0)
            # 初始化最好的蜜蜂
        self.best_nectar = self.Nectar[0]

    def compute_fitness(self, bee):
        """
        :param bee:蜜蜂
        """
        # 计算全体样本的中心
        center = np.zeros((1, self.dimension))
        for i in range(len(self.matrix_data)):
            center += self.matrix_data[i]
        center = center / len(self.matrix_data)

        # 计算点到各类别中心的距离
        point_to_center_distance = compute_distance(self.matrix_data, bee.solution)

        # 获得各点属于哪一类别
        cluster = get_cluster(point_to_center_distance)

        # 各类别共有多少个点
        each_class_num = get_each_class_num(cluster, self.class_num)

        # 计算类中心到全体样本中心的距离
        classcenter_center_distance = compute_distance(bee.solution, center)

        # trb是类间分离度
        trb = 0
        for i in range(self.class_num):
            trb += each_class_num[i] * classcenter_center_distance[i]

        # 计算各类别的样本距中心的平均距离
        each_class_distance = get_each_class_distance(point_to_center_distance, cluster, self.class_num, each_class_num)

        # trw是类内聚合度
        trw = 0
        for i in range(self.class_num):
            trw += each_class_distance[0][i]

        # 计算适应度
        value = (trb / self.class_num - 1) / (trw / (len(self.matrix_data) - self.class_num))
        return value

    def employed_bees_search(self):
        for i in range(self.pop_size):
            for j in range(self.class_num):
                for k in range(self.dimension):
                    self.employed_bees[i].solution[j][k] = self.Nectar[i].solution[j][k]
            while True:
                rand_num = randint(0, self.pop_size - 1)
                if rand_num != i:
                    break
            rand_demension = randint(0, self.dimension - 1)
            rand_class = randint(0, self.class_num - 1)
            self.employed_bees[i].solution[rand_class, rand_demension] = self.Nectar[i].solution[
                                                                             rand_class, rand_demension] + uniform(-1,
                                                                                                                   1) * (
                                                                                 self.Nectar[i].solution[
                                                                                     rand_class, rand_demension] -
                                                                                 self.Nectar[rand_num].solution[
                                                                                     rand_class, rand_demension])
            # 修复
            if self.employed_bees[i].solution[rand_class, rand_demension] > self.max_solution[rand_demension]:
                self.employed_bees[i].solution[rand_class, rand_demension] = self.max_solution[rand_demension]
            elif self.employed_bees[i].solution[rand_class, rand_demension] < self.min_solution[rand_demension]:
                self.employed_bees[i].solution[rand_class, rand_demension] = self.min_solution[rand_demension]
            self.employed_bees[i].fitness = self.compute_fitness(self.employed_bees[i])

            # 找到好蜜源就更新
            if self.employed_bees[i].fitness > self.Nectar[i].fitness:
                for j in range(self.class_num):
                    for k in range(self.dimension):
                        self.Nectar[i].solution[j][k] = self.employed_bees[i].solution[j][k]
            else:
                self.Nectar[i].limit += 1

    def compute_prob(self):
        sum_value = 0
        for i in range(self.pop_size):
            sum_value += self.compute_fitness(self.Nectar[i])
        for i in range(self.pop_size):
            self.selected_prob[i] = self.compute_fitness(self.Nectar[i]) / sum_value

    def onlooker_bees_search(self):
        choose_prob = random()
        for i in range(self.pop_size):
            choose_prob = choose_prob - self.selected_prob[i]
            if choose_prob <= 0:
                for j in range(self.class_num):
                    for k in range(self.dimension):
                        self.onlooker_bees[i].solution[j][k] = self.Nectar[i].solution[j][k]
                while True:
                    rand_num = randint(0, self.pop_size - 1)
                    if rand_num != i:
                        break
                rand_demension = randint(0, self.dimension - 1)
                rand_class = randint(0, self.class_num - 1)
                self.onlooker_bees[i].solution[rand_class, rand_demension] = self.Nectar[i].solution[
                                                                                 rand_class, rand_demension] + uniform(
                    -1,
                    1) * (
                                                                                     self.Nectar[i].solution[
                                                                                         rand_class, rand_demension] -
                                                                                     self.Nectar[rand_num].solution[
                                                                                         rand_class, rand_demension])
                # 修复
                if self.onlooker_bees[i].solution[rand_class, rand_demension] > self.max_solution[rand_demension]:
                    self.onlooker_bees[i].solution[rand_class, rand_demension] = self.max_solution[rand_demension]
                elif self.onlooker_bees[i].solution[rand_class, rand_demension] < self.min_solution[rand_demension]:
                    self.onlooker_bees[i].solution[rand_class, rand_demension] = self.min_solution[rand_demension]
                self.onlooker_bees[i].fitness = self.compute_fitness(self.onlooker_bees[i])

                # 找到好蜜源就更新
                if self.onlooker_bees[i].fitness > self.Nectar[i].fitness:
                    for j in range(self.class_num):
                        for k in range(self.dimension):
                            self.Nectar[i].solution[j][k] = self.onlooker_bees[i].solution[j][k]
                else:

                    self.Nectar[i].limit += 1

    def scout_bees_search(self):
        for i in range(self.pop_size):
            if self.compute_fitness(self.Nectar[i]) > self.compute_fitness(self.best_nectar):
                self.best_nectar = self.Nectar[i]
                self.best_nectar.fitness = self.compute_fitness(self.best_nectar)

    def savebest_nectar(self):
        for i in range(self.pop_size):
            if self.compute_fitness(self.Nectar[i]) > self.best_nectar.fitness:
                self.best_nectar = self.Nectar[i]
                self.best_nectar.fitness = self.compute_fitness(self.best_nectar)

    def run(self):
        self.savebest_nectar()
        all_best = []
        for i in range(self.max_iter):
            self.employed_bees_search()
            self.compute_prob()
            self.onlooker_bees_search()
            self.scout_bees_search()
            self.savebest_nectar()
            print("第%d次迭代，最优值为%f" % (i, self.best_nectar.fitness))
            all_best.append(self.best_nectar.fitness)
        return all_best


# seed(8)
data, label, label_dict = get_my_data("balance-scale.txt")
data_matrix = get_data_matrix(data)
max_list, min_list = find_max_min(data_matrix)
colony = Colony(pop_size=10, dimension=data_matrix.shape[1], max_iter=150, limit=15, class_num=3,
                max_solution=max_list, min_solution=min_list, matrix_data=data_matrix)
bee = Bee(colony.dimension, colony.max_solution, colony.min_solution, colony.class_num)
all_best = colony.run()
my_center = colony.best_nectar.solution
distance = compute_distance(data_matrix, my_center)
cluster = get_cluster(distance)
true_lable = get_true_label(distance, label_dict.keys(), label, cluster, 3)
error = val_cluster(cluster, label)
print("The error of K-means is:",1- error)

plt.plot(all_best)
plt.title("The best fitness of each iteration for balance")
plt.xlabel("Iteration")
plt.ylabel("Fitness")
plt.show()
