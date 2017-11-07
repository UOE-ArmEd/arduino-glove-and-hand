/*
 * Arm3d
 *
 * Kyle Montemayor
 * kmonte@umd.edu
 */

#include "filter.hpp"

Filter::Filter(){
}

#define MIN(x,y) ((x > y) ? x : y)
float Filter::get_average(){
    float sum = 0.0;
    int limit = MIN(items, WINDOW_LENGTH);

    for(int i = 0; i < limit; i++){
        sum += buffer[(i+items)%WINDOW_LENGTH]*weights[i];
    }

    return sum/limit;
}
#undef MIN

void Filter::add_value(short val){
    // DW about it
    buffer[items++%WINDOW_LENGTH] = val;
}

int Filter:total_elements(){
    return items;
}

