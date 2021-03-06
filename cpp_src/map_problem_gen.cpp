//
// Created by byrdie on 9/18/16.
//

#include "map_problem_gen.h"


using namespace std;

Map * problem_gen(int num_vert, int win_sz) {


    int N = num_vert + 4;
    int margin = 50;

    Graph_point ** graph = new Graph_point * [N];
    Graph_point ** polygraph = new Graph_point * [N];
    Graph_edge ** all_edges = new Graph_edge * [N * N];



    // Fill the list of points with random location
    for (int i = 0; i < num_vert; ++i) {

        int x_pt;
        int y_pt;

        bool escape = false;
        while (!escape) {
            x_pt = rand() % (win_sz - 2 * margin) + margin;
            y_pt = rand() % (win_sz - 2 * margin) + margin;

            bool point_escape = true;
            for (int j = 0; j < i; j++) {
                if (x_pt == graph[j]->pt->x and y_pt == graph[j]->pt->y) {
                    point_escape = false;
                    break;
                }
            }
            escape = point_escape;
        }

        Point * next_pt = new Point(x_pt, y_pt);
        graph[i] = new Graph_point(N, i, next_pt);
        polygraph[i] = new Graph_point(N, i, next_pt);

    }

    // Create complete graph
    for (int i = 0; i < num_vert; ++i) {
        Graph_point * this_point = graph[i];
        Graph_edge ** edges = new Graph_edge*[N];
        int k = 0;
        for (int j = 0; j < num_vert; ++j) {
            if (j != i) { // Don't connect vertex to itself
                edges[k] = new Graph_edge(this_point, graph[j]);
                k++;
            }
        }
        sort_edges_by_length(num_vert - 1, edges);
        this_point->all_edges = edges;
    }

    // Eliminate crossings
    int num_total_edges = elim_crossings(num_vert, graph, 0, all_edges);



    // Initialize corners for polygon tracing
    graph[num_vert] = new Graph_point(N, num_vert, new Point(10, 10));
    graph[num_vert + 1] = new Graph_point(N, num_vert + 1, new Point(10, win_sz - 10));
    graph[num_vert + 2] = new Graph_point(N, num_vert + 2, new Point(win_sz - 10, 10));
    graph[num_vert + 3] = new Graph_point(N, num_vert + 3, new Point(win_sz - 10, win_sz - 10));
    polygraph[num_vert] = new Graph_point(N, num_vert, new Point(10, 10));
    polygraph[num_vert + 1] = new Graph_point(N, num_vert + 1, new Point(10, win_sz - 10));
    polygraph[num_vert + 2] = new Graph_point(N, num_vert + 2, new Point(win_sz - 10, 10));
    polygraph[num_vert + 3] = new Graph_point(N, num_vert + 3, new Point(win_sz - 10, win_sz - 10));

    // create list of all edges between corner nodes and graph
    for (int i = num_vert; i < N; i++) {
        Graph_point * this_point = graph[i];
        Graph_edge ** edges = new Graph_edge*[N - 1];
        int k = 0;
        for (int j = 0; j < N; j++) {
            if (j != i) { // Don't connect vertex to itself
                edges[k] = new Graph_edge(this_point, graph[j]);
                k++;
            }
        }
        sort_edges_by_length(N - 1, edges);
        this_point->all_edges = edges;
    }

    // Create list of all edges between graph and corner nodes
    for (int i = 0; i < num_vert; ++i) {
        Graph_point * this_point = graph[i];
        Graph_edge ** edges = new Graph_edge*[4];
        int k = 0;
        for (int j = num_vert; j < N; ++j) {
            edges[k] = new Graph_edge(this_point, graph[j]);
            k++;
        }
        sort_edges_by_length(4, edges);
        this_point->all_edges[N - 5] = edges[0];
        this_point->all_edges[N - 4] = edges[1];
        this_point->all_edges[N - 3] = edges[2];
        this_point->all_edges[N - 2] = edges[3];
    }

    // Eliminate crossings with the corners
    num_total_edges = elim_crossings(N, graph, num_total_edges, all_edges);

    // Sort the edges by angle for polygon generator
    sort_edges_by_angle(N, graph);



    // Construct polygon structure to represent graph
    for (int i = 0; i < num_vert; i++) {
        Graph_point * pt1 = graph[i];
        int num_e = pt1->num_edges;

        for (int j = 0; j < num_e; j++) {

            // Grab two adjacent edges
            Graph_edge * edge2 = pt1->edges[j];
            Graph_edge * edge3 = pt1->edges[(j + 1) % num_e];
            Graph_point * pt2 = edge2->end_point;
            Graph_point * pt3 = edge3->end_point;

            // Construct line to midpoint of each edge
            Graph_point * mid_pt = new Graph_point(N, num_e * 2, new Point(((pt1->pt->x + pt2->pt->x) / 2.0), ((pt1->pt->y + pt2->pt->y) / 2.0)));
            Graph_edge * new_edge = new Graph_edge(pt1, mid_pt);
            polygraph[i]->add_edge(new_edge);

            // Find centroid and add edge
            Point * next_center = centroid(pt1->pt, pt2->pt, pt3->pt);
            Graph_edge * next_edge = new Graph_edge(pt1, new Graph_point(N, 2 * num_e + 1, next_center));
            polygraph[i]->add_edge(next_edge);
            //            cairo->draw_point(next_center, red);
        }

        // Create list of vertices for polygons
        int num_pvert = polygraph[i]->num_edges;
        Point ** poly_verts = new Point * [num_pvert];
        for (int j = 0; j < num_pvert; j++) {
            poly_verts[j] = polygraph[i]->edges[j]->end_point->pt;
        }
        graph[i]->poly = poly_verts;
        graph[i]->num_poly_vert = num_pvert;


    }

    sort_edges_by_index(N, graph);

    // Trim off corners and edges connecting them
    for (int i = 0; i < num_vert; i++) {
        int num = graph[i]->num_edges;
        for (int j = 0; j < num; j++) {
            Point * end_pt = graph[i]->edges[j]->end_point->pt;
            int x = end_pt->x;
            if (x == 10 or x == win_sz - 10) {
                graph[i]->num_edges--;
            }
        }
    }

    sort_points_by_num_edges(num_vert, graph);
    for(int i = 0; i < num_vert; i++){
        graph[i]->index = i;
    }

    // Create a matrix of relationships for quick checking
    int ** matrix = new int * [num_vert];
    for (int i = 0; i < num_vert; i++) {
        matrix[i] = new int[graph[i]->num_edges];
        for (int j = 0; j < graph[i]->num_edges; j++) {
            matrix[i][j] = graph[i]->edges[j]->end_point->index;
        }
    }

    unsigned int * colors = new unsigned int[num_vert];
    for (int i = 0; i < num_vert; i++) {
        colors[i] = 0xF0F0F0F0;
    }

    return new Map(num_vert, graph, matrix, colors);

}

int elim_crossings(const int N, Graph_point * graph[], int num_total_edges, Graph_edge * all_edges[]) {

    // Variables to track whether it's time to exit the loop
    bool escape = true;
    bool vertex_escape[N];
    fill_n(vertex_escape, N, false);



    // Loop until all possible edges are connected
    while (escape) {
        int i = rand() % N;
        Graph_edge ** edges = graph[i]->all_edges;
        int num_edges = N - 1;

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
        for (int j = 0; j < N; j++) {
            if (vertex_escape[j]) {
                num_vert_escape++;
            }
        }
        if (num_vert_escape == N) {
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
            dx = graph[i]->edges[j]->end_point->pt->x - graph[i]->edges[j]->start_point->pt->x;
            dy = graph[i]->edges[j]->end_point->pt->y - graph[i]->edges[j]->start_point->pt->y;
            graph[i]->edges[j]->theta = atan2f(dy, dx) + M_PI;
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

void sort_edges_by_index(int N, Graph_point * graph[]) {
    int i, j;
    for (i = 0; i < N; i++) {

        std::sort(graph[i]->edges, graph[i]->edges + graph[i]->num_edges,
                [](Graph_edge * a, Graph_edge * b) -> float {
                    return a->end_point->index < b->end_point->index; });
    }
}

void sort_points_by_num_edges(int N, Graph_point * graph[]) {

    std::sort(graph, graph + N,
            [](Graph_point * a, Graph_point * b) -> int {
                return a->num_edges < b->num_edges; });




}

Point * centroid(Point * p1, Point * p2, Point * p3) {
    float X = 0;
    float Y = 0;

    X = (p1->x + p2->x + p3->x) / 3.0;
    Y = (p1->y + p2->y + p3->y) / 3.0;

    return new Point(X, Y);
}