/* 
 * Arm3d
 * Simple window filter for the inputs
 * Implemented with a "ring buffer"
 *
 * If we wanted to, it would be pretty easy to weight the filter
 * 
 * TODO: Per buffer lengths
 * TODO: Make sure it works with arduino (Might have to make it a class?)
 * TODO: Make sure we can instantiate multiple buffers (malloc maybe, or with classes idk)
 * TODO: Weighted rolling average
 * TODO: Properly test __EVERYTHING__
 *
 * Kyle Montemayor
 * kmonte@umd.edu
 */
#ifndef __FILTER_H__
#define __FILTER_H__

/*
 * How large the buffer is
 * Needs to be tweaked
 */
#define WINDOW_LENGTH 16

/*
 * Computes and returns the average in the buffer
 * I think it's better to computer it here vs in 
 * get_average() because we should be updating the
 * buffer more than we poll it
 *
 * If not then we can computer the average as we add new values
 *
 */
float get_average();

/*
 * Adds a new value to the buffer
 * Will overwrite old values
 * really not exciting, maybe have
 * it return the total number of
 * items that have ever been put in
 * the buffer
 */
void add_value(short);

#endif
