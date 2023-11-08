#include <stdint.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"
#include "greatest.h"
#include "debug.h"

#define WINDOW_BITS 12
#define LOOKAHEAD_BITS 6
#define BUFFER_SIZE 2048

int main()
{
    double input_data[] = {0.9779411554336548, 0.9264705777168274, 0.6813725233078003, 0.0, 0.0, 0.0, 0.0, 0.0};

    size_t input_data_size = sizeof(input_data) - 1; // Subtract 1 to exclude the null terminator
    debug(input_data_size);

    // Allocate a heatshrink_encoder
    heatshrink_encoder *hse = heatshrink_encoder_alloc(WINDOW_BITS, LOOKAHEAD_BITS);

    if (hse == NULL)
    {
        fprintf(stderr, "Failed to allocate the encoder\n");
        return 1;
    }

    // An array to hold the compressed data
    double compressed_data[BUFFER_SIZE];

    // The offset in the input data where we are currently reading from
    size_t input_offset = 0;

    // The offset in the output data where we are currently writing to
    size_t output_offset = 0;

    /*
     * Repeat steps 2 and 3 to stream data through the state machine.
     * Since it's doing data compression, the input and output sizes can vary significantly.
     * Looping will be necessary to buffer the input and output as the data is processed.
     */
    while (input_offset < input_data_size)
    {
        size_t input_bytes_remaining = input_data_size - input_offset;
        size_t output_bytes_free = BUFFER_SIZE - output_offset;

        /**
         * Determine the size of the input to be processed based on the amount of input bytes remaining and the amount of output bytes free.
         * If there are fewer input bytes remaining than output bytes free, the input size is set to the remaining input bytes.
         * Otherwise, the input size is set to the amount of output bytes free.
         *
         * @param input_bytes_remaining The number of input bytes remaining to be processed.
         * @param output_bytes_free The number of output bytes free in the output buffer.
         * @return The size of the input to be processed.
         */
        size_t input_size = (input_bytes_remaining < output_bytes_free) ? input_bytes_remaining : output_bytes_free;

        size_t output_size = 0;
        HSE_sink_res res = heatshrink_encoder_sink(hse, input_data + input_offset, input_size, &output_size);

        if (res < 0)
        {
            fprintf(stderr, "Failed to sink data into encoder, the buffer is full\n");
            return 1;
        }

        /**
         * Increase the input offset by the input size.
         */
        input_offset += input_size;

        size_t poll_size = 0;

        /*
         * HSE_poll_res heatshrink_encoder_poll(heatshrink_encoder *hse, uint8_t *out_buf, size_t out_buf_size, size_t *output_size)
         * Poll for output from the encoder, copying at most OUT_BUF_SIZE bytes into
         * OUT_BUF (setting *OUTPUT_SIZE to the actual amount copied).
         */
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
        printf("%.16f ", compressed_data[i]);
    }
    printf("\n");

    // Cleanup the encoder
    heatshrink_encoder_free(hse);

    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Decoding
    // ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Sample compressed data only for testing
    // uint8_t compressed_data[] = {0xAA, 0x5A, 0x2D, 0x37, 0x39, 0x00, 0x00, 0x82, 0xB0, 0xC8, 0x2E, 0x76, 0x1B, 0x6D, 0xC2, 0xD9, 0x65, 0x90, 0x5A, 0x6D, 0xD7, 0x0B, 0xAD, 0xD2, 0x41, 0x64, 0xB0, 0xDD, 0x2C, 0x32, 0x0B, 0x35, 0xBE, 0xE5, 0x20, 0xB1, 0xDB, 0xED, 0xB7, 0x0B, 0x95, 0x96, 0xE7, 0x73, 0xB4, 0xDB, 0xED, 0xD2, 0xE0};
    debug(output_offset);

    double compressed_data_new[output_offset];

    for (size_t i = 0; i < output_offset; i++)
    {
        compressed_data_new[i] = compressed_data[i];
    }

    size_t compressed_data_size = sizeof(compressed_data_new);

    heatshrink_decoder *hsd = heatshrink_decoder_alloc(BUFFER_SIZE, WINDOW_BITS, LOOKAHEAD_BITS);

    if (hsd == NULL)
    {
        fprintf(stderr, "Failed to allocate the decoder\n");
        return 1;
    }

    double output_data[BUFFER_SIZE];
    size_t input_offset_decompressed = 0;
    size_t output_offset_decompressed = 0;

    while (input_offset_decompressed < compressed_data_size)
    {
        size_t input_bytes_remaining = compressed_data_size - input_offset_decompressed;
        size_t output_bytes_free = BUFFER_SIZE - output_offset_decompressed;

        size_t input_size = (input_bytes_remaining < output_bytes_free) ? input_bytes_remaining : output_bytes_free;
        size_t output_size = 0;

        HSD_sink_res res = heatshrink_decoder_sink(hsd, compressed_data + input_offset_decompressed, input_size, &input_size);

        if (res != HSDR_SINK_OK) // (enum <unnamed>)HSDR_SINK_OK = 0
        {
            fprintf(stderr, "Failed to sink data into decoder\n");
            return 1;
        }

        input_offset_decompressed += input_size;

        HSD_poll_res poll_res = heatshrink_decoder_poll(hsd, output_data + output_offset_decompressed, output_bytes_free, &output_size);

        if (poll_res != HSDR_POLL_MORE) // (enum <unnamed>)HSDR_POLL_MORE = 1, more data remaining, call again w/ fresh output buffer
        {
            // Output is ready; you can process it
            output_offset_decompressed += output_size;
        }
    }

    // Finish decoding
    HSD_finish_res finish_res_decompressed = heatshrink_decoder_finish(hsd);
    debug(finish_res_decompressed);

    // if (finish_res_decompressed != HSDR_FINISH_DONE)
    // {
    //     fprintf(stderr, "Failed to finish decoding\n");
    //     return 1;
    // }

    if (finish_res_decompressed > 0)
    {
        size_t output_bytes_free = BUFFER_SIZE - output_offset_decompressed; // Define output_bytes_free here
        // More output data to collect
        HSD_poll_res poll_res = heatshrink_decoder_poll(hsd, output_data + output_offset_decompressed, output_bytes_free, &output_size);
        if (poll_res < 0)
        {
            fprintf(stderr, "Failed to poll data from encoder\n");
            return 1;
        }
        output_offset_decompressed += output_size;
    }

    // Output the decoded data
    printf("Decoded Data (%zu bytes):\n", output_offset_decompressed);
    for (size_t i = 0; i < output_offset_decompressed; i++)
    {
        printf("%f,", output_data[i]);
    }
    printf("\n");

    // Cleanup the decoder
    heatshrink_decoder_free(hsd);

    return 0;
}
