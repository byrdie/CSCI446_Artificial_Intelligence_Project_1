//
// Created by byrdie on 9/18/16.
//
#include "map_problem_gen.h"
#include <cairo/cairo.h>

using namespace std;

Map problem_gen(int num_vert, int win_sz, Cairo * cairo) {

    int N = num_vert + 4;
    int margin = 20;

    Graph_point * graph = new Graph_point[N];
    Graph_point polygraph[N];
    Graph_edge all_edges[N * N];



    // Fill the list of points with random location
    for (int i = 4; i < N; ++i) {
        float x_pt = i * 20;
        float y_pt = i * 20;

        
        
        Point * next_pt = new Point(x_pt, y_pt);
        graph[i].pt = next_pt;
        polygraph[i].pt = next_pt;
        
        cairo->draw_point(next_pt);
    }

    // Create complete graph
    for (int i = 4; i < N; ++i) {
        Graph_edge * edges = new Graph_edge[N];
        for (int j = 4; j < N; ++j) {

        }
    }


}
