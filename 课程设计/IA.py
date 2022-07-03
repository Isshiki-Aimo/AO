import numpy as np

G = 100
choice = 'max'
dim = 2
limit_x = [-4, 4]
limit_y = [-4, 4]
pop_size = 10
mutate_rate = 0.7
delta = 0.2
beta = 1
colone_num = 10
if choice == 'max':
    alpha = 2
else:
    alpha = -2


def f(x, y):
    x1 = x[0]
    x2 = x[1]
    x3 = x[2]
    x4 = x[3]
    x5 = x[4]
    x6 = x[5]
    x7 = x[6]
    x8 = x[7]
    y1 = y[0]
    y2 = y[1]
    func = x1 * np.exp(x2) + x3 * np.sin(x4) + x5 + x6 + x7 + x8
    return func


def init_pop(dim, pop_size, *limit):
    pop = np.random.rand(dim, pop_size)
    for i in range(dim):
        pop[i, :] *= (limit[i][1] - limit[i][0])
        pop[i, :] += limit[i][0]

    return pop


def calc_density(pop, delta):
    density = np.zeros([pop.shape[1], ])
    for i in range(pop.shape[1]):
        density[i] = np.sum(
            len(np.ones([pop.shape[1], ])[np.sqrt(np.sum((pop - pop[:, i].reshape([2, 1])) ** 2, axis=0)) < delta]))
    return density / pop.shape[1]


def calc_simulation(simulation, density):
    return (alpha * simulation - beta * density)


def mutate(x, gen, mutata_rate, dim, *limit):
    for i in range(dim):
        if np.random.rand() <= mutata_rate:
            x[i] += (np.random.rand() - 0.5) * (limit[i][1] - limit[i][0]) / (gen + 1)
            if (x[i] > limit[i][1]) or (x[i] < limit[i][0]):
                x[i] = np.random.rand() * (limit[i][1] - limit[i][0]) + limit[i][0]


pop = init_pop(dim, pop_size, limit_x, limit_y)
init_simulation = f(pop[0, :], pop[1, :])
density = calc_density(pop, delta)
simulation = calc_simulation(init_simulation, density)
index = np.argsort(-simulation)
pop = pop[:, index]
new_pop = pop.copy()
simulation = simulation[index]
for gen in range(G):
    best_a = np.zeros([dim, int(pop_size / 2)])
    best_a_simulation = np.zeros([int(pop_size / 2), ])
    for i in range(int(pop_size / 2)):
        a = new_pop[:, i].reshape([2, 1])
        b = np.tile(a, (1, colone_num))
        for j in range(colone_num):
            mutate(a, gen, mutate_rate, dim, limit_x, limit_y)
        b[:, 0] = pop[:, i]
        b_simulation = f(b[0, :], b[1, :])
        index = np.argsort(-b_simulation)
        best_a_simulation = b_simulation[index][0]
        best_a[:, i] = b[:, index][:, 0]
    a_density = calc_density(best_a, delta)
    best_a_simulation = calc_simulation(best_a_simulation, a_density)
    new_a = init_pop(2, int(pop_size / 2), limit_x, limit_y)
    new_a_simulation = f(new_a[0, :], new_a[1, :])
    new_a_density = calc_density(new_a, delta)
    new_a_simulation = calc_simulation(new_a_simulation, new_a_density)
    pop = np.hstack([best_a, new_a])
    simulation = np.hstack([best_a_simulation, new_a_simulation])
    index = np.argsort(-simulation)
    pop = pop[:, index]
    simulation = simulation[index]
    new_pop = pop.copy()
