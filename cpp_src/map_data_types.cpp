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

Graph_point::Graph_point(int N, Point * point) {
//    map = new Map;
    pt = point;
    edges = new Graph_edge * [N];
    all_edges = new Graph_edge * [N];
    num_edges = 0;

}

Graph_edge::Graph_edge(Graph_point * st_pt, Graph_point * end_pt) {
    start_point = st_pt;
    end_point = end_pt;
    distance = 0;
    checked = false;
    theta = 0;
}

void Graph_point::add_edge(Graph_edge * edge){
    edges[num_edges] = edge;
    num_edges = num_edges + 1;
}

void Graph_edge::find_length() {
    float x1 = start_point->pt->x;
    float y1 = start_point->pt->y;
    float x0 = end_point->pt->x;
    float y0 = end_point->pt->y;

    distance = sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
}
