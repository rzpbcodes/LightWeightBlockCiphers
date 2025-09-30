# On the Efficiency of Software Implementations of Lightweight Block Ciphers from the Perspective of Programming Languages

This repository contains the implementation and benchmarking results from the paper *"On the Efficiency of Software Implementations of Lightweight Block Ciphers from the Perspective of Programming Languages"*.

## Key Contributions

- **Analysis of Implementation Choices**: We examine how different software implementations, programming languages, and platforms (including cloud environments) affect the performance of the LED block cipher.
- **Implementation Types**: We define six different lookup-table-based (LUT) software implementations for the LED cipher, ranging from memory-optimized to throughput-optimized variants.
- **Platform Comparison**: We benchmark 72 unique implementations (combinations of four programming languages and three key sizes) across 32-bit and 64-bit platforms running two major operating systems (Windows and Linux) on **Amazon Web Services (AWS)** cloud.
- **Results**: Our benchmarks reveal significant performance differences across platforms and languages, highlighting the impact on throughput and software efficiency.

## Paper Link
The full paper is available for download are [ScienceDirect](https://www.sciencedirect.com/science/article/pii/S0167739X19310519) and [ePrint](https://eprint.iacr.org/2019/1218.pdf)

## Implementations
We implemented the LED block cipher for three different key sizes (64, 80, and 128 bits) using six different LUT-based methods. These implementations were coded in the following languages:
- **Java**
- **C#**
- **C++**
- **Python**

The implementation types include:
1. **4-bit Serial**
2. **4-bit LUT**
3. **8-bit LUT**
4. **16-bit LUT**
5. **32-bit LUT**
6. **64-bit LUT**

Each method was designed with trade-offs between memory consumption and throughput performance, offering various optimizations depending on the use case.

## Benchmarking
We performed thorough benchmarking using EC2 instances in the AWS cloud, running the implementations on both **32-bit and 64-bit versions** of **Windows** and **Linux**. The following performance metrics were considered:
- **Throughput**: The rate at which data is encrypted or decrypted.
- **Software Efficiency (SE)**: The throughput per unit of code size, indicating the efficiency of the implementation.

