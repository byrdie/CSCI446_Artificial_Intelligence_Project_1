//
// Created by byrdie on 9/18/16.
//

#ifndef CPP_SRC_MAP_PROBLEM_GEN_H
#define CPP_SRC_MAP_PROBLEM_GEN_H
#endif //CPP_SRC_MAP_PROBLEM_GEN_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "map_data_types.h"

bool does_cross(Graph_edge * line1, Graph_edge * line2);
void init_rand_seed(int seed);
void init_rand();
void sort_edges_by_angle(int N, Graph_point * graph);