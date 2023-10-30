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

main: $(OBJFILES)
	$(CC) $(FLAGS) -o $(TARGET) $(OBJFILES)

# fileCompress: fileCompress.c $(LZ4DIR)/liblz4.a
# 	$(CC) $(FLAGS) $^ -o $@$(EXT)

clean:
	rm -f $(OBJFILES) $(TARGET)
	@echo Cleaning completed
