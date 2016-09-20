
#include "map_data_types.h"

bool backtrack(Map * map, int k, int index) {
    
    Graph_point ** graph = map->graph;

    if (index == map->N) {
        return true;
    }

    Graph_point * next_pt = graph[index];

    // Loop through all color combinations
    for (int j = 1; j < k + 1; j++) {
        
        next_pt->set_color(static_cast<Color>(j));  // Set the color of this node
        
        // Logic for recursive call
        if(next_pt->has_conflicting_neighbors()){
            continue;
        } else {
            if(backtrack(map, k, index +1)){
                return true;
            } else {
                continue;
            }
        }
    }
    next_pt->set_color(nocolor);  // reset the color of this node
    return false;
}

