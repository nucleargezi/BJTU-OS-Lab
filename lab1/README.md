#### 使用说明
利用c++编写的unix外壳, 接受用户命令, 在单独的进程中执行每个命令, 实现了创建子进程和创建历史专题的功能 
 

编译命令 :  
```cpp
"cd $dir && g++ -std=c++2a $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt" 
```
在linux下编译 需要c++20及以上版本 

随后可直接运行可执行文件