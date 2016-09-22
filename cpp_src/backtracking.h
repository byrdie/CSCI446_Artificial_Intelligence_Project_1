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




bool backtrack(Map * map, const unsigned int k, const unsigned int index);
bool backtrack_forward(Map * map, uint index);
bool forward_check(Map * map, uint index, uint color);
bool undo_forward_check(Map * map, uint index, uint old_colors[]);

bool backtrack_mac(Map * map, uint index);
bool ac3(Map * map, uint index, Graph_edge * queue[], uint qlen);
bool undo_ac3(Map * map, uint old_colors[]);
bool revise(Map * map, int x_i, int x_j);

#endif /* BACKTRACKING_H */

