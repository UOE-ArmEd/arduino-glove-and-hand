#include "filter.hpp"

#define MIN(x,y) ((x > y) ? x : y)
float Filter::get_average(){
    unsigned int sum = 0;
    unsigned int limit = MIN(items, WINDOW_LENGTH);

    for(unsigned int i = 0; i < limit; i++){
        sum += buffer[i];
    }

    return (float)sum/limit;
}
#undef MIN

void Filter::add_value(unsigned int val){
    // DW about it
    buffer[items++%WINDOW_LENGTH] = val;
}
