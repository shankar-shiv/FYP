# Different LZ4 bindings implemented in Python: https://lz4.org/#benchmarks

# Method 1: Simple way

# The recommended binding to use is the LZ4 frame format binding, since this provides interoperability with other implementations and language bindings.
# The simplest way to use the frame bindings is via the compress() and decompress() functions: https://python-lz4.readthedocs.io/en/stable/quickstart.html

import os
import lz4.frame
import time


def simple_compress_decompress():
    with open("/home/shankar/CAPSTONE/Capstone/.datasets/mitbih-train.csv", "rb") as f:
        input_data = f.read()

    compressed = lz4.frame.compress(
        data=input_data, compression_level=lz4.frame.COMPRESSIONLEVEL_MINHC
    )
    decompressed = lz4.frame.decompress(compressed)


# Method 2: Working with data in chunks
def chunks():
    with open("/home/shankar/CAPSTONE/Capstone/.datasets/mitbih-train.csv", "rb") as f:
        input_data = f.read()

    print(type(input_data))

    with lz4.frame.LZ4FrameCompressor() as compressor:
        compressed = compressor.begin()
        compressed += compressor.compress(input_data[: 10 * 128 * 1024])
        compressed += compressor.compress(input_data[10 * 128 * 1024 :])
        compressed += compressor.flush()
    with lz4.frame.LZ4FrameDecompressor() as decompressor:
        decompressed = decompressor.decompress(compressed[: len(compressed) // 2])
        decompressed += decompressor.decompress(compressed[len(compressed) // 2 :])


if __name__ == "__main__":
    start_time = time.perf_counter()
    chunks()
    # simple_compress_decompress()
    end_time = time.perf_counter()
    print(end_time - start_time, "seconds")
