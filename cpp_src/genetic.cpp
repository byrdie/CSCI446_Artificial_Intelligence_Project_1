/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "genetic.h"
GeneticAlgorithm ::GeneticAlgorithm(Map * in_map, int in_pop_size, int in_mut_rate, int in_N,  int in_num_colors){
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
    return map->num_conflicts();
}

int GeneticAlgorithm :: tournament_select(){
    int sel_x = (rand()%pop_size) + 1;
    int sel_y = (rand()%pop_size) + 1;
    int x_conf;
    int y_conf;
    
    map->set_all_colors(pop[sel_x]);
    x_conf = map->num_conflicts();
    map->set_all_colors(pop[sel_y]);
    y_conf = map->num_conflicts();
    
    if(x_conf < y_conf){
        return x_conf;
    }else {
        y_conf;
    }
}

int* GeneticAlgorithm :: crossover(unsigned int x, unsigned int y){
    unsigned int new_indiv [2][N];
    int cross_point = (rand()%(N-2)) +1;
    for (int i =0; i < N; i++){
        if (i < cross_point){
            new_indiv[0][i] = pop[x][i];
            new_indiv[1][i] = pop[y][i];
        } else{
            new_indiv[0][i] = pop[y][i];
            new_indiv[1][i] = pop[x][i];
        }
    }
    return new_indiv;
    
}