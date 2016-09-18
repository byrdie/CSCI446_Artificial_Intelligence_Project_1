import random
from map_data_types import *
class GeneticAlgorithm():
    def __init__(self, map, k):
        self.pop_size = 10
        self.pop = []
        self.map = map
        self.colors = colors
        self.mutation_rate = 5
        self.k = k

    def run(self):
        self.pop_copy = []
        for indiv in self.pop:
            indiv_x = self.tournament_select()
            indiv_y = self.tournament_select()
        self.init_pop()

    def init_pop(self):
        for i in range(0, self.pop_size):
            self.pop.append([])
            for j in range(0, len(self.map.graph)):
               self.pop[i].append(self.colors[random.randint(1,self.k)])
            print (self.calc_fitness(self.pop[i]))

    def calc_fitness(self, indiv):
        for i in range(0, len(self.map.graph)):
            self.map.graph[i].color = indiv[i]
        return self.map.num_conflicts()
    def tournament_select(self, indiv_1, indiv2):