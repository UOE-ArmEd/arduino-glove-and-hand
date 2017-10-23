/* 
 * Arm3d
 * Simple window filter for the inputs
 * Implemented with a "ring buffer"
 *
 * If we wanted to, it would be pretty easy to weight the filter
 * 
 * Kyle Montemayor
 * kmonte@umd.edu
 */
#ifndef __FILTER_H__
#define __FILTER_H__

#define WINDOW_LENGTH 16
/*
 * Returns the average of the buffer
 */
float get_average();

/*
 * Adds a new value to the buffer
 * Currently computes the average here, 
 * though I think it's weird for this to
 * return anything other than a success
 */
void add_value(short);

#endif
