#include <stdio.h>
#include <stdlib.h>

#include "bitpacking.h"



int testshortpack() {
    int bit;
    size_t i;
    uint32_t length;
    srand(0);
    printf("testshortpack\n");
    printf("bit = ");
    for (bit = 0; bit <= 32; ++bit) {
        printf(" %d ",bit);
        fflush(stdout);
        for(int trial = 0; trial < 100; ++trial) {
        const size_t N = 512;
        uint32_t * data = malloc(N * sizeof(uint32_t)+ 64 * sizeof(uint32_t));
        uint32_t * backdata = malloc(N * sizeof(uint32_t) + 64 * sizeof(uint32_t) );
        uint8_t * buffer = malloc((2 * N + 1024) * sizeof(uint32_t) + 32);

        for (i = 0; i < N; ++i) {
            data[i] = rand() & (uint32_t)((UINT64_C(1) << bit) - 1);
        }
        for (length = 0; length <= N; ++length) {
            for (i = 0; i < N; ++i) {
                backdata[i] = 0;
            }
            pack32(data, length, bit,buffer);
            unpack32(buffer, length, bit, backdata);
            for (i = 0; i < length; ++i) {
                if (data[i] != backdata[i]) {
                    printf("bug\n");
                    for (uint32_t j = 0; j < length; ++j) {
                        if (data[j] != backdata[j]) {
                            printf("data[%d]=%d v.s. backdata[%d]=%d\n",j,data[j],j,backdata[j]);
                        } else {
                            printf("data[%d]=%d\n",j,data[j]);
                        }
                    }
                    return -1;
                }
            }
        }
        free(data);
        free(backdata);
        free(buffer);
        }
    }
    printf("\n");
    return 0;
}

int main() {
    int r;
    r =  testshortpack();
    if (r) {
        printf("test failure 1\n");
        return r;
    }

    printf("All tests OK!\n");


    return 0;
}
