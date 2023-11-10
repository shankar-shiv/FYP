#ifndef HEATSHRINK_CONFIG_H
#define HEATSHRINK_CONFIG_H

/* Should functionality assuming dynamic allocation be used? */
#ifndef HEATSHRINK_DYNAMIC_ALLOC
#define HEATSHRINK_DYNAMIC_ALLOC 0
#endif

#if HEATSHRINK_DYNAMIC_ALLOC
/* Optional replacement of malloc/free */
#define HEATSHRINK_MALLOC(SZ) malloc(SZ)
#define HEATSHRINK_FREE(P, SZ) free(P)
#else
/* Required parameters for static configuration */
#define HEATSHRINK_STATIC_INPUT_BUFFER_SIZE 32
#define HEATSHRINK_STATIC_WINDOW_BITS 10
#define HEATSHRINK_STATIC_LOOKAHEAD_BITS 5
#endif

/* Turn on logging for debugging. */
#define HEATSHRINK_DEBUGGING_LOGS 0

/* Use indexing for faster compression. (This requires additional space.) heatshrink is based on LZSS, since it's particularly suitable for compression in small amounts of memory.
It can use an optional, small index to make compression significantly faster, but otherwise can run in under 100 bytes of memory.
The index currently adds 2^(window size+1) bytes to memory usage for compression, and temporarily allocates 512 bytes on the stack during index construction (if the index is enabled).*/
#define HEATSHRINK_USE_INDEX 1

#endif
