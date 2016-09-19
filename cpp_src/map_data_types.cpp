//
// Created by byrdie on 9/18/16.
//

#include "map_data_types.h"

Map::Map(Graph_point * g) {
    graph = g;
}

Point::Point(float X, float Y) {
    x = X;
    y = Y;
}

Graph_point::Graph_point() {
    map = NULL;
    pt = NULL;
    edges = NULL;
    num_edges = 0;
    all_edges = NULL;

}

Graph_edge::Graph_edge() {
    start_point = NULL;
    end_point = NULL;
    distance = 0;
    checked = false;
    theta = 0;
}

void Graph_point::add_edge(Graph_edge * edge){
    edges[num_edges] = edge;
}

void Graph_edge::find_length() {
    float x1 = start_point->pt->x;
    float y1 = start_point->pt->y;
    float x0 = end_point->pt->x;
    float y0 = end_point->pt->y;

    distance = sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
}
