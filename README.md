# LittleIntPacker
C library to pack and unpack short arrays of integers as fast as possible

## Introduction

This is a bit packing library. Bit packing is the process by which you
take arrays of (32-bit) integers that fit in [0,2^L) and you write them
out using as close to L bits per integer as possible. 



## Motivation

For long blocks of integers (e.g., 128 integers or more), SIMD bit packing
is ideal. See for example https://github.com/lemire/simdcomp where blocks
of 128 integers are packed and unpacked very fast.

However, what happens if you have small blocks having variable lengths,
and lengths that are typically much smaller than 128 integers?

The work is motivated by the  engineering underlying TurboPFor
https://github.com/powturbo/TurboPFor
That is, we write and load compressed bytes in 64-bit words as opposed
to 32-bit words.

## Hardware requirements

This software makes little sense if you do not have a 64-bit processor.

## Usage

```bash
make
./unit 
```

## Code usage

```C
//#include "bitpacking.h

// number of bytes required to compress l 32-bit integers using b bits each
uint32_t c = byte_count(l, b);

// packing an array of 32-bit unsigned ints from data to buffer
pack32(data, l, b,buffer);
// recovering data
unpack32(buffer, l, b,backdata);
```


## Current status

Tested.

## References

* Daniel Lemire, Leonid Boytsov, Nathan Kurz, SIMD Compression and the Intersection of Sorted Integers, Software Practice & Experience (to appear) http://arxiv.org/abs/1401.6399
* Daniel Lemire and Leonid Boytsov, Decoding billions of integers per second through vectorization, Software Practice & Experience 45 (1), 2015.  http://arxiv.org/abs/1209.2137 http://onlinelibrary.wiley.com/doi/10.1002/spe.2203/abstract
* Jeff Plaisance, Nathan Kurz, Daniel Lemire, Vectorized VByte Decoding, International Symposium on Web Algorithms 2015, 2015. http://arxiv.org/abs/1503.07387
* Wayne Xin Zhao, Xudong Zhang, Daniel Lemire, Dongdong Shan, Jian-Yun Nie, Hongfei Yan, Ji-Rong Wen, A General SIMD-based Approach to Accelerating Compression Algorithms, ACM Transactions on Information Systems 33 (3), 2015. http://arxiv.org/abs/1502.01916
