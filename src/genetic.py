import random
import copy
from map_data_types import *

class GeneticAlgorithm():
    def __init__(self, map, k):
        self.pop_size = 100
        self.pop = []
        self.map = map
        self.mutation_rate = 40
        self.k = k
        self.solved = False
        self.generations = 0
        self.total = 0

    def run(self):
        gen = 0
        pop_copy = []
        self.init_pop()

        while (self.solved == False):
            #print (len(self.pop))
            pop_copy = []
            gen += 1
            #print (gen)
            for i in range(0, int(len(self.pop)/2)):
                indiv_x = self.tournament_select()
                indiv_y = self.tournament_select()

                temp = self.crossover(indiv_x, indiv_y)
                self.mutate(temp[0])
                self.mutate(temp[1])
                if self.calc_fitness(temp[0]) == 0:
                    self.solved = True
                    print (self.generations)
                    print (self.total)
                    return self.map

                elif self.calc_fitness(temp[1]) == 0:
                    self.solved = True
                    print(self.generations)
                    print(self.total)
                    return self.map

                pop_copy.append(temp[0])
                pop_copy.append(temp[1])
            self.pop = copy.deepcopy(pop_copy)
            self.generations += 1
            self.total += 1


            if (self.generations>125):
                self.generations = 0
                for i in range(0, int(len(self.pop)/2)):
                    for j in range(0, len(self.map.graph)):
                        self.pop[i][j] = Color(random.randint(1, self.k))


    def init_pop(self):
        for i in range(0, self.pop_size):
            self.pop.append([])

            for j in range(0, len(self.map.graph)):
               self.pop[i].append(Color(random.randint(1,self.k)))

    def calc_fitness(self, indiv):
        for i in range(0, len(self.map.graph)):
            self.map.graph[i].color = Color(indiv[i])

        return self.map.num_conflicts()

    def tournament_select(self):
        sel_x = self.pop[random.randint(0, len(self.pop)-1)]
        sel_y = self.pop[random.randint(0, len(self.pop)-1)]
        print(self.calc_fitness(sel_x))
        print(self.calc_fitness(sel_y))

        if self.calc_fitness(sel_x) > self.calc_fitness(sel_y):

            return sel_y
        else:
            return sel_x

    def crossover(self, indiv_x, indiv_y):
        new_x = []
        new_y = []
        cross_point = random.randint(1, len(self.map.graph) - 1)
        for i in range(0, len(self.map.graph)):
            if i < cross_point:
                new_x.append(indiv_y[i])
                new_y.append(indiv_x[i])
            else:
                new_x.append(indiv_x[i])
                new_y.append(indiv_y[i])


        return [new_x, new_y]

    def mutate(self, indiv):
        if random.randint(1, 100) < self.mutation_rate:
            indiv[random.randint(0, len(indiv) - 1)] = Color(random.randint(1,self.k))