# # This makefile compile and test

# # **Debugging specific**
# # If you're using GCC as compiler add to the CFLAGS variable the -g option. Then you'll be able to debug the resulting executable using the gdb command.
# # -ggdb would provide more debug information, but is gdb specific. If you use gdb it is worth it.
# # https://stackoverflow.com/questions/9391807/how-to-debug-a-c-code-that-is-compiled-using-a-makefile

# # Before: -std=gnu99
# # After: -std=c11
# CC = gcc
# CFLAGS ?= -O3
# CFLAGS += -g -std=c11 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Wstrict-prototypes
# FLAGS := $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)
# # FLAGS    := $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)

# --------------------------------------------------------------------------------------------------

# Compiler and flags
CC = gcc
CFLAGS = -O3 -g -ggdb3 -std=c11 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Wstrict-prototypes
LDFLAGS =
MOREFLAGS =

# Source files and output target
SRCFILES = main.c unishox2.c
OBJFILES = $(SRCFILES:.c=.o)
TARGET = main

# Targets
default: all

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) $(MOREFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<


clean:
	rm -f $(OBJFILES) $(TARGET)
	@echo Cleaning completed

.PHONY: default all clean

# Second version of makefile

# CC = gcc
# CXX = g++
# CFLAGS = -O3 -std=c11 -Wall
# CXXFLAGS = -O3 -std=c++11 -Wall
# LDFLAGS =

# C_SRC = main.c
# CXX_SRC = unishox2.cpp

# C_OBJ = $(C_SRC:.c=.o)
# CXX_OBJ = $(CXX_SRC:.cpp=.o)

# TARGET = main

# all: $(TARGET)

# $(TARGET): $(C_OBJ) $(CXX_OBJ)
# 	$(CXX) -o $(TARGET) $(C_OBJ) $(CXX_OBJ) $(LDFLAGS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean:
# 	rm -f $(C_OBJ) $(CXX_OBJ) $(TARGET)
