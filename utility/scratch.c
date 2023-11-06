#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define DOUBLE_COUNT (1U << 12U)
#define OUTPUT_SIZE (((size_t)(((1U << 12U)) + 1) / 2) + ((size_t)((1U << 12U)) * 8))

typedef enum
{
    STOP,
    CAUTION,
    GO
} traffic_light_states_t;

// Define a structure for the module
struct module
{
    double mc; // Module Credits
};

// Function to update module credits based on hours spent per week
void update_mc(struct module *cs1010, long hours_spent_per_week)
{
    cs1010->mc = (double)hours_spent_per_week / 2.5;
}

void printArray(uint8_t arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

int main()
{
    printf("%ld \n", OUTPUT_SIZE);

    return 0;
}
