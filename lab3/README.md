# word processor

该项目用三个程序实现了三种IPC方法, 用于完成相同的一个任务: 给定一个文本文件, 程序输出包含给定单词的行
 
## Requirements
C++20 或更高版本 

标准 C++ 库

## How to Build
1. 确保您拥有支持 C++20 或更高版本的 C++ 编译器。
2. 使用您偏好的构建系统，或者直接通过编译器命令进行编译。例如，使用 g++：
```sh
g++ -std=c++20 test1/2/3.cpp -o test1/2/3
```
## How to Run

在构建项目后，运行可执行文件, 后面接着三个参数分别是 读取文本路径, 查询单词, 输出文件名

```sh
./test1/2/3 file_path word out_file
```

也可以直接使用solx中的go.sh构建并运行