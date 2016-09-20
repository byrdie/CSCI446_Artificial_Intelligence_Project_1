//
// Created by byrdie on 9/18/16.
//

#ifndef CPP_SRC_MAP_PROBLEM_GEN_H
#define CPP_SRC_MAP_PROBLEM_GEN_H


#include <iostream>
#include "map_data_types.h"
#include "cairo_int.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cairo/cairo.h>
#include "map_problem_gen.h"
#include "map_data_types.h"

Map problem_gen(int num_vert, int win_sz, Cairo * cairo);
bool does_cross(Graph_edge * line1, Graph_edge * line2);
void init_rand_seed(int seed);
void init_rand();
void sort_edges_by_angle(int N, Graph_point * graph[]);
void sort_edges_by_length(int N, Graph_point * graph[]);
void elim_crossing(int N, Graph_point * graph[], int num_edges, Graph_edge * all_edges[]);

#endif //CPP_SRC_MAP_PROBLEM_GEN_H




