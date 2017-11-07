/*
 * Arm3d
 *
 * Kyle Montemayor
 * kmonte@umd.edu
 */

#include "filter.hpp"

#define MIN(x,y) ((x < y) ? x : y)
float Filter::get_average(){
    float sum = 0.0;
    int limit = MIN(items, WINDOW_LENGTH);

    for(int i = limit-1; i >= 0; i--){
        sum += weights[i]*buffer[(i+items)%WINDOW_LENGTH];
    }

    return sum/limit;
}
#undef MIN

void Filter::add_value(unsigned int val){
    // DW about it
    buffer[items++%WINDOW_LENGTH] = val;
}

int Filter:total_elements(){
    return items;
}
