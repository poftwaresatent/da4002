#ifndef ITADS_EX7_CLOCKMS_H
#define ITADS_EX7_CLOCKMS_H

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

#endif /* ITADS_EX7_CLOCKMS_H */
