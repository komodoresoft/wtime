#include <stdio.h>
#include <stdint.h>

volatile uint64_t sink = 0;

int main(void)
{
    uint64_t total = 0;
    for (uint64_t i = 0; i < 50ULL * 1000 * 1000 * 1000; ++i) {
        total += (i % 17) * (i % 23);
        if (i % 1000000000 == 0)
            printf(".");
    }
    printf("\ntotal = %llu\n", total);
    sink = total;
    return 0;
}
