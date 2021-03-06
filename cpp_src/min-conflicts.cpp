/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "min-conflicts.h"

int min_conflicts(Map * map, const unsigned int num_colors, unsigned long int max_steps, long int * counter, bool draw_steps) {
    int N = map->N;
    bool finished = false;
    int steps = 0;

    /*################
     * initialize map
     #################*/
    for (unsigned long int i = 0; i < N; i++) {
        map->colors[i] = (rand() % num_colors) + 1;
        map->num_writes += 1;
    }

    /*################
     * start main program loop
    #################*/
    for (unsigned long int i = 0; i < max_steps; i++) {
        steps++;
        //update conflicts
        for (int i = 0; i < N; i++) {
            map->num_conflicting_neighbors(i);
        }


        //find conflicting neighbors
        unsigned int con[N];
        int count = 0;
        int choice;
        for (int j = 0; j < N; j++) {
            if (map->graph[j]->conflicts > 0) {
                con[count] = j;
                count++;
            }
        }


        //make random choice
        choice = con[rand() % count];


        //find the best color
        int min_choice = 1;
        int cur_conflicts = map->num_conflicting_neighbors(choice);
        int hold = cur_conflicts;
        for (int j = 1; j < num_colors + 1; j++) {

            map->colors[choice] = j;
            map->num_writes += 1;
            if (map->num_conflicting_neighbors(choice) <= cur_conflicts) {
                cur_conflicts = map->num_conflicting_neighbors(choice);
                min_choice = j;
            }
        }


        //if conflict decrease not possible choose a random color
        if (cur_conflicts == hold) {
            min_choice = (rand() % num_colors) + 1;
        }


        //add choice to map
        map->colors[choice] = min_choice;
        map->num_writes += 1;

        *counter += 1;
        if (draw_steps) {
            char filename[100];
            sprintf(filename, "../results/min_conflicts/map_build/minconf_I%05ld.pdf", *counter);
            Cairo * cairo = new Cairo(filename);
            map->draw_map(cairo, i, *counter, i);
            cairo->finish();
        }

        //if done, return
        if (map->num_conflicts() == 0) {
            if (draw_steps) {
                for (int m = 0; m < 20; m++) {
                    *counter += 1;

                    char filename[100];
                    sprintf(filename, "../results/min_conflicts/map_build/minconf_I%05ld.pdf", *counter);
                    Cairo * cairo = new Cairo(filename);
                    map->draw_map(cairo, i, *counter, i);
                    cairo->finish();
                }
            }

            return steps;
        }

    }
    printf("steps %d\n", steps);
    return 0;
}

