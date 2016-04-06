#ifndef BITPACKING_H
#define BITPACKING_H

/**
* This is conventional bit packing using portable C
*/

#include "portability.h"

/**
* how many 64-bit words does it take to pack number integers that use bit bits each?
* (function should have ~5 cycles latency or so)
*/
static inline uint32_t word_count(uint32_t number, uint32_t bit) {
  return (number * bit + 63) >> 6; /* >>6 is division by 64 */
}


/* write number 32-bit values from in bit bits per value to out.
 * For safety, pad in with 64 extra integers, and pad out with an extra 32 bytes. */
void pack32(const uint32_t *  in, uint32_t number, const uint32_t bit, uint8_t *  out);

/* reads  number 32-bit values from "in" as packed bit bits values, and write to "out"
 * For safety, pad in with 32 extra bytes, and pad out with an extra 64 integers.*/
void unpack32(const uint8_t *  in, uint32_t number, const uint32_t bit, uint32_t *  out);


#endif //BITPACKING_H
