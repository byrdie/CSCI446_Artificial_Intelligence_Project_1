/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "genetic.h"

GeneticAlgorithm::GeneticAlgorithm(Map * in_map, int in_pop_size, int in_N, int in_num_colors, int max_gen) {
    map = in_map;
    pop_size = in_pop_size;
    N = in_N;
    pop = new unsigned int*[pop_size];
    num_colors = in_num_colors;
    max_generations = max_gen;
    for (int i = 0; i < pop_size; i++) {
        pop[i] = new unsigned int[N];
    }
    mut_rate = 1/float(N);
    
}

int GeneticAlgorithm::run(long int * counter, bool draw_steps) {
    int gen = 0;
    init_pop();

    while (!solved) {
        int h = 0; //used to add individuals to copy correctly
        unsigned int copy[pop_size][N];
        //loop until a new population is made
        for (int i = 0; i < pop_size / 2; i++) {
            //select two new individuals and add to new pop
            int indiv_x = tournament_select();
            int indiv_y = tournament_select();
            for (int j = 0; j < N; j++) {
                copy[h][j] = pop[indiv_x][j];
                copy[h + 1][j] = pop[indiv_y][j];
            }
            
            if (i == 0){
             for(int j = 0; j < N; j++ ){
                copy[h][j] = 2;
            }
             map->set_all_colors(copy[h]);   
                
             *counter += 1;
             if (draw_steps){
                 
              char filename[100];
              sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
              Cairo * cairo = new Cairo(filename);
              map->draw_map(cairo, generations, *counter, generations);
              cairo->finish();
             }
             for(int j = 0; j < N; j++ ){
                copy[h+1][j] = 3;
            }
              map->set_all_colors(copy[h+1]);   
             *counter += 1;
             if (draw_steps){
              char filename[100];
              sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
              Cairo * cairo = new Cairo(filename);
              map->draw_map(cairo, generations, *counter, generations);
              cairo->finish();
             }
            }
            crossover(copy[h], copy[h + 1]);
            //apply mutations to new individuals
            if (i == 0){
             map->set_all_colors(copy[h]);   
                
             *counter += 1;
             if (draw_steps){
              char filename[100];
              sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
              Cairo * cairo = new Cairo(filename);
              map->draw_map(cairo, generations, *counter, generations);
              cairo->finish();
             }
              map->set_all_colors(copy[h+1]);   
             *counter += 1;
             if(draw_steps){
              char filename[100];
              sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
              Cairo * cairo = new Cairo(filename);
              map->draw_map(cairo, generations, *counter, generations);
              cairo->finish();
             }
            }
            
            
            mutate(copy[h]);
            mutate(copy[h + 1]);
            
            



            //check if new individuals are solutions
            map->set_all_colors(copy[h]);

            if (map->num_conflicts() == 0) {
                i = pop_size / 2;
//                if (draw_steps) {
//                    for (int m = 0; m < 20; m++) {
//                        *counter += 1;
//
//                        char filename[100];
//                        sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
//                        Cairo * cairo = new Cairo(filename);
//                        map->draw_map(cairo, generations, *counter, generations);
//                        cairo->finish();
//                    }
//                }



                solved = true;
            } else {
                map->set_all_colors(copy[h + 1]);

                if (map->num_conflicts() == 0) {
//                    if (draw_steps) {
//                        for (int m = 0; m < 20; m++) {
//                            *counter += 1;
//
//                            char filename[100];
//                            sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
//                            Cairo * cairo = new Cairo(filename);
//                            map->draw_map(cairo, generations, *counter, generations);
//                            cairo->finish();
//                        }
//                    }



                    i = pop_size / 2;
                    solved = true;
                }
            }
            h += 2;
            
        }

        // PRINT MAP HERE
        int herc_index = -1;
        int herc_fit = 1e6;
        for (int j = 0; j < pop_size; j++) {
            map->set_all_colors(copy[j]);
            if (map->num_conflicts() < herc_fit) {
                herc_fit = map->num_conflicts();
                herc_index = j;
            }
        }
//        map->set_all_colors(copy[herc_index]);
//        *counter += 1;
//        if (draw_steps) {
//            char filename[100];
//            sprintf(filename, "../results/genetic/map_build/genetic_I%05ld.pdf", *counter);
//            Cairo * cairo = new Cairo(filename);
//            map->draw_map(cairo, generations, *counter, generations);
//            cairo->finish();
//        }

        //copy copy into pop
        for (int l = 0; l < pop_size; l++) {
            for (int m = 0; m < N; m++) {
                pop[l][m] = copy[l][m];
            }
        }

        generations++;
        if (generations > max_generations) {
            return 0;
        }
    }

    return generations;

}

void GeneticAlgorithm::init_pop() {
    for (int i = 0; i < pop_size; i++) {
        for (int j = 0; j < N; j++) {
            pop[i][j] = (rand() % num_colors) + 1;
        }
    }
}

int GeneticAlgorithm::calc_fitness(int indiv) {
    return map->num_conflicts();
}

int GeneticAlgorithm::tournament_select() {
    int sel_x = (rand() % pop_size);
    int sel_y = (rand() % pop_size);
    int x_conf;
    int y_conf;

    map->set_all_colors(pop[sel_x]);
    x_conf = map->num_conflicts();

    map->set_all_colors(pop[sel_y]);
    y_conf = map->num_conflicts();

    if (x_conf < y_conf) {
        return sel_x;
    } else {
        return sel_y;
    }
}

void GeneticAlgorithm::crossover(unsigned int* x, unsigned int* y) {
    unsigned int hold [N];
    int cross_point = (rand() % (N - 2)) + 1;
    for (int i = 0; i < N; i++) {
        if (i < cross_point) {
            hold[i] = x[i];
            x[i] = y[i];
            y[i] = hold[i];
        }
    }
}

void GeneticAlgorithm::mutate(unsigned int* x) {

    for (int i = 0; i < N; i++){
        if ((float(rand())/RAND_MAX) < mut_rate) {
            x[i] = (rand() % num_colors) + 1;
            map->num_writes++;
        }
    }
}

