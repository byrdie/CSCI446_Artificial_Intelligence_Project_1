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

using namespace std;

int main(int argc, char** argv) ;
void backtrack_simple_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes);
void backtrack_mac_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes);
void backtrack_forward_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes);
vector<float> standard_deviation(vector<float> data);


#endif /* MAIN_H */

