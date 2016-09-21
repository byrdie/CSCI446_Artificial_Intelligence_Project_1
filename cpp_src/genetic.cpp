/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "genetic.h"
GeneticAlgorithm ::GeneticAlgorithm(Map * in_map, int in_pop_size, int in_mut_rate, int in_N, int in_num_colors){
    map = in_map;
    pop_size = in_pop_size;
    mut_rate = in_mut_rate;
    N = in_N;
    pop = new int*[pop_size];
    num_colors = in_num_colors;
    for (int i = 0; i < pop_size; i++){
        pop[i] = new int[N];
    }
}

void GeneticAlgorithm :: run(){
    int f = 0;
}

void GeneticAlgorithm :: init_pop(){
    for (int i = 0; i < pop_size; i++){
        for (int j = 0; j < N; j++){
            pop[i][j] = (rand()%num_colors) + 1;
        }
    }
}

int GeneticAlgorithm :: calc_fitness(int indiv){
    for(int i = 0; i < N; i++){
        pop[indiv];
    }
}