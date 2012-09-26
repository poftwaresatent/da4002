/*
 * random.h
 *
 * Utility functions to create random data.
 */

#ifndef ITADS_PROJ1_RANDOM_H
#define ITADS_PROJ1_RANDOM_H

#include <sys/types.h>

void random_read (void * buf, size_t nbytes);

int random_uniform (int minval, int maxval);

void random_uniform_array  (int minval, int maxval, int * arr, size_t len);

void random_chunkwise_array (int minval, int maxval, int * arr, size_t len,
			     size_t chunkmin, size_t chunkmax, char chunkdir);

#endif /* ITADS_PROJ1_RANDOM_H */
