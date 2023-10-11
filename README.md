# Compression
Lossy compression methods include DCT (Discrete Cosine Transform), Vector Quantisation, and Transform Coding while Lossless compression methods include RLE (Run Length Encoding), string-table compression, LZW (Lempel Ziff Welch), and zlib.

## Brief introduction
### 1. SVD and PRD

### 2. Lempel-ziv
This algorithm compresses repetitive sequences of data very well. Since the codewords are 12 bits, any single encoded character will expand the data size rather than reduce it.

```bash

```

#### Advantages of LZW over Huffman: 

* LZW requires no prior information about the input data stream.
* LZW can compress the input stream in one single pass.
* Another advantage of LZW is its simplicity, allowing fast execution.
* High Compression Ratio: LZW can achieve high compression ratios, particularly for text-based data, which can significantly reduce file sizes and storage requirements.
  
* Fast Decompression: LZW decompression is typically faster than other compression algorithms, making it a good choice for applications where decompression speed is critical.
  
* Universal Adoption: LZW is widely used and supported across a variety of software applications and operating systems, making it a popular choice for compression and decompression.
  
* Dynamic Compression: LZW uses a dynamic compression algorithm, meaning it adapts to the data being compressed, which allows it to achieve high compression ratios even for data with repetitive patterns.

#### Disadvantages:
* Patent Issues: LZW compression was patented in the 1980s, and for many years its use was subject to licensing fees, which limited its adoption in some applications.

* Memory Requirements: LZW compression requires significant memory to maintain the compression dictionary, which can be a problem for applications with limited memory resources.

* Compression Speed: LZW compression can be slower than some other compression algorithms, particularly for large files, due to the need to constantly update the dictionary.

* Limited Applicability: LZW compression is particularly effective for text-based data, but may not be as effective for other types of data, such as images or video, which have different compression requirements.

#### Resources:  

[LZW (Lempel–Ziv–Welch) Compression technique Geeks for Geeks](https://www.geeksforgeeks.org/lzw-lempel-ziv-welch-compression-technique/)
mit.edu
Dave.Marshall
duke.edu
michael.dipperstein
LZW(Youtube)
faculty.kfupm.edu.sa
github repository(kmeelu)

### 3. Brotli

### 4. memcpy

### 5. zstd


## Benchmarks
The benchmark uses lzbench, compiled with GCC v8.2.0 on Linux 64-bits (Ubuntu 4.18.0-17). The reference system uses a Core i7-1260p CPU @ 4GHz.

| Compressor                    | Compression ratio (CR) | Compression speed (Mb/s) | Decompression speed (Mb/s) | Assigned to |
| ----------------------------- | ---------------------- | ------------------------ | -------------------------- | ----------- |
| SVD and PRD                   |                        |                          |                            | Faruq       |
| Lempel-ziv                    |                        |                          |                            | Shiva       |
| Brotli                        |                        |                          |                            | Shiva       |
| memcpy                        |                        |                          |                            | Shiva       |
| zstd                          |                        |                          |                            | Shiva       |
| wavelet-based-ecg-compression |                        |                          |                            | Shiva       |