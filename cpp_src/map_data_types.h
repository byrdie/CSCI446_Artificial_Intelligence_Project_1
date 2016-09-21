//
// Created by byrdie on 9/18/16.
//

#ifndef CPP_SRC_MAP_DATA_TYPES_H
#define CPP_SRC_MAP_DATA_TYPES_H

enum Color{
    nocolor,
    red,
    green,
    blue,
    purple,
    black,
}; 

#include <iostream>
#include <cmath>
#include "cairo_int.h"



class Graph_point;
class Map;
class Graph_edge;
class Point;
class Cairo;


class Point {
public:
    float x;
    float y;
    Point(float X, float Y);
};



class Graph_edge{
public:
    Graph_point * start_point;
    Graph_point * end_point;
    float distance;
    bool checked;
    float theta;
    Graph_edge(Graph_point * st_pt, Graph_point * end_pt);
    float find_length();
};

class Graph_point {
public:
    Map * map;
    Point * pt;
    Graph_edge ** edges;
    int num_edges;
    int index;  // Index of the point in the graph
    Graph_edge ** all_edges;
    Point ** poly;
    int num_poly_vert;
    int conflicts;
    int color_reads;
    int color_writes;
    Graph_point(int N, int i, Point * point);
    void add_edge(Graph_edge * edge);
    void set_color(Color col);
    Color get_color();
    bool has_conflicting_neighbors();

private:
    Color color;
};

class Map {
public:
    Graph_point ** graph;
    int ** matrix;
    unsigned int * colors;
    unsigned int N;
    long int num_reads;
    long int num_writes;
    Map(const unsigned int num_vert, Graph_point ** g, int ** mat, unsigned int * cols);
    void draw_map(Cairo * cairo);
    void clean_map();
    bool has_conflicting_neighbors(int i);
    void set_color(int index ,int col);
    int get_color(int index);
};

#endif //CPP_SRC_MAP_DATA_TYPES_H
