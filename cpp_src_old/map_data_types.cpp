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

Graph_point::Graph_point(){
    map = NULL;
    pt = NULL;
    edges = NULL;

}

Graph_edge::Graph_edge() {
    start_point = NULL;
    end_point = NULL;
    distance = 0;
    checked = false;
    theta = 0;
}
