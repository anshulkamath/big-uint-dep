#include "sha256.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define COUNT 1000000

int main(void) {
    clock_t start = clock();
    uint8_t res[32] = {0};
    for (size_t i = 0; i < 10000000; i++) {
        if (i != 0 && i % COUNT == 0) {
            clock_t end = clock();
            double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("%f kH\n", COUNT / cpu_time_used / 1000);
            start = end;
        }
        sha256(res, (char *) res, 32);
    }
}
