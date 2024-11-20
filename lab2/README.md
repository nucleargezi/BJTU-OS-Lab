# sudoku_solution_validator

该项目实现了一个多线程的数独验证器。它通过并行验证给定的 9x9 数独网格，检查其是否有效。
 
## Requirements
C++20 或更高版本
标准 C++ 库

## How to Build

1. 确保您拥有支持 C++20 或更高版本的 C++ 编译器。
2. 使用您偏好的构建系统，或者直接通过编译器命令进行编译。例如，使用 g++：
```sh
g++ -std=c++20 sudoku_solution_validator.cpp -o sudoku_solution_validator
```
## How to Run

在构建项目后，运行可执行文件：

```sh
./sudoku_solution_validator
```

# multithreaded_sorting_application
该项目实现了一个多线程归并排序算法。它包括对不同容器类型（std::vector、std::list、std::array）的排序功能，并对比std::sort和多线程归并排序的时间效率。 

## Requirements
C++20 或更高版本
标准 C++ 库

## How to Build

1. 确保您拥有支持 C++20 或更高版本的 C++ 编译器。
2. 使用您偏好的构建系统，或者直接通过编译器命令进行编译。例如，使用 g++：
```sh
g++ -std=c++20 multithreaded_sorting_application.cpp -o multithreaded_sorting_application
```
## How to Run

在构建项目后，运行可执行文件：

```sh
./multithreaded_sorting_application
```

## Notes
如果程序有误排序失败会触发assert