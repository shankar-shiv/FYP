#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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
    // Create a module structure for CS1010
    struct module cs1010;

    // Call the update_mc function to update module credits
    long hours_spent = 10; // Replace with the actual hours spent per week
    update_mc(&cs1010, hours_spent);

    // Print the updated module credits
    printf("CS1010 Module Credits: %.2f\n", cs1010.mc);

    // Declare a variable of type traffic_light_states_t
    traffic_light_states_t current_state;

    // Assign one of the enum values to the variable
    current_state = CAUTION;

    // You can now use the variable to represent the traffic light state
    if (current_state == STOP)
    {
        printf("Traffic light is in STOP state.\n");
    }
    else if (current_state == CAUTION)
    {
        printf("Traffic light is in CAUTION state.\n");
    }
    else if (current_state == GO)
    {
        printf("Traffic light is in GO state.\n");
    }

    // Demonstration of memeset()

    // char str[50] = "GeeksForGeeks is for programming geeks.";
    // printf("\nBefore memset(): %s\n", str);
    // // Fill 8 characters starting from str[13] with '.'
    // memset(str + 13, '.', 8 * sizeof(char));
    // printf("After memset():  %s \n", str);

    uint16_t output[1024];
    memset(output, 10, 1024);
    printArray(output, 1024);

    return 0;
}
