#ifndef UTIL_H
#define UTIL_H

#include "portability.h"

/* returns the integer logarithm of v (bit width) */
uint32_t bits(const uint32_t v);


/* max integer logarithm over a range of length integers */
uint32_t maxbits_length(const uint32_t * in,uint32_t length);


#endif // UTIL_H
