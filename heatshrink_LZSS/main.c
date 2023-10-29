#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"
#include "greatest.h"

// Change these according to your requirements
#define WINDOW_BITS 10
#define LOOKAHEAD_BITS 5

// Define the buffer size
#define BUFFER_SIZE 1024

static void dump_buf(char *name, uint8_t *buf, uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        uint8_t c = (uint8_t)buf[i];
        printf("%s %d: 0x%02x ('%c')\n", name, i, c, isprint(c) ? c : '.');
    }
}

int main()
{
    heatshrink_encoder *hse = heatshrink_encoder_alloc(8, 7);
    // ASSERT(hse);
    uint8_t input[512];
    size_t bytes_copied = 0;
    memset(input, '*', 512);
    // ASSERT_EQ(HSER_SINK_OK, heatshrink_encoder_sink(hse, input, 512, &bytes_copied));
    // ASSERT_EQ(256, bytes_copied);

    heatshrink_encoder_free(hse);

    return 0;
}
