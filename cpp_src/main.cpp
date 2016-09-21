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
    const int pop_size = 10;
    const int mut_rate = 20;
    const int N = 10;
    init_rand();

    Cairo * cairo = new Cairo();

    Map * map = problem_gen(N, WIDTH, cairo);

    map->clean_map();

    auto t1 = chrono::high_resolution_clock::now();
    backtrack(map, 4, 0);
    auto t2 = std::chrono::high_resolution_clock::now();
    
    GeneticAlgorithm * ga = new GeneticAlgorithm(map, pop_size, mut_rate, N, 4);
            
    cout << "Number of reads: " << (float) map->num_reads << endl;
    cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    cout << "Number of writes: " << (float) map->num_writes << endl;
    cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;

    map->draw_map(cairo);

    //    Color mycolor = purple;
    //    int N = 10;
    //    Point ** graph;
    //    graph = new Point* [N];
    //    for (int i = 0; i<N; i++){
    //        graph[i] = new Point(float(rand()%100), float(rand()%100) );
    //    }
    //    cairo->draw_poly(graph, N, mycolor);
    cairo->finish();

    return 0;
}

