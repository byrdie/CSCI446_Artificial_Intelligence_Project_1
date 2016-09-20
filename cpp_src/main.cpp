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

#include "cairo_int.h"
#include "map_problem_gen.h"



using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    init_rand(1474388194);
    
    Cairo * cairo = new Cairo();
    
    problem_gen(100, WIDTH, cairo);
            
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

