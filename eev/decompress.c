#include <stdio.h>

char last[36];
int last_i;
void emit(char c)
{
    c ^= last[last_i];
    putchar(c);
    last[last_i] = c;

    if (last_i == sizeof(last) - 1)
        last_i = 0;
    else
        last_i++;
}

int main(int argc, char *argv[])
{
    int mc;
    int mask;
    mc = getchar();
    while (mc != EOF)
    {
        int c;
        mask = 0x1;
        while (mask != 0x100)
        {
            if ((mc & mask) == 0)
            {
                emit(0);
            }
            else
            {
                c = getchar();
                if (c != EOF && c != 0)
                    emit(c);
            }
            mask = mask << 1;
        }
        mc = getchar();
    }
}