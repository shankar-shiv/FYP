#include "int_array_compression.h"
#include <stdio.h>

#define INPUT_SIZE 111
#define OUTPUT_SIZE 1024

int main()
{
    // Original readings
    int8_t readings[] = {
        5,
        6,
        6,
        6,
        10,
        12,
        12,
        10,
        10,
        10,
        -36,
        5,
        6,
        6,
        6,
        10,
        12,
        12,
        10,
        10,
        10,
        -36,
        5,
        6,
        6,
        6,
        10,
        12,
        12,
        10,
        10,
        10,
        -36,
    };
    uint8_t readings_nBytes = sizeof(readings);

    // Decoded readings
    int8_t readings_decoded[readings_nBytes];
    uint8_t readings_decoded_nBytes = 0;

    // Bit buffer, where the compressed encodings are stored.
    // In our case it's an Iridium packet comprised of 59 bytes.
    uint8_t bitBuffer[OUTPUT_SIZE];
    uint8_t bitBuffer_nBytes = OUTPUT_SIZE;
    uint32_t bitBuffer_nBits = 0;

    // Take the data from the readings and encode it into the bit buffer
    bitBuffer_reset(bitBuffer, bitBuffer_nBytes); // Reset now, enjoy later
    encodeReadings(readings, readings_nBytes, bitBuffer, &bitBuffer_nBits);

    printf("bitBuffer_nBits: %d\n", bitBuffer_nBits);

    // Take the bits from the bit buffer and decode the original readings
    decodeReadings(readings_decoded, &readings_decoded_nBytes, bitBuffer, bitBuffer_nBits);

    // Print the decoded readings
    for (int i = 0; i < readings_decoded_nBytes; i++)
        printf("%d ", readings_decoded[i]);
    printf("\n");

    // print size before compression
    printf("before compression size is %ld bytes \n", sizeof(readings));

    // print size after compression
    printf("after compression size is %ld bytes \n", bitBuffer_nBits);

    printf("compression ratio is %f \n", (float)sizeof(readings) / bitBuffer_nBits);

    return 0;
}
