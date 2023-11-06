#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    uint16_t bitpattern[sizeof(float)];
    float f = 9.739696383476257324e-01;
    memcpy(bitpattern, &f, sizeof(float));

    for (int i = 0; i < sizeof(float); i++)
        printf("%d ", bitpattern[i]);

    printf("\n");

    // convert the bit pattern to an integer
    float destination = 0;
    memcpy(&destination, &bitpattern, sizeof(float));
    printf("%f \n", destination);

    return 0;
}