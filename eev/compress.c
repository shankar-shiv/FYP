/*
 * The proposed "look-back-36-bytes" compression works so well because the jumps are so rare.
 */
#include <stdio.h>

static char last[36];      // 36 bytes of look-back
static char emitting[8];   // 8 bytes of data to emit
static int emit_count = 0; //
static int emit_mask = 0;
static int emit_data_count = 0;

static void emit(char c)
{
    int i;
    if (c)
    {
        emit_mask |= 1 << emit_count;
        emitting[emit_data_count++] = c;
    }
    emit_count++;

    if (emit_count != 8)
        return;

    putchar(emit_mask);
    for (i = 0; i < emit_data_count; i++)
        putchar(emitting[i]);

    emit_data_count = 0;
    emit_count = 0;
    emit_mask = 0;
}

static void emit_flush(void)
{
    int i;
    // Zeros that are explicitly added at the
    // end of file, not by the "zero mask" are padding
    while (emit_count != 8)
    {
        emit_mask |= 1 << emit_count;
        emitting[emit_data_count++] = 0x00;
        emit_count++;
    }

    printf("Emit mask = %c", emit_mask);
    for (i = 0; i < emit_data_count; i++)
        putchar(emitting[i]);

    emit_data_count = 0;
    emit_count = 0;
    emit_mask = 0;
}

int main(int argc, char *argv[])
{
    int i = 0, c;  // This line declares two integer variables, i and c. i is initialized to 0, and c is declared but not yet initialized.
    c = getchar(); // Here, the program reads the first character from standard input using the getchar function and stores it in the variable c.

    while (c != EOF)
    {
        /* This line starts a while loop that will continue executing as long as the value of c is not equal to EOF, which stands for "end of file."
        This loop will keep running as long as there is more input to process.*/

        /* Within the loop, the program performs a bitwise XOR operation between the current character c and the i-th element of the last array.
        The result of this operation is then bitwise ANDed with 0xFF (hexadecimal value 0xFF), which effectively limits the result to 8 bits.
        The result is passed to a function called emit, which is responsible for handling the output of the transformed data.*/
        emit((c ^ last[i]) & 0xFF);

        last[i] = c;

        if (i == sizeof(last) - 1)
        {
            i = 0;
        }
        else
        {
            i++;
        }

        c = getchar();
    }
    // After the loop ends (likely when EOF is encountered), the program calls emit_flush, which is expected to perform any final output operations or cleanup.
    emit_flush();
}