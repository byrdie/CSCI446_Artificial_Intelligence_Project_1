//
// Created by byrdie on 9/18/16.
//

#include "map_problem_gen.h"
#include "map_data_types.h"

bool does_cross(Graph_edge * line1, Graph_edge * line2)
{
    float p0_x = line1->start_point->x;
    float p0_y = line1->start_point->y;
    float p1_x = line1->end_point->x;
    float p1_y = line1->end_point->y;
    float p2_x = line2->start_point->x;
    float p2_y = line2->start_point->y;
    float p3_x = line2->end_point->x;
    float p3_y = line2->end_point->y;

    if(p0_x == p2_x && p0_y == p2_y && p1_x == p3_x && p1_y == p3_y) {
        return false;
    }

    float s1_x = p1_x - p0_x;
    float s1_y = p1_y - p0_y;
    float s2_x = p3_x - p2_x;
    float s2_y = p3_y - p2_y;

    if ((-s2_x * s1_y + s1_x * s2_y) == 0.0 ||  (-s2_x * s1_y + s1_x * s2_y) == 0.0){
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
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

void init_rand_seed(unsigned int seed){
    srand(seed);
}

void init_rand(){
    unsigned int seed = time(NULL);
    srand(seed);
    printf("Seed: %u", seed);
}