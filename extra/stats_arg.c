// stats_arg.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <int1> <int2> ... <intN>\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    int value;
    int min, max;
    long long sum = 0;  // safer than int for larger sums

    // Example required conversion style:
    // int a = atoi("12");

    for (int i = 1; i < argc; i++) {
        value = atoi(argv[i]);

        if (i == 1) {
            min = max = value;
        }

        sum += value;

        if (value < min) min = value;
        if (value > max) max = value;
    }

    printf("Count: %d\n", count);
    printf("Sum: %lld\n", sum);
    printf("Min: %d\n", min);
    printf("Max: %d\n", max);

    return 0;
}