#include <stdio.h>
#include <string.h>
#include "lzf.h" // Include the correct header file for lzf functions
#include <ctype.h>
#include <stdint.h>

// Maximum size for each line
#define MAX_LINE_SIZE 256

int main()
{
    // Open the file for reading
    FILE *file = fopen("/home/shankar/CAPSTONE/Capstone/.datasets/mitbih_test.csv", "r");

    if (!file)
    {
        printf("Failed to open the file.\n");
        return 1;
    }

    float average_compression_ratio = 0;
    uint32_t total_lines = 0;

    char input_data[MAX_LINE_SIZE];
    uint32_t input_data_size = 0; // Total input data size in bytes

    // Read data from the file line by line
    while (fgets(input_data, MAX_LINE_SIZE, file) != NULL)
    {
        input_data_size = strlen(input_data); // Get the size of the input data

        // Process the input_data (e.g., apply compression/decompression)
        // Compressed data buffer
        char compressed_data[input_data_size * 2]; // We assume maximum expansion is 100%
        uint32_t compressed_data_size = sizeof(compressed_data);

        // Decompressed data buffer
        char decompressed_data[input_data_size];
        uint32_t decompressed_data_size = sizeof(decompressed_data);

        // Compress the data
        uint32_t compressed_size = lzf_compress(input_data, input_data_size, compressed_data, compressed_data_size);

        if (compressed_size == 0)
        {
            printf("Compression failed or buffer is too small.\n");
            return 1;
        }

        // Decompress the data
        uint32_t decompressed_size = lzf_decompress(compressed_data, compressed_size, decompressed_data, decompressed_data_size);

        if (decompressed_size == 0)
        {
            printf("Decompression failed or buffer is too small.\n");
            return 1;
        }

        // First layer of check: Compare the original data with the decompressed data
        if (decompressed_size != input_data_size || memcmp(input_data, decompressed_data, input_data_size) != 0)
        {
            printf("Decompressed data does not match the original data.\n");
            return 1;
        }

        // Second layer of check: check each value in the decompressed data with the input data
        for (int i = 0; i < input_data_size; i++)
        {
            if (decompressed_data[i] != input_data[i])
            {
                printf("Decompressed data does not match the original data.\n");
                return 1;
            }
        }

        // Print the decompressed data
        // for (int i = 0; i < input_data_size; i++)
        // {
        //     printf("%c", decompressed_data[i]);
        // }

        // Print number of input data bytes
        // printf("\n\nNumber of input data bytes: %d\n", input_data_size);
        // Print number of bytes compressed
        // printf("Number of bytes compressed: %d\n", compressed_size);
        // Print number of bytes decompressed
        // printf("Number of bytes decompressed: %d\n", decompressed_size);
        // Print compression ratio
        // printf("Compression ratio: %f\n", (float)input_data_size / (float)compressed_size);

        total_lines += 1;
        average_compression_ratio += (float)compressed_size / (float)input_data_size;
    }

    fclose(file); // Close the file

    printf("Compression and decompression successful.\n");
    // print average compression ratio
    printf("Average compression ratio: %f\n", average_compression_ratio / total_lines);

    return 0;
}
