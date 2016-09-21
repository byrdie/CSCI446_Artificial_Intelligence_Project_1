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
#include "gnuplot-iostream.h"


using namespace std;

int main(int argc, char** argv) {

    // 1474440327
    init_rand();

    Cairo * cairo = new Cairo();
    
    float reads[10][2];
    float writes[10];

    Map * map;
    for (int i = 0; i < 10; i++) {
        
        int N = (i+1) * 3;
        map = problem_gen(N, WIDTH, cairo);

        map->clean_map();

        auto t1 = chrono::high_resolution_clock::now();
        //    backtrack(map, 4, 0, false);
        cout << backtrack_mac(map, 0) << endl;
        auto t2 = std::chrono::high_resolution_clock::now();

        reads[i][0] = (map->num_reads);
        reads[i][1] = N;
        
        cout << "Number of reads: " << (float) map->num_reads << endl;
        cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
        cout << "Number of writes: " << (float) map->num_writes << endl;
        cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
        cout << endl;
    }

    Gnuplot gp;
    
    gp << "set terminal pdfcairo \n";
    gp << "set output 'graph_test.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "plot '-' with lines title 'reads' \n";
    gp.send2d(reads);
    



    map->draw_map_bitwise(cairo);

    cairo->finish();

    return 0;
}

