//
// Created by byrdie on 9/18/16.
//

#include "map_problem_gen.h"


using namespace std;

Map problem_gen(int num_vert, int win_sz, Cairo * cairo) {


    int N = num_vert + 4;
    int margin = 50;

    Graph_point ** graph = new Graph_point * [N];
    Graph_point ** polygraph = new Graph_point * [N];
    Graph_edge ** all_edges = new Graph_edge * [N * N];



    // Fill the list of points with random location
    for (int i = 4; i < N; ++i) {
        int x_pt = rand() % (win_sz - 2 * margin) + margin;
        int y_pt = rand() % (win_sz - 2 * margin) + margin;



        Point * next_pt = new Point(x_pt, y_pt);
        graph[i] = new Graph_point(N, next_pt);
        polygraph[i] = new Graph_point(N, next_pt);

        cairo->draw_point(next_pt);
    }

    // Create complete graph
    for (int i = 4; i < N; ++i) {
        Graph_point * this_point = graph[i];
        Graph_edge ** edges = new Graph_edge*[N - 5];
        int k = 0;
        for (int j = 4; j < N; ++j) {
            if (j != i) { // Don't connect vertex to itself
                edges[k] = new Graph_edge(this_point, graph[j]);
                k++;
            }
        }
        sort_edges_by_length(N - 4 - 1, edges);
        this_point->all_edges = edges;
    }

    // Eliminate crossings
    int num_total_edges = elim_crossings(4, N, graph, 0, all_edges);

    cout << num_total_edges << endl;

    for (int i = 4; i < N; i++) {
        cout << i << endl;
        for (int j = 0; j < graph[i]->num_edges; j++) {
            cout << graph[i]->edges[j]->distance << endl;
            cairo->draw_line(graph[i]->edges[j]);
        }
    }




}

int elim_crossings(const int start, const int N, Graph_point * graph[], int num_total_edges, Graph_edge * all_edges[]) {

    // Variables to track whether it's time to exit the loop
    bool escape = true;
    bool vertex_escape[N];
    fill_n(vertex_escape, N, false);
    
    int num_edges = N - start - 1;

    // Loop until all possible edges are connected
    while (escape) {
        int i = (rand() % (N-start)) + start;
        Graph_edge ** edges = graph[i]->all_edges;

        for (int j = 0; j < num_edges; j++) {
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
                    if (crosses == false) {
                        graph[i]->add_edge(test_edge);
                        all_edges[num_total_edges] = test_edge;
                        num_total_edges += 1;
                        break;
                    }
                }
            }
            ;

            // set variable if we've made a full trip through the for loop
            if (j == (num_edges - 1)) {
                vertex_escape[i] = true;
            }
        }
        int num_vert_escape = 0;
        for (int j = start; j < N; j++) {
            if (vertex_escape[j]) {
                num_vert_escape++;
            }
        }
        if (num_vert_escape == N - start) {
            escape = false;
        }
    }
    return num_total_edges;
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

    if ((-s2_x * s1_y + s1_x * s2_y) == 0.0 or (-s2_x * s1_y + s1_x * s2_y) == 0.0) {
        return false;
    }

    float s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    float t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    float i_x = p0_x + (t * s1_x);
    float i_y = p0_y + (t * s1_y);

    if (s > 0.0 and s < 1.0 and t > 0.0 and t < 1.0) {

//        return true;
        if ((i_x == p0_x and i_y == p0_y) or (i_x == p1_x and i_y == p1_y) or (i_x == p2_x and i_y == p2_y) or (i_x == p3_x and i_y == p3_y)) {
            return false;
        } else {
            return true;
        }

    } else {
        return false;
    }
}

void init_rand(unsigned long int seed) {
    srand(seed);
}

void init_rand() {
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u\n", seed);
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

void sort_edges_by_length(int N, Graph_edge * edges[]) {

    std::sort(edges, edges + N,
            [](Graph_edge * a, Graph_edge * b) -> float {
                return a->distance < b->distance; });
}

