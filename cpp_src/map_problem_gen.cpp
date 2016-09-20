//
// Created by byrdie on 9/18/16.
//

#include "map_problem_gen.h"


using namespace std;

Map problem_gen(int num_vert, int win_sz, Cairo * cairo) {

    cout << win_sz << "\n";

    int N = num_vert + 4;
    int margin = 50;

    Graph_point ** graph = new Graph_point * [N];
    Graph_point ** polygraph = new Graph_point * [N];
    Graph_edge ** all_edges = new Graph_edge * [N * N];



    // Fill the list of points with random location
    for (int i = 4; i < N; ++i) {
        float x_pt = ((float) rand()) / RAND_MAX * (win_sz - 2 * margin) + margin;
        float y_pt = ((float) rand()) / RAND_MAX * (win_sz - 2 * margin) + margin;



        Point * next_pt = new Point(x_pt, y_pt);
        graph[i] = new Graph_point(N, next_pt);
        polygraph[i] = new Graph_point(N, next_pt);

        cairo->draw_point(next_pt);
    }

    // Create complete graph
    for (int i = 4; i < N; ++i) {
        Graph_point * this_point = graph[i];
        for (int j = 4; j < N; ++j) {
            if (j != i) {   // Don't connect vertex to itself
                Graph_edge * edge = new Graph_edge(this_point, graph[j]);
                this_point->all_edges[this_point->num_edges] = edge;
                cairo->draw_line(edge);
            }
        }        
    }
    // Sort edges by length so we elimaninate crossings in the correct order
//    sort_edges_by_length(N, graph);



}

void elim_crossing(const int N, Graph_point * graph[], int num_total_edges, Graph_edge * all_edges[]) {

    // Variables to track whether it's time to exit the loop
    bool escape = true;
    bool vertex_escape[N];
    fill_n(vertex_escape, N, false);

    // Loop until all possible edges are connected
    while (escape) {
        int i = rand() % N;
        Graph_edge ** edges = graph[i]->all_edges;

        for (int j = 0; j < N - 1; j++) {
            Graph_edge * test_edge = edges[j];

            if (!test_edge->checked) { // proceed only if we haven't check this edge
                test_edge->checked = true;

                // Check that the test edge does not cross any current edges
                if (num_total_edges == 0) {
                    graph[i]->add_edge(test_edge);
                    all_edges[0] = test_edge;
                    num_total_edges += 1;
                    break;
                } else {
                    bool crosses = false;

                    for (int k = 0; k < num_total_edges; k++) {
                        if (does_cross(test_edge, all_edges[k])) {
                            crosses = true;
                            break;
                        }
                    }

                    if (!crosses) {
                        graph[i]->add_edge(test_edge);
                        all_edges[0] = test_edge;
                        num_total_edges += 1;
                        break;
                    }
                }
            }
            // set variable if we've made a full trip through the for loop
            if (j == (N - 1)){
                vertex_escape[i] = true;
            }
        }
        for(int j = 0; j < N; j++){
            escape = escape & vertex_escape[i];
        }
    }
}

bool does_cross(Graph_edge * line1, Graph_edge * line2) {
    float p0_x = line1->start_point->pt->x;
    float p0_y = line1->start_point->pt->y;
    float p1_x = line1->end_point->pt->x;
    float p1_y = line1->end_point->pt->y;
    float p2_x = line2->start_point->pt->x;
    float p2_y = line2->start_point->pt->y;
    float p3_x = line2->end_point->pt->x;
    float p3_y = line2->end_point->pt->y;

    if (p0_x == p2_x && p0_y == p2_y && p1_x == p3_x && p1_y == p3_y) {
        return false;
    }

    float s1_x = p1_x - p0_x;
    float s1_y = p1_y - p0_y;
    float s2_x = p3_x - p2_x;
    float s2_y = p3_y - p2_y;

    if ((-s2_x * s1_y + s1_x * s2_y) == 0.0 || (-s2_x * s1_y + s1_x * s2_y) == 0.0) {
        return false;
    }

    float s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    float t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    float i_x = p0_x + (t * s1_x);
    float i_y = p0_y + (t * s1_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {

        if ((i_x == p0_x && i_y == p0_y) || (i_x == p1_x && i_y == p1_y) || (i_x == p2_x && i_y == p2_y) ||
                (i_x == p3_x && i_y == p3_y)) {
            return false;
        } else {
            return true;
        }

    } else {
        return false;
    }
}

void init_rand_seed(unsigned int seed) {
    srand(seed);
}

void init_rand() {
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u", seed);
}

void sort_edges_by_angle(int N, Graph_point * graph[]) {
    int i, j;
    float dx, dy;
    for (i = 0; i < N; i++) {
        for (j = 0; j < graph[i]->num_edges; j++) {
            dx = graph[i]->edges[j]->end_point->pt->x;
            dy = graph[i]->edges[j]->end_point->pt->y;
            graph[i]->edges[j]->theta = atan2f(dy, dx);
        }

        std::sort(graph[i]->edges, graph[i]->edges + graph[i]->num_edges,
                [](Graph_edge * a, Graph_edge * b) -> float {
                    return a->theta < b->theta; });
    }
}

void sort_edges_by_length(int N, Graph_point * graph[]) {
    int i;
    for (i = 0; i < N; i++) {
        cout << graph[i]->num_edges << endl;
        std::sort(graph[i]->edges, graph[i]->edges + graph[i]->num_edges,
                [](Graph_edge * a, Graph_edge * b) -> float {
                    return a->distance < b->distance; });
    }
}

