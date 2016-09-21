
#include "map_data_types.h"

using namespace std;

bool backtrack(Map * map, const unsigned int k, const unsigned int index) {
    
//    Graph_point ** graph = map->graph;

    if (index == map->N) {
        return true;
    }

//    cout << index << endl;
    
//    Graph_point * next_pt = graph[index];

    // Loop through all color combinations
    for (int j = 1; j < k + 1; j++) {
        
        map->set_color(index, j);  // Set the color of this node
        
        // Logic for recursive call
        if(map->has_conflicting_neighbors(index)){
            continue;
        } else {
            if(backtrack(map, k, index + 1)){
                return true;
            } else {
                continue;
            }
        }
    }
    map->set_color(index, nocolor);  // reset the color of this node
    return false;
}

