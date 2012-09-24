#ifndef ITADS_EX7_RANDOM_H
#define ITADS_EX7_RANDOM_H

#include <sys/types.h>

void random_read (void * buf, size_t nbytes);
int random_uniform (int minval, int maxval);
void random_uniform_array  (int minval, int maxval, int * arr, size_t len);

#endif /* ITADS_EX7_RANDOM_H */
