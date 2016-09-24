/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   backtracking.h
 * Author: byrdie
 *
 * Created on September 20, 2016, 2:18 PM
 */

#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include "map_data_types.h"




bool backtrack(Map * map, const unsigned int k, const unsigned int index, int* counter, int max_depth, bool draw_steps);
bool backtrack_forward(Map * map, uint index, int* counter, int max_depth, bool draw_steps);
bool forward_check(Map * map, uint index, uint color, bool draw_steps, int * counter);
bool undo_forward_check(Map * map, uint index, uint old_colors[]);

bool backtrack_mac(Map * map, uint index, int* counter, int max_depth, bool draw_steps);
bool ac3(Map * map, uint index, Graph_edge * queue[], uint qlen, int * counter, bool draw_steps);
bool undo_ac3(Map * map, uint old_colors[]);
bool revise(Map * map, int x_i, int x_j, int * counter, bool draw_steps);

#endif /* BACKTRACKING_H */

