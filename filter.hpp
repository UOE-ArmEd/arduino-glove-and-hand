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
class Filter{
    /*
     * How large the buffer is
     * Needs to be tweaked
     */
     #define WINDOW_LENGTH 16

   public:
        /*
         * Computes and returns the average in the buffer
         * I think it's better to computer it here vs in
         * get_average() because we should be updating the
         * buffer more than we poll it
         *
         * If not then we can compute the average as we
         * add new values
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
        void add_value(unsigned int);


        /*
         * Returns totals number of elements
         * that have ever been in the filter
         * Mostly for debugging, but might 
         * be useful otherwise
         */

        int total_elements();

    private:
        /*
         * Using shorts because I'm pretty sure the inputs are 10 bit
         * Might want to have dynamic sized buffers in the future
         */
        short buffer[WINDOW_LENGTH];
        /*
         * The weights if we want to treat this as a FIR
         * The weights are in reverse order, eg the weight
         * for the most recent element is the last on in the
         * array
         * 
         * TODO: TUNE THIS
         */
        float weights[WINDOW_LENGTH] = {0.2, 0.2, 0.2, 0.2
                                        0.4, 0.4, 0.4, 0.4
                                        0.6, 0.6, 0.6, 0.6
                                        0.8, 0.8, 1.0, 1.0};

        /*
         * Count of how many total items have been put in the buffer
         * Also used to keep track of the last item added
         *
         */
        int items = 0;

};
#endif
