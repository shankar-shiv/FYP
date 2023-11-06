#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    uint16_t bitpattern[sizeof(double)];
    double f = 9.673590660095214844e-01;
    memcpy(bitpattern, &f, sizeof(double));

    for (int i = 0; i < sizeof(double); i++)
        printf("%d \t", bitpattern[i]);

    double destination = 0;
    memcpy(&destination, bitpattern, sizeof(double));
    printf("\n%f\n", destination);

    return 0;
}