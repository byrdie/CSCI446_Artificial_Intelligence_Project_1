//
// Created by byrdie on 9/18/16.
//

#include "map_data_types.h"
Map::Map(Point * g){
    graph = g;
}

Point::Point(float X, float Y){
    x = X;
    y = Y;
}

Graph_point::Graph_point(Point * point){
    map = NULL;
    pt = point;
    edges = NULL;

}

Graph_edge::Graph_edge(Point * start_pt, Point * end_pt, float dist) {
    start_point = start_pt;
    end_point = end_pt;
    distance = dist;
    checked = false;
    theta = 0;
}
