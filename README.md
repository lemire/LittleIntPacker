# LittleIntPacker
C library to pack and unpack short arrays of integers as fast as possible

## Introduction

This is a bit packing library. Bit packing is the process by which you
take arrays of (32-bit) integers that fit in [0,2^L) and you write them
out using as close to L bits per integer as possible. By extension,
we can apply the same idea to array of integers with the difference between
successive integers fits in [0,2^L).


## Motivation

For long blocks of integers (e.g., 128 integers or more), SIMD bit packing
is ideal. See for example https://github.com/lemire/simdcomp where blocks
of 128 integers are packed and unpacked very fast.

However, what happens if you have small blocks having variable lengths,
and lengths that are typically much smaller than 128 integers?

The goal of this library is to explore this project in some depth.

The work is motivated by the excellent engineering underlying TurboPFor
https://github.com/powturbo/TurboPFor

## Hardware requirements

At least initially, this project will assume recent Intel processors (Haswell or better).


## Current status

Purely experimental.

## References

* Daniel Lemire, Leonid Boytsov, Nathan Kurz, SIMD Compression and the Intersection of Sorted Integers, Software Practice & Experience (to appear) http://arxiv.org/abs/1401.6399
* Daniel Lemire and Leonid Boytsov, Decoding billions of integers per second through vectorization, Software Practice & Experience 45 (1), 2015.  http://arxiv.org/abs/1209.2137 http://onlinelibrary.wiley.com/doi/10.1002/spe.2203/abstract
* Jeff Plaisance, Nathan Kurz, Daniel Lemire, Vectorized VByte Decoding, International Symposium on Web Algorithms 2015, 2015. http://arxiv.org/abs/1503.07387
* Wayne Xin Zhao, Xudong Zhang, Daniel Lemire, Dongdong Shan, Jian-Yun Nie, Hongfei Yan, Ji-Rong Wen, A General SIMD-based Approach to Accelerating Compression Algorithms, ACM Transactions on Information Systems 33 (3), 2015. http://arxiv.org/abs/1502.01916
