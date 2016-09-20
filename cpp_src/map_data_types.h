//
// Created by byrdie on 9/18/16.
//

#ifndef CPP_SRC_MAP_DATA_TYPES_H
#define CPP_SRC_MAP_DATA_TYPES_H

#include <iostream>
#include <cmath>
enum Color{
    red,
    green,
    blue,
    purple
}; 

class Graph_point;

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
    Graph_edge();
    void find_length();
};

class Graph_point {
public:
//    Map * map;
    Point * pt;
    Graph_edge * edges;
    int conflicts;
    int color_reads;
    int color_writes;
    Graph_point();

private:
    int color;
};

class Map {
public:
    Graph_point * graph;
    Map(Graph_point * g);
};

#endif //CPP_SRC_MAP_DATA_TYPES_H
