# word processor

This project consists of writing a program that translates logical to physical addresses for a virtual
address space of size 2^16 = 65,536 bytes. Your program will read from a file containing logical
addresses and, using a TLB and a page table, will translate each logical address to its
corresponding physical address and output the value of the byte stored at the translated physical
address.
Your learning goal is to use simulation to understand the steps involved in translating logical to
physical addresses. This will include resolving page faults using demand paging, managing a TLB ,
and implementing a page-replacement algorithm.
 
## Requirements
C++20 或更高版本 

标准 C++ 库

## How to Build
1. 确保您拥有支持 C++20 或更高版本的 C++ 编译器。
2. 使用您偏好的构建系统，或者直接通过编译器命令进行编译。例如，使用 g++：
```sh
g++ -std=c++20 virtual_memory_manager.cpp -o tt
# fifo & lru
g++ -std=c++20 virtual_memory_manager.cpp2 -o tt
```
3. 也可以直接使用go.sh脚本编译运行
```sh
bash go.sh
```
## How to Run

在构建项目后，运行可执行文件, 后面接着三个参数分别是 addresses, BACKING_STORE.bin, 输出文件名

```sh
./tt addersses.txt BACKING_STORE.bin my_out
# 
./tt addersses.txt BACKING_STORE.bin my_out fifo(lua)
```
也可以直接使用go.sh脚本编译运行
