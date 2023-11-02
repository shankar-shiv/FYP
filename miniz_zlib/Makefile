# This makefile compile and test

# **Debugging specific**
# If you're using GCC as compiler add to the CFLAGS variable the -g option. Then you'll be able to debug the resulting executable using the gdb command.
# -ggdb would provide more debug information, but is gdb specific. If you use gdb it is worth it.
# https://stackoverflow.com/questions/9391807/how-to-debug-a-c-code-that-is-compiled-using-a-makefile

# Before: -std=gnu99
# After: -std=c11
CC = gcc
CFLAGS   ?= -O3
CFLAGS   += -g -std=c11 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Wstrict-prototypes
FLAGS    := $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)
# FLAGS    := $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)

OBJFILES = main.o miniz.c
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
