//
// Created by byrdie on 9/18/16.
//

#ifndef CPP_SRC_MAP_PROBLEM_GEN_H
#define CPP_SRC_MAP_PROBLEM_GEN_H

#include <iostream>
#include <random>
#include "map_data_types.h"

#include <string>

Map problem_gen(int num_vert, int win_sz);

std::default_random_engine init_rand();

#endif //CPP_SRC_MAP_PROBLEM_GEN_H
