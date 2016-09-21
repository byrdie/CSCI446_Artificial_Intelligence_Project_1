/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   genetic.h
 * Author: Nevin
 *
 * Created on September 20, 2016, 11:31 PM
 */

#ifndef GENETIC_H
#define GENETIC_H
#include "map_data_types.h"
class GeneticAlgorithm;
class GeneticAlgorithm{
public:
    Map * map;
    int pop_size;
   unsigned int ** pop;
    int mut_rate;
    int N;
    bool solved = false;
    int generations = 0;
    int total = 0;
    int num_colors;
    GeneticAlgorithm(Map * in_map, int in_pop_size, int in_mut_rate, int in_N, int in_num_colors);
    void run();
    void init_pop();
    int calc_fitness(int indiv);
    int tournament_select();
    int** crossover(unsigned int x, unsigned int y);
};

#endif /* GENETIC_H */

