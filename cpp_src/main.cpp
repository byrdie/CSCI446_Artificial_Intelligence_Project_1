/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on September 19, 2016, 10:37 AM
 */

#include <cstdlib>
#include <string>
#include <chrono>


#include "cairo_int.h"
#include "map_problem_gen.h"
#include "backtracking.h"
#include "genetic.h"



using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
   //ga options
    const int pop_size = 1000;
    const int mut_rate = 30;
    const int N = 100;
    init_rand();

    Cairo * cairo = new Cairo();

    Map * map = problem_gen(N, WIDTH, cairo);

    map->clean_map();

    auto t1 = chrono::high_resolution_clock::now();
    backtrack(map, 4, 0);
    auto t2 = chrono::high_resolution_clock::now();
    
            
    cout << "Number of reads: " << (float) map->num_reads << endl;
    cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    cout << "Number of writes: " << (float) map->num_writes << endl;
    cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    
    
    map->clean_map();
    GeneticAlgorithm * ga = new GeneticAlgorithm(map, pop_size, mut_rate, N, 4);
    
    t1 = chrono::high_resolution_clock::now();
    int num_runs=ga->run();
    t2 = chrono::high_resolution_clock::now();
    printf("\n\n");
    cout << "Number of reads: " << (float) map->num_reads << endl;
    cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    cout << "Number of writes: " << (float) map->num_writes << endl;
    cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    cout << "Number of generations: " << (int) num_runs << endl;
    
    map->draw_map(cairo);


    cairo->finish();

    return 0;
}

