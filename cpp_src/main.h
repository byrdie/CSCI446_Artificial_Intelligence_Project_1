/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.h
 * Author: byrdie
 *
 * Created on September 21, 2016, 5:16 PM
 */

#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <string>
#include <chrono>


#include "cairo_int.h"
#include "map_problem_gen.h"
#include "backtracking.h"
#include "gnuplot-iostream.h"
#include "min-conflicts.h"
#include "genetic.h"

using namespace std;

int main(int argc, char** argv) ;
void minconflicts_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k);
void backtrack_simple_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k);
void backtrack_mac_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k);
void backtrack_forward_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k);
void genetic_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k);
vector<float> standard_deviation(vector<float> data);
void print_time(std::chrono::time_point<std::chrono::system_clock> t1, std::chrono::time_point<std::chrono::system_clock> t2);


#endif /* MAIN_H */

