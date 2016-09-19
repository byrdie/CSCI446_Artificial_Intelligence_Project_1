//
// Created by byrdie on 9/18/16.
//

#ifndef CPP_SRC_MAP_DATA_TYPES_H
#define CPP_SRC_MAP_DATA_TYPES_H

#include <iostream>



class Point {
public:
    float x;
    float y;
    Point(float X, float Y);
};

class Map {
public:
    Point * graph;
    Map(Point * g);
};

class Graph_edge{
public:
    Point * start_point;
    Point * end_point;
    float distance;
    bool checked;
    float theta;
    Graph_edge();
};

class Graph_point {
public:
    Map * map;
    Point * pt;
    Graph_edge * edges;
    int conflicts;
    int color_reads;
    int color_writes;
    Graph_point();

private:
    int color;
};

#endif //CPP_SRC_MAP_DATA_TYPES_H
