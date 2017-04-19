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
turbopack32(data, l, b,buffer);
// recovering data
turbounpack32(buffer, l, b,backdata);
```


## Current status

Tested.

## References


* Jianguo Wang, Chunbin Lin, Yannis Papakonstantinou, Steven Swanson, An Experimental Study of Bitmap Compression vs. Inverted List Compression, SIGMOD 2017 http://db.ucsd.edu/wp-content/uploads/2017/03/sidm338-wangA.pdf
* P. Damme, D. Habich, J. Hildebrandt, W. Lehner, Lightweight Data Compression Algorithms: An Experimental Survey (Experiments and Analyses), EDBT 2017 http://openproceedings.org/2017/conf/edbt/paper-146.pdf
* P. Damme, D. Habich, J. Hildebrandt, W. Lehner, Insights into the Comparative Evaluation of Lightweight Data Compression Algorithms, EDBT 2017 http://openproceedings.org/2017/conf/edbt/paper-414.pdf
* Daniel Lemire, Leonid Boytsov, Nathan Kurz, SIMD Compression and the Intersection of Sorted Integers, Software Practice & Experience 46 (6) 2016. http://arxiv.org/abs/1401.6399
* Daniel Lemire and Leonid Boytsov, Decoding billions of integers per second through vectorization, Software Practice & Experience 45 (1), 2015.  http://arxiv.org/abs/1209.2137 http://onlinelibrary.wiley.com/doi/10.1002/spe.2203/abstract
* Jeff Plaisance, Nathan Kurz, Daniel Lemire, Vectorized VByte Decoding, International Symposium on Web Algorithms 2015, 2015. http://arxiv.org/abs/1503.07387
* Wayne Xin Zhao, Xudong Zhang, Daniel Lemire, Dongdong Shan, Jian-Yun Nie, Hongfei Yan, Ji-Rong Wen, A General SIMD-based Approach to Accelerating Compression Algorithms, ACM Transactions on Information Systems 33 (3), 2015. http://arxiv.org/abs/1502.01916

## Other relevant libraries

* SIMDCompressionAndIntersection: A C++ library to compress and intersect sorted lists of integers using SIMD instructions https://github.com/lemire/SIMDCompressionAndIntersect
* The FastPFOR C++ library : Fast integer compression https://github.com/lemire/FastPFor
* High-performance dictionary coding https://github.com/lemire/dictionary
* The SIMDComp library: A simple C library for compressing lists of integers using binary packing https://github.com/lemire/simdcomp
* StreamVByte: Fast integer compression in C using the StreamVByte codec https://github.com/lemire/streamvbyte
* MaskedVByte: Fast decoder for VByte-compressed integers https://github.com/lemire/MaskedVByte
* CSharpFastPFOR: A C#  integer compression library  https://github.com/Genbox/CSharpFastPFOR
* JavaFastPFOR: A java integer compression library https://github.com/lemire/JavaFastPFOR
* Encoding: Integer Compression Libraries for Go https://github.com/zhenjl/encoding
* FrameOfReference is a C++ library dedicated to frame-of-reference (FOR) compression: https://github.com/lemire/FrameOfReference
* libvbyte: A fast implementation for varbyte 32bit/64bit integer compression https://github.com/cruppstahl/libvbyte
* TurboPFor is a C library that offers lots of interesting optimizations. Well worth checking! (GPL license) https://github.com/powturbo/TurboPFor
* Oroch is a C++ library that offers a usable API (MIT license) https://github.com/ademakov/Oroch


