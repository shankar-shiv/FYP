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

    double test[] = {9.739696383476257324e-01, 9.132320880889892578e-01, 8.655097484588623047e-01, 8.232104182243347168e-01, 7.462038993835449219e-01, 6.420824527740478516e-01, 5.477223396301269531e-01, 4.262472987174987793e-01, 3.253796100616455078e-01, 2.798264622688293457e-01, 2.288503199815750122e-01, 1.366594433784484863e-01, 4.772234335541725159e-02, 1.084598712623119354e-02, 1.008676812052726746e-01, 1.887201666831970215e-01, 2.277657240629196167e-01, 2.407809048891067505e-01, 2.570498883724212646e-01, 2.635574936866760254e-01, 2.939262390136718750e-01, 3.188720047473907471e-01, 3.492407798767089844e-01, 4.023861289024353027e-01, 4.392624795436859131e-01, 4.501084685325622559e-01, 4.620390534400939941e-01, 4.750542342662811279e-01, 4.891540110111236572e-01, 4.869848191738128662e-01, 5.075922012329101562e-01, 5.108459591865539551e-01, 5.303687453269958496e-01, 5.433839559555053711e-01, 5.694143176078796387e-01, 5.824295282363891602e-01};

    printf("Length of test: %ld\n", sizeof(test) / sizeof(test[0]));

    return 0;
}
