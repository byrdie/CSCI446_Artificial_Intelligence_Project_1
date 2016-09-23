//
// Created by byrdie on 9/18/16.
//

#include "map_data_types.h"


Map::Map(const unsigned int num_vert, Graph_point ** g, int ** mat, unsigned int * cols) {
    N = num_vert;
    graph = g;
    matrix = mat;
    colors = cols;
    num_reads = 0;
    num_writes = 0;
}

void Map::clean_map() {
    
    for (int i = 0; i < N; i++) {
        Graph_point * pt = graph[i];
        set_color(i, 0);
        pt->set_color(nocolor);
        pt->color_reads = 0;
        pt->color_writes = 0;
        pt->conflicts = 0;
    }
}

void Map::clean_map_bitwise() {
    
    for (int i = 0; i < N; i++) {
        Graph_point * pt = graph[i];
        set_color(i, NOCOLOR);
        pt->set_color(nocolor);
        pt->color_reads = 0;
        pt->color_writes = 0;
        pt->conflicts = 0;
    }
}

void Map::draw_map(Cairo * cairo) {
    for (int i = 0; i < N; i++) {
        //                cout << i << endl;
        cairo->draw_poly(graph[i]->poly, graph[i]->num_poly_vert, static_cast<Color> (colors[i]));
        cairo->draw_point(graph[i]->pt, black);


        for (int j = 0; j < graph[i]->num_edges; j++) {

            cairo->draw_line(graph[i]->edges[j], black);
        }
    }
}

void Map::draw_map_bitwise(Cairo * cairo) {
    for (int i = 0; i < N; i++) {

        cairo->draw_poly(graph[i]->poly, graph[i]->num_poly_vert, colors[i]);

    }
    for (int i = 0; i < N; i++) {
        cairo->draw_point(graph[i]->pt, black);


        for (int j = 0; j < graph[i]->num_edges; j++) {

            cairo->draw_line(graph[i]->edges[j], black);
        }
    }

}

bool Map::has_conflicting_neighbors(int i) {
    for (int j = 0; j < graph[i]->num_edges; j++) {
        if (colors[i] == colors[matrix[i][j]]) {
            return true;
        }
        num_reads++;
    }
    return false;
}

void Map::set_color(int index, int col) {
    colors[index] = col;
    num_writes++;
}

int Map::get_color(int index) {
    num_reads++;
    return colors[index];
}

int Map::num_conflicting_neighbors(int j) {
    graph[j]->conflicts = 0;
    for (int i = 0; i < graph[j]->num_edges; i++) {
        num_reads++;
        if (colors[matrix[j][i]] == colors[j]) {
            graph[j]->conflicts++;
        }
    }
    return graph[j]->conflicts;
}

int Map :: num_conflicts(){
    
    int conflicts = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j , j < graph[i]->num_edges; j++ ){
            num_reads++;
            if (colors[i] == colors[matrix[i][j]]) {
                conflicts++;
            }
        }
    }
    return conflicts;
}


Point::Point(float X, float Y) {
    x = X;
    y = Y;
}

Graph_point::Graph_point(int N, int i, Point * point) {
    //    map = new Map;
    pt = point;
    edges = new Graph_edge * [N];
    all_edges = new Graph_edge * [N];
    num_edges = 0;
    index = i;

}

void Graph_point::set_color(Color col) {
    color = col;
    color_writes++;
}

Color Graph_point::get_color() {
    color_reads++;
    return color;
}

bool Graph_point::has_conflicting_neighbors() {
    for (int i = 0; i < num_edges; i++) {
        if (edges[i]->end_point->get_color() == color) {
            return true;
        }
    }
    return false;
}



Graph_edge::Graph_edge(Graph_point * st_pt, Graph_point * end_pt) {
    start_point = st_pt;
    end_point = end_pt;
    distance = find_length();
    checked = false;
    theta = 0;
}

void Graph_point::add_edge(Graph_edge * edge) {
    edges[num_edges] = edge;
    num_edges = num_edges + 1;
}

float Graph_edge::find_length() {
    float x1 = start_point->pt->x;
    float y1 = start_point->pt->y;
    float x0 = end_point->pt->x;
    float y0 = end_point->pt->y;

    return sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
}
