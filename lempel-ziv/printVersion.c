// LZ4 trivial example : print Library version number

#include <stdio.h>
#include "../.libraries/lz4-1.9.4/lib/lz4file.h" // relative path to lz4file.h

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    printf("Hello World ! LZ4 Library version = %d\n", LZ4_versionNumber());
    return 0;
}
