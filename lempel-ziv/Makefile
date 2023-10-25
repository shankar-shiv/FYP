# This makefile compile and test
# example programs, using (mostly) LZ4 streaming library,

CPPFLAGS += -I../lib
CFLAGS   ?= -O3
CFLAGS   += -std=gnu99 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Wstrict-prototypes
FLAGS    := $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(MOREFLAGS)

TESTFILE  = Makefile
LZ4DIR   := ../.libraries/lz4-1.9.4/lib
LZ4       = ../.libraries/lz4-1.9.4/programs/lz4

# include ../Makefile.inc

default: all

all: printVersion fileCompress

$(LZ4DIR)/liblz4.a: $(LZ4DIR)/lz4.c $(LZ4DIR)/lz4hc.c $(LZ4DIR)/lz4frame.c $(LZ4DIR)/lz4.h $(LZ4DIR)/lz4hc.h $(LZ4DIR)/lz4frame.h $(LZ4DIR)/lz4frame_static.h
	$(MAKE) -C $(LZ4DIR) liblz4.a

printVersion: printVersion.c $(LZ4DIR)/liblz4.a
	$(CC) $(FLAGS) $^ -o $@$(EXT)

fileCompress: fileCompress.c $(LZ4DIR)/liblz4.a
	$(CC) $(FLAGS) $^ -o $@$(EXT)

$(LZ4) :
	$(MAKE) -C ../programs lz4

# test : all $(LZ4)
# 	@echo "\n=== Print Version ==="
# 	./printVersion$(EXT)
# 	@echo "\n=== Simple compression example ==="
# 	./simpleBuffer$(EXT)
# 	@echo "\n=== Double-buffer ==="
# 	./doubleBuffer$(EXT) $(TESTFILE)
# 	@echo "\n=== Ring Buffer ==="
# 	./ringBuffer$(EXT)   $(TESTFILE)
# 	@echo "\n=== Ring Buffer + LZ4 HC ==="
# 	./ringBufferHC$(EXT) $(TESTFILE)
# 	@echo "\n=== Compress line by line ==="
# 	./lineCompress$(EXT) $(TESTFILE)
# 	@echo "\n=== Dictionary Random Access ==="
# 	./dictionaryRandomAccess$(EXT) $(TESTFILE) $(TESTFILE) 1100 1400
# 	@echo "\n=== Frame compression ==="
# 	./frameCompress$(EXT) $(TESTFILE)
# 	$(LZ4) -vt $(TESTFILE).lz4
# 	@echo "\n=== file compression ==="
# 	./fileCompress$(EXT) $(TESTFILE)
# 	$(LZ4) -vt $(TESTFILE).lz4

.PHONY: cxxtest
cxxtest: CFLAGS := -O3 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Werror
cxxtest: clean
	CC=$(CXX) $(MAKE) -C . all CFLAGS="$(CFLAGS)"

clean:
	@rm -f core *.o *.dec *-0 *-9 *-8192 *.lz4s *.lz4 \
	 printVersion$(EXT) doubleBuffer$(EXT) dictionaryRandomAccess$(EXT) \
	 ringBuffer$(EXT) ringBufferHC$(EXT) lineCompress$(EXT) frameCompress$(EXT) \
	 fileCompress$(EXT) compressFunctions$(EXT) simpleBuffer$(EXT)
	@echo Cleaning completed
