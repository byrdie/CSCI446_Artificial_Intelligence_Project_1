
#include "backtracking.h"

using namespace std;

bool backtrack(Map * map, const unsigned int k, const unsigned int index, int* counter, int max_depth) {
    *counter+=1;
   
    if (index == map->N) {
        return true;
    }
    
    if( *counter > max_depth){
        return true;
    }

    // Loop through all color combinations
    for (int j = 1; j < k + 1; j++) {

        map->set_color(index, j); // Set the color of this node

        // Logic for recursive call
        if (map->has_conflicting_neighbors(index)) {
            continue;
        } else {
            if (backtrack(map, k, index + 1, counter, max_depth)) {
                return true;
            } else {
                continue;
            }
        }
    }
    map->set_color(index, nocolor); // reset the color of this node
    return false;
}

bool backtrack_forward(Map * map, uint index, int* counter, int max_depth) {
    *counter+=1;
    if (index == map->N) {
        return true;
    }
    if( *counter > max_depth){
        return true;
    }
    uint num_e = map->graph[index]->num_edges;
    uint old_colors[num_e];
    for (int j = 0; j < num_e; j++) {
        old_colors[j] = map->get_color(map->matrix[index][j]);
    }

    uint current_color = map->get_color(index);

    if (current_color & RED) {
        uint new_color = RED;

        if (forward_check(map, index, new_color)) {
            map->set_color(index, new_color);
            if (backtrack_forward(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_forward_check(map, index, old_colors);
    }
    if (current_color & GREEN) {
        uint new_color = GREEN;

        if (forward_check(map, index, new_color)) {
            map->set_color(index, new_color);
            if (backtrack_forward(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_forward_check(map, index, old_colors);
    }
    if (current_color & BLUE) {
        uint new_color = BLUE;

        if (forward_check(map, index, new_color)) {
            map->set_color(index, new_color);
            if (backtrack_forward(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_forward_check(map, index, old_colors);
    }
    if (current_color & PURPLE) {
        uint new_color = PURPLE;

        if (forward_check(map, index, new_color)) {
            map->set_color(index, new_color);
            if (backtrack_forward(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_forward_check(map, index, old_colors);
    }

    //    cout << index << ", ";

    map->set_color(index, current_color);
    return false;


}

bool forward_check(Map * map, uint index, uint color) {

    int num_e = map->graph[index]->num_edges;

    for (int j = 0; j < num_e; j++) {
        uint color_set = map->get_color(map->matrix[index][j]);
        uint new_color_set = ~((~color_set) | (color));
        map->set_color(map->matrix[index][j], new_color_set);
        if (new_color_set == 0) {
            return false;
        }

    }
    return true;

}

bool undo_forward_check(Map * map, uint index, uint old_colors[]) {

    int num_e = map->graph[index]->num_edges;

    for (int j = 0; j < num_e; j++) {
        map->set_color(map->matrix[index][j], old_colors[j]);
    }

}

bool backtrack_mac(Map * map, uint index, int* counter, int max_depth) {
    *counter+=1;
    if (index == map->N) {
        return true;
    }
    if( *counter > max_depth){
        return true;
    }

    uint old_colors[map->N];
    for (int j = 0; j < map->N; j++) {
        old_colors[j] = map->get_color(j);
    }

    Graph_edge * queue[map->N * map->N];
    uint q_len = 0;
    for (int j = 0; j < map->graph[index]->num_edges; j++) {
//        if (map->get_color(map->matrix[index][j]) == NOCOLOR) {
            queue[q_len] = map->graph[index]->edges[j];
            q_len++;
//        }
    }

    uint current_color = map->get_color(index);

    if (current_color & RED) {
        uint new_color = RED;
        map->set_color(index, new_color);
        if (ac3(map, index, queue, q_len)) {
            if (backtrack_mac(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_ac3(map, old_colors);
    }
    if (current_color & GREEN) {
        uint new_color = GREEN;
        map->set_color(index, new_color);
        if (ac3(map, index, queue, q_len)) {
            if (backtrack_mac(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_ac3(map, old_colors);
    }
    if (current_color & BLUE) {
        uint new_color = BLUE;
        map->set_color(index, new_color);
        if (ac3(map, index, queue, q_len)) {
            if (backtrack_mac(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_ac3(map, old_colors);
    }
    if (current_color & PURPLE) {
        uint new_color = PURPLE;
        map->set_color(index, new_color);
        if (ac3(map, index, queue, q_len)) {
            if (backtrack_mac(map, index + 1, counter, max_depth)) {
                return true;
            }
        }
        undo_ac3(map, old_colors);
    }


    map->set_color(index, current_color);
    return false;
}

bool ac3(Map * map, uint index, Graph_edge * queue[], uint qlen) {

    int q_i = 0; //queue index
    while (qlen - q_i > 0) {
        Graph_edge * next_edge = queue[q_i];
        q_i++;
        int i = next_edge->end_point->index;
        int j = next_edge->start_point->index;

        if (revise(map, i, j)) {
            if (map->get_color(i) == 0) {
                return false;
            }
            for (int k = 0; k < map->graph[i]->num_edges; k++) {
                queue[qlen] = map->graph[i]->edges[k];
                qlen++;
            }
        }
    }
    return true;

}

bool undo_ac3(Map * map, uint old_colors[]) {


    for (int j = 0; j < map->N; j++) {
        map->set_color(j, old_colors[j]);
    }

}

bool revise(Map * map, int i, int j) {
    bool revised = false;


    uint current_colors_i = map->get_color(i);
    uint test_color_i = 0xF0000000;

    while (test_color_i != 0) {
        if (current_colors_i & test_color_i) { // test color is in the domain
            uint current_colors_j = map->get_color(j);
            uint test_color_j = 0xF0000000;
            bool no_value = true;
            while (test_color_j != 0) {
                if (current_colors_j & test_color_j) {
                    if (test_color_i != test_color_j) {
                        no_value = false;
                        break;
                    }
                }
                test_color_j = test_color_j >> 8; // Move to the next color
            }
            if (no_value) { // If no value
                uint new_color_set = ~((~current_colors_i) | (test_color_i));
//                cout << hex << new_color_set << endl;
                map->set_color(i, new_color_set);
                revised = true;
            }
        }
        test_color_i = test_color_i >> 8; // Move to the next color
    }
    return revised;

}