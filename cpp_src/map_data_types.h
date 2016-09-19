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
    Graph_point * graph;
    Map(Graph_point * g);
};

class Graph_edge{
public:
    Point * start_point;
    Point * end_point;
    float distance;
    bool checked;
    float theta;
    Graph_edge(Point * start_pt, Point * end_pt, float distance);
};

class Graph_point {
public:
    Map * map;
    Point * pt;
    Graph_edge * edges;
    int conflicts;
    int color_reads;
    int color_writes;
    Graph_point(Point * point);

private:
    int color;
};

#endif //CPP_SRC_MAP_DATA_TYPES_H
