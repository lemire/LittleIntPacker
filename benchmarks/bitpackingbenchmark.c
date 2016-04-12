#include <stdio.h>

#include "bitpacking.h"

#define COMPILER_NOINLINE __attribute__ ((noinline))

#define RDTSC_START(timestamp_ptr)                                      \
    __asm volatile("cpuid\n"                                            \
                   "rdtscp\n"                                           \
                   "shl $32, %%rdx\n"                                   \
                   "or %%rax, %%rdx\n"                                  \
                   "mov %%rdx, (%0)" :                                  \
                   /* no register writes */ :                           \
                   /* writes memory*/ "r" (timestamp_ptr) :             \
                   /* clobbers */ "memory", "%rax", "%rbx", "%rcx", "%rdx")


#define RDTSC_STOP(timestamp_ptr)                                       \
    __asm volatile("rdtscp\n"                                           \
                   "shl $32, %%rdx\n"                                   \
                   "or %%rax, %%rdx\n"                                  \
                   "mov %%rdx, (%0)\n"                                  \
                   "cpuid" :                                            \
                   /* no register writes */ :                           \
                   /* writes memory */ "r" (timestamp_ptr) :            \
                   /* clobbers */ "memory", "%rax", "%rbx", "%rcx", "%rdx")


COMPILER_NOINLINE uint64_t rdtsc_overhead_func(uint64_t dummy) {
    __asm volatile("" : : : /* pretend to clobber */ "memory");
    return dummy;
}

uint64_t global_rdtsc_overhead = (uint64_t) UINT64_MAX;

#define RDTSC_SET_OVERHEAD(test)                                        \
    do {                                                                \
        uint64_t cycles_start, cycles_stop, cycles_diff;                \
        uint64_t _min_diff = UINT64_MAX;                                 \
        for (size_t _i = 0; _i < 1000; _i++) {                             \
            RDTSC_START(&cycles_start);                                 \
            test;                                                       \
            RDTSC_STOP(&cycles_stop);                                   \
            cycles_diff = (cycles_stop - cycles_start);                 \
            if (cycles_diff < _min_diff) _min_diff = cycles_diff;         \
        }                                                               \
        global_rdtsc_overhead = _min_diff;                               \
        printf("rdtsc_overhead set to %ld\n", (long int) global_rdtsc_overhead);   \
    } while (0)


#define RDTSC_TIME(test, cycles)                                \
    do {                                                        \
        if (global_rdtsc_overhead == UINT64_MAX) {              \
            RDTSC_SET_OVERHEAD(rdtsc_overhead_func(1));         \
        }                                                       \
        uint64_t cycles_start, cycles_stop;                     \
        RDTSC_START(&cycles_start);                             \
        { test; }                                               \
        RDTSC_STOP(&cycles_stop);                               \
        cycles = (cycles_stop - cycles_start);                  \
        if (cycles <= global_rdtsc_overhead) cycles = 0;        \
        else cycles = cycles - global_rdtsc_overhead;           \
    } while (0)

#define RDTSC_BEST(test, repeat, best)                          \
    do {                                                        \
        best = UINT64_MAX;                                      \
        for (uint64_t i = 0; i < repeat; i++) {                 \
            uint64_t cycles;                                    \
            RDTSC_TIME(test, cycles);                           \
            if (cycles < best) best = cycles;                   \
        }                                                       \
    } while (0)

uint32_t * get_random_array_from_bit_width(uint32_t length, uint32_t bit) {
    uint32_t * answer = malloc(sizeof(uint32_t) * length);
    uint32_t mask = (uint32_t) ((UINT64_C(1) << bit) - 1);
    uint32_t i;
    for(i = 0; i < length; ++i) {
        answer[i] = rand() & mask;
    }
    return answer;
}

uint32_t * get_random_array_from_bit_width_d1(uint32_t length, uint32_t bit) {
    uint32_t * answer = malloc(sizeof(uint32_t) * length);
    uint32_t mask = (uint32_t) ((UINT64_C(1) << bit) - 1);
    uint32_t i;
    answer[0] = rand() & mask;
    for(i = 1; i < length; ++i) {
        answer[i] = answer[i-1] + (rand() & mask);
    }
    return answer;
}

void demo128() {
    const uint32_t length = 128;
    uint32_t bit;
    printf("# --- %s\n", __func__);
    printf("# compressing %d integers\n",length);
    printf("# format: bit width, pack in cycles per int, unpack in cycles per int\n");
    for(bit = 1; bit <= 32; ++bit) {
        uint32_t * data = get_random_array_from_bit_width(length, bit);
        uint8_t * buffer = malloc(length * sizeof(uint32_t));
        uint32_t * backdata = malloc(length * sizeof(uint32_t));
        uint32_t repeat = 50000;
        uint64_t min_diff;
        printf("%d\t",bit);
        RDTSC_BEST(pack32(data, length, bit, buffer), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);
        RDTSC_BEST(unpack32(buffer, length, bit, backdata), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);

        free(data);
        free(buffer);
        free(backdata);
        printf("\n");
    }
    printf("\n\n"); /* two blank lines are required by gnuplot */
}

void turbodemo128() {
    const uint32_t length = 128;
    uint32_t bit;
    printf("# --- %s\n", __func__);
    printf("# compressing %d integers\n",length);
    printf("# format: bit width, pack in cycles per int, unpack in cycles per int\n");
    for(bit = 1; bit <= 32; ++bit) {
        uint32_t * data = get_random_array_from_bit_width(length, bit);
        uint8_t * buffer = malloc(length * sizeof(uint32_t));
        uint32_t * backdata = malloc(length * sizeof(uint32_t));
        uint32_t repeat = 50000;
        uint64_t min_diff;
        printf("%d\t",bit);
        RDTSC_BEST(turbopack32(data, length, bit, buffer), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);
        RDTSC_BEST(turbounpack32(buffer, length, bit, backdata), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);

        free(data);
        free(buffer);
        free(backdata);
        printf("\n");
    }
    printf("\n\n"); /* two blank lines are required by gnuplot */
}

void bmidemo128() {
    const uint32_t length = 128;
    uint32_t bit;
    printf("# --- %s\n", __func__);
    printf("# compressing %d integers\n",length);
    printf("# format: bit width, pack in cycles per int, unpack in cycles per int\n");
    for(bit = 1; bit <= 32; ++bit) {
        uint32_t * data = get_random_array_from_bit_width(length, bit);
        uint8_t * buffer = malloc(length * sizeof(uint32_t));
        uint32_t * backdata = malloc(length * sizeof(uint32_t));
        uint32_t repeat = 50000;
        uint64_t min_diff;
        printf("%d\t",bit);
        RDTSC_BEST(bmipack32(data, length, bit, buffer), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);
        RDTSC_BEST(bmiunpack32(buffer, length, bit, backdata), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);

        free(data);
        free(buffer);
        free(backdata);
        printf("\n");
    }
    printf("\n\n"); /* two blank lines are required by gnuplot */
}

void scdemo128() {
    const uint32_t length = 128;
    uint32_t bit;
    printf("# --- %s\n", __func__);
    printf("# compressing %d integers\n",length);
    printf("# format: bit width, pack in cycles per int, unpack in cycles per int\n");
    for(bit = 1; bit <= 32; ++bit) {
        uint32_t * data = get_random_array_from_bit_width(length, bit);
        uint8_t * buffer = malloc(length * sizeof(uint32_t));
        uint32_t * backdata = malloc(length * sizeof(uint32_t));
        uint32_t repeat = 50000;
        uint64_t min_diff;
        printf("%d\t",bit);
        RDTSC_BEST(scpack32(data, length, bit, buffer), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);
        RDTSC_BEST(scunpack32(buffer, length, bit, backdata), repeat, min_diff);
        printf("%.2f\t",min_diff*1.0/length);

        free(data);
        free(buffer);
        free(backdata);
        printf("\n");
    }
    printf("\n\n"); /* two blank lines are required by gnuplot */
}




int main() {
    demo128();
    turbodemo128();
    bmidemo128();
    scdemo128();

    return 0;
}
