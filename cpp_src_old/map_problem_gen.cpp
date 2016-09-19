//
// Created by byrdie on 9/18/16.
//
#include "map_problem_gen.h"
#include "gnuplot_i.h"

using namespace std;

Map problem_gen(int num_vert, int win_sz){
    int N = num_vert + 4;
    int margin = 20;

    Graph_point * graph = new Graph_point[N];
    Graph_point polygraph[N];
    Graph_edge all_edges[N * N];

    Gnuplot g0;

    g0.cmd("set output '/home/byrdie/School/CSCI446_Artifical_Intelligence/CSCI446_Artificial_Intelligence_Project_1/cpp_src/test.eps'");

    // Fill the list of points with random location
    for (int i = 4; i < N; ++i) {
        float x_pt = i / N * win_sz;
        float y_pt = i / N * win_sz;

        Point * next_pt = new Point(x_pt, y_pt);
        graph[i].pt = next_pt;
        polygraph[i].pt = next_pt;
        string cmd_string = string("set object circle at ") + to_string(x_pt) + string(",") + to_string(y_pt) + string(" radius char 1.0 fillcolor rgb 'red' fillstyle solid noborder");
        cout << cmd_string;
        g0.cmd( cmd_string);
    }

    // Create complete graph
    for (int i = 4; i < N; ++i) {
        Graph_edge * edges = new Graph_edge[N];
        for (int j = 4; j < N; ++j) {
            
        }
    }


}
