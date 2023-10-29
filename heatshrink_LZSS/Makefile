# This makefile compile and test

CC = gcc
CFLAGS   ?= -O3
CFLAGS   += -std=gnu99 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Wstrict-prototypes
FLAGS    := $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)
# FLAGS    := $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)

OBJFILES = main.o heatshrink_encoder.o heatshrink_decoder.o
TARGET   = main
default: all
all: main

# $(LZ4DIR)/liblz4.a: $(LZ4DIR)/lz4.c $(LZ4DIR)/lz4hc.c $(LZ4DIR)/lz4frame.c $(LZ4DIR)/lz4.h $(LZ4DIR)/lz4hc.h $(LZ4DIR)/lz4frame.h $(LZ4DIR)/lz4frame_static.h
# 	$(MAKE) -C $(LZ4DIR) liblz4.a

main: $(OBJFILES)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJFILES)

# fileCompress: fileCompress.c $(LZ4DIR)/liblz4.a
# 	$(CC) $(FLAGS) $^ -o $@$(EXT)

# simpleBuffer: simple_buffer.c $(LZ4DIR)/liblz4.a
# 	$(CC) $(FLAGS) $^ -o $@$(EXT)

# compressFunctions: compress_functions.c $(LZ4DIR)/liblz4.a
# 	$(CC) $(FLAGS) $^ -o $@$(EXT) -lrt

clean:
	rm -f $(OBJFILES) $(TARGET)
	@echo Cleaning completed
