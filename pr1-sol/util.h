/*
 * util.h
 *
 * Header file which declares some utility functions.
 */

#ifndef ITADS_PROJ1_UTIL_H
#define ITADS_PROJ1_UTIL_H

/*
 * Return the number of milliseconds since the first time you called
 * this function. In other words, when you first call this function,
 * it returns zero. From then on, it returns the number of
 * milliseconds that have elapsed since last time you called this
 * function.
 *
 * Internally, it uses gettimeofday from sys/time.h as a workaround
 * for systems that do not provide a properly functioning clock
 * library call.
 */
double clockms (void);


/*
 * Create a duplicate of the given array. This allocates new memory,
 * so you are responsible for calling free on the returned pointer
 * after you are done with it.
 */
int * duplicate (int * arr, int len);

#endif /* ITADS_PROJ1_UTIL_H */
