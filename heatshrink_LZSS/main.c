#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"
#include "greatest.h"

static void dump_buf(char *name, uint8_t *buf, uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        uint8_t c = (uint8_t)buf[i];
        printf("%s %d: 0x%02x ('%c')\n", name, i, c, isprint(c) ? c : '.');
    }
}

#define WINDOW_BITS 12
#define LOOKAHEAD_BITS 4
#define BUFFER_SIZE 1024

int main()
{
    // Sample input data
    uint8_t input_data[] = "This is a sample input data for compression.";
    size_t input_data_size = sizeof(input_data) - 1; // Subtract 1 to exclude the null terminator

    // Compression
    heatshrink_encoder *hse = heatshrink_encoder_alloc(WINDOW_BITS, LOOKAHEAD_BITS);

    if (hse == NULL)
    {
        fprintf(stderr, "Failed to allocate the encoder\n");
        return 1;
    }

    uint8_t compressed_data[BUFFER_SIZE];
    size_t input_offset = 0;
    size_t output_offset = 0;

    while (input_offset < input_data_size)
    {
        size_t input_bytes_remaining = input_data_size - input_offset;
        size_t output_bytes_free = BUFFER_SIZE - output_offset;

        size_t input_size = input_bytes_remaining < output_bytes_free ? input_bytes_remaining : output_bytes_free;

        size_t output_size = 0;
        HSE_sink_res res = heatshrink_encoder_sink(hse, input_data + input_offset, input_size, &output_size);

        if (res < 0)
        {
            fprintf(stderr, "Failed to sink data into encoder\n");
            return 1;
        }
        input_offset += input_size;

        size_t poll_size = 0;
        HSE_poll_res poll_res = heatshrink_encoder_poll(hse, compressed_data + output_offset, output_bytes_free, &poll_size);

        if (poll_res < 0)
        {
            fprintf(stderr, "Failed to poll data from encoder\n");
            return 1;
        }

        output_offset += poll_size;
    }

    // Compression finished; call finish to generate any remaining output
    size_t output_size = 0;
    HSE_finish_res finish_res = heatshrink_encoder_finish(hse);

    if (finish_res < 0)
    {
        fprintf(stderr, "Failed to finish encoding\n");
        return 1;
    }

    if (finish_res > 0)
    {
        size_t output_bytes_free = BUFFER_SIZE - output_offset; // Define output_bytes_free here
        // More output data to collect
        HSE_poll_res poll_res = heatshrink_encoder_poll(hse, compressed_data + output_offset, output_bytes_free, &output_size);
        if (poll_res < 0)
        {
            fprintf(stderr, "Failed to poll data from encoder\n");
            return 1;
        }
        output_offset += output_size;
    }

    // Output the compressed data
    printf("Compressed Data (%zu bytes):\n", output_offset);
    for (size_t i = 0; i < output_offset; i++)
    {
        printf("%02X ", compressed_data[i]);
    }
    printf("\n");

    // Cleanup the encoder
    heatshrink_encoder_free(hse);
    return 0;
}