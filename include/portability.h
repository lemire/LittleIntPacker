#ifndef PORTABILITY_H
#define PORTABILITY_H

#include <iso646.h> /* mostly for Microsoft compilers */
#include <string.h>

#if defined(_MSC_VER) && _MSC_VER < 1600
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;
#else
#include <stdint.h> /* part of Visual Studio 2010 and better, others likely anyway */
#endif

#include <stdbool.h>

#endif // PORTABILITY_H
