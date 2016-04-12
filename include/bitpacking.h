#ifndef BITPACKING_H
#define BITPACKING_H

/**
* This is conventional bit packing using portable C
*/

#include "portability.h"

/**
* how many bytes does it take to pack "number" integers that use "bit" bits each?
* (function should have ~5 cycles latency or so)
*/
static inline uint32_t byte_count(uint32_t number, uint32_t bit) {
  return (number * bit + 7) >> 3;
}


/* write number 32-bit values from in bit bits per value to out.
 * Internally, it reads blocks of 32 integers. The integers should
 * be in [0,2^bit).
 * For safety, pad in with 32 extra integers, and pad out with an extra 32 bytes.
 *
 * turbopack32 and pack32 have identical results except that they use
 * a different implementation. turbopack32 uses an approach based on 64-bit words.
 *
 *  */
void turbopack32(const uint32_t *  in, uint32_t number, const uint32_t bit, uint8_t *  out);

/* reads  number 32-bit values from "in" as packed bit bits values, and write to "out"
 * Internally, it writes blocks of 32 integers.
 * For safety, pad in with 32 extra bytes, and pad out with an extra 32 integers.
 *
 * turbounpack32 and unpack32 have identical results except that they use
 * a different implementation. turbounpack32 uses an approach based on 64-bit words.
 * */
void turbounpack32(const uint8_t *  in, uint32_t number, const uint32_t bit, uint32_t *  out);



/* write number 32-bit values from in bit bits per value to out.
 * Internally, it reads blocks of 32 integers. The integers should
 * be in [0,2^bit).
 * For safety, pad in with 32 extra integers, and pad out with an extra 32 bytes.
 * This is implemented using conventional bit packing from 32-bit words to 32-bit words.
 * */
void pack32(const uint32_t *  in, uint32_t number, const uint32_t bit, uint8_t *  out);

/* reads  number 32-bit values from "in" as packed bit bits values, and write to "out"
 * Internally, it writes blocks of 32 integers.
 * For safety, pad in with 32 extra bytes, and pad out with an extra 32 integers.
 * This is implemented using conventional bit unpacking from 32-bit words to 32-bit words.
 * */
void unpack32(const uint8_t *  in, uint32_t number, const uint32_t bit, uint32_t *  out);


/* write number 32-bit values from in bit bits per value to out.
 * Internally, it might use BMI instructions. The integers should
 * be in [0,2^bit).
 * */
void bmipack32(const uint32_t *  in, uint32_t number, const uint32_t bit, uint8_t *  out);

/* reads  number 32-bit values from "in" as packed bit bits values, and write to "out"
 * Internally, it might use BMI instructions.
 * */
void bmiunpack32(const uint8_t *  in, uint32_t number, const uint32_t bit, uint32_t *  out);




/* write number 32-bit values from in bit bits per value to out.
 * Uses experimental approach.*/
void scpack32(const uint32_t *  in,  uint32_t number, const uint32_t bit, uint8_t *  out);

/* reads  number 32-bit values from "in" as packed bit bits values, and write to "out"
 * Uses experimental approach.*/
void scunpack32(const uint8_t * in, uint32_t number, const uint32_t bit, uint32_t *  out);


#endif //BITPACKING_H
