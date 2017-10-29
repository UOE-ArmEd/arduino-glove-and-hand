#include "filter.hpp"

Filter::Filter(){
}

#define MIN(x,y) ((x > y) ? x : y)
float Filter::get_average(){
    int sum = 0;
    int limit = MIN(items, WINDOW_LENGTH);

    for(int i = 0; i < limit; i++){
        sum += buffer[i];
    }

    return (float)sum/limit;
}
#undef MIN

void Filter::add_value(short val){
    // DW about it
    buffer[items++%WINDOW_LENGTH] = val;
}



