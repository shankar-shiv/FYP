#ifndef PAN_TOMPKINS
#define PAN_TOMPKINS
#include <stdbool.h>

typedef int dataType;
/*typedef enum {false, true} bool;*/
typedef enum { false_value = false, true_value = true } Boolean;

void panTompkins();
void init(char file_in[], char file_out[]);

#endif