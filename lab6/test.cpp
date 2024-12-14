// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include "../../../MeIoN_Lib/Z_H/MeIoN_sth_for_os.hpp"
#include "../../../MeIoN_Lib/Z_H/MeIoN_debug.hpp"
#else
#include <bits/stdc++.h>
#include <pthread.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

#include <list>
#include <mutex>
#include <thread>
#include <type_traits>
#include <typeindex>
#define debug(...) void(0721)
#endif

#define meion auto
#define iroha return

using std::string, std::vector, std::bitset, std::array, std::set, std::map,
      std::pair;

constexpr int L = 100, B = 512, K = 10, max_files = 10;

class moe_mem {
    char ldisk[L][B];  // 用二维数组表示内存块
    bool bitmap[L];    // 用于管理内存块使用情况的位图

   public:
    moe_mem(int sz = max_files) {
        memset(ldisk, 0, sizeof ldisk);    // 初始化内存块为0
        memset(bitmap, 0, sizeof bitmap);  // 初始化位图为0
    }

    int read(int i, char *s) {
        if (i < 0 or i > L - 1) iroha - 1;  // 检查索引是否有效
        memcpy(s, ldisk[i], B);  // 从内存块中复制数据到缓冲区
        iroha B;                 // 返回读取的字节数
    }
    int write(int i, char *s) {
        if (i < 0 or i > L - 1) iroha - 1;  // 检查索引是否有效
        memcpy(ldisk[i], s, B);             // 将数据写入指定内存块
        iroha B;
    }
    // 清除位图中的标记
    void fbits(int i) {
        assert(i < L and i > -1);  // 检查索引是否有效
        bitmap[i] = false;
    }
    // 设置位图中的标记
    void sbits(int i) {
        assert(i < L and i > -1);  // 检查索引是否有效
        bitmap[i] = true;
    }
    // 获取位图中的状态
    bool bit(int i) {
        assert(i < L and i > -1);  // 检查索引是否有效
        iroha bitmap[i];
    }
};

// 定义类lycoris，用于模拟文件系统
class lycoris {
    // 文件描述符结构体
    struct file_descriptor {
        int length;            // 文件长度
        array<int, 3> blocks;  // 文件所在的内存块数组
        file_descriptor(int sz = -1, int base = -1) : length(sz) {
            blocks.fill(base);  // 初始化文件块数组
        }
    };
    // 打开文件的表项
    struct open_file_entry {
        char buffer[B];      // 文件缓冲区
        int pointer;         // 当前指针位置
        int descriptor_idx;  // 文件描述符索引
        bool is_open;        // 文件是否打开
        open_file_entry() : pointer(0), descriptor_idx(-1), is_open(false) {
            memset(buffer, 0, sizeof buffer);  // 初始化缓冲区
        }
    };

    int size;                                  // 文件描述符数量
    moe_mem takina;                            // 内存管理实例
    vector<file_descriptor> file_descriptors;  // 文件描述符数组
    map<string, int> directory;                // 目录
    vector<open_file_entry> open_file_table;   // 打开文件表

   public:
    
    lycoris(int sz) : size(sz), file_descriptors(sz), open_file_table(sz) {
        std::cout << "Ciallo～(∠・ω< )⌒★" << ' ' << "enter your command: " << std::endl;
        std::cout << "(create, destroy, open, close, read, "
                     "write, lseek, list, exit)"
                  << std::endl;
    }
    
    // 创建文件
    bool create(const string &filename) {
        if (directory.size() + 1 > size) {
            iroha std::cout << "file limit exceeded" << std::endl, false;
        }

        if (directory.contains(filename)) {
            iroha std::cout << "file already exists" << std::endl, false;
        }
        
        int idx = -1;
        for (int i = 0; i < size; ++i) {
            if (file_descriptors[i].length == -1) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            iroha std::cout << "no available file descriptors" << std::endl, false;
        }

        directory[filename] = idx;         // 将文件添加到目录
        file_descriptors[idx].length = 0;  // 初始化文件描述符
        iroha std::cout << "file create success" << std::endl, true;
    }

    // 销毁文件
    bool destroy(const string &filename) {
        if (not directory.contains(filename)) {
            iroha std::cout << "file not found" << std::endl, false;
        }

        int idx = directory[filename];
        for (int block : file_descriptors[idx].blocks) {
            if (block != -1) {
                takina.fbits(block);  // 清除已分配的内存块
            }
        }

        file_descriptors[idx] = file_descriptor(0, 1);  // 重置文件描述符
        directory.erase(filename);  // 从目录中删除文件

        iroha std::cout << "file deleted success" << std::endl, true;
    }

    // 打开文件
    int open(const string &filename) {
        if (not directory.contains(filename)) {
            iroha std::cout << "file not found" << std::endl, -1;
        }

        int idx = directory[filename];
        for (int i = 0; meion &file : open_file_table) {
            if (not file.is_open) {
                file.descriptor_idx = idx;
                file.pointer = 0;
                file.is_open = true;

                if (file_descriptors[idx].blocks[0] != -1) {
                    takina.read(file_descriptors[idx].blocks[0],
                                file.buffer);  // 从磁盘读取文件内容
                }

                iroha std::cout << "file opened success" << std::endl, i;
            }
            ++i;
        }
        iroha std::cout << "file opened fail" << std::endl, -1;
    }

    // 关闭文件
    bool close(int idx) {
        if (idx < 0 or idx > size - 1 or not open_file_table[idx].is_open) {
            iroha std::cout << "invalid file index" << std::endl, false;
        } 

        int fidx = open_file_table[idx].descriptor_idx;
        if (file_descriptors[fidx].blocks[0] != -1) {
            takina.write(file_descriptors[fidx].blocks[0],
                         open_file_table[idx].buffer);  // 写入数据到磁盘
        }

        open_file_table[idx] = open_file_entry();  // 重置打开文件表项
        iroha std::cout << "file closed success" << std::endl, true;
    }

    // 读取文件
    int read(int idx, char *mem_area, int count) {
        if (idx < 0 or idx > size - 1 or not open_file_table[idx].is_open) {
            iroha std::cout << "invalid file index" << std::endl, -1;
        }

        meion &[buffer, pointer, fidx, is_open] = open_file_table[idx];
        int bits = 0;

        while (count and pointer < file_descriptors[fidx].length) {
            int b_idx = pointer / B;
            int off = pointer % B;

            if (b_idx > 2 or file_descriptors[fidx].blocks[b_idx] == -1) {
                break;
            }
            if (off == 0) {
                takina.read(file_descriptors[fidx].blocks[b_idx],
                            buffer);  // 读取块数据到缓冲区
            }

            int btc = std::min(count, B - off);
            std::memcpy(mem_area + bits, buffer + off, btc);

            bits += btc;
            count -= btc;
            pointer += btc;
        }
        iroha bits;
    }

    // 写入文件
    int write(int idx, const char *mem_area, int count) {
        if (idx < 0 or idx > size - 1 or not open_file_table[idx].is_open) {
            iroha std::cout << "invalid file index" << std::endl, -1;
        }

        meion &[buffer, pointer, fidx, is_open] = open_file_table[idx];
        int bits = 0;
        while (count) {
            int b_idx = pointer / B;  // 计算当前文件指针对应的块索引
            int off = pointer % B;    // 计算当前写入偏移量

            if (b_idx > 2) {
                std::cout << "file size limit exceeded" << std::endl;
                break;
            }

            if (file_descriptors[fidx].blocks[b_idx] == -1) { // 如果该块没有分配，则进行分配操作
                for (int i = K; i < L; ++i) {
                    if (not takina.bit(i)) {
                        takina.sbits(i);
                        file_descriptors[fidx].blocks[b_idx] = i;
                        break;
                    }
                }

                if (file_descriptors[fidx].blocks[b_idx] == -1) {
                    std::cout << "no free blocks available" << std::endl;
                    break;
                }
            }

            // 将数据写入缓冲区
            int btc = std::min(count, B - off);
            memcpy(buffer + off, mem_area + bits, btc);
            takina.write(file_descriptors[fidx].blocks[b_idx], buffer);

            bits += btc;
            count -= btc;
            pointer += btc;
            if (pointer > file_descriptors[fidx].length) {
                file_descriptors[fidx].length = pointer;
            }
        }
        iroha bits;
    }

    // 设定文件指针
    bool lseek(int idx, int pos) {
        if (idx < 0 or idx > size - 1 or not open_file_table[idx].is_open) {
            iroha std::cout << "invalid file index" << std::endl, false;
        }

        int fidx = open_file_table[idx].descriptor_idx;
        if (pos < 0 or pos > file_descriptors[fidx].length) {
            iroha std::cout << "invalid seek position" << std::endl, false;
        }

        iroha open_file_table[idx].pointer = pos, true;
    }

    // 列出目录中的所有文件
    void list_directory() {
        std::cout << "directory: " << std::endl;
        for (const meion &[name, idx] : directory) {
            std::cout << "filename: " << name
                      << " length: " << file_descriptors[idx].length
                      << std::endl;
        }
    }
};

// test
inline void MeIoN_is_UMP45() {
    lycoris chisato(max_files);
    string command;
    while ((std::cout << "> ").flush(), std::cin >> command) {
        if (command == "create") {
            std::string filename;
            std::cin >> filename;
            chisato.create(filename);
        } else if (command == "destroy") {
            std::string filename;
            std::cin >> filename;
            chisato.destroy(filename);
        } else if (command == "open") {
            std::string filename;
            std::cin >> filename;
            meion idx = chisato.open(filename);
            if (idx != -1) {
                std::cout << "index: " << idx << std::endl;
            }
        } else if (command == "close") {
            int index;
            std::cin >> index;
            chisato.close(index);
        } else if (command == "read") {
            int index, count;
            std::cin >> index >> count;
            vector<char> buffer(count + 1);
            int bytesRead = chisato.read(index, buffer.data(), count);
            if (bytesRead > 0) {
                std::cout << "Read " << bytesRead << " bytes: ";
                for (int i = 0; i < bytesRead; ++i) {
                    std::cout << buffer[i];
                }
                std::cout << std::endl;
            }
        } else if (command == "write") {
            int index, count;
            std::cout << "enter idx and size: " << std::endl;
            std::cin >> index >> count;
            string buffer;
            std::cout << "Enter data to write: " << std::endl;
            std::cin.ignore();
            std::getline(std::cin, buffer);
            int bytesWritten = chisato.write(index, buffer.data(), count);
            std::cout << "Written " << bytesWritten << " bytes" << std::endl;
        } else if (command == "lseek") {
            int index, pos;
            std::cin >> index >> pos;
            chisato.lseek(index, pos);
        } else if (command == "list") {
            chisato.list_directory();
        } else if (command == "exit") {
            std::cout << "system exited" << std::endl;
            break;
        } else {
            std::cout << "unknown command, zako user" << std::endl;
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(12);

    int T = 1;
    while (T--) {
        MeIoN_is_UMP45();
    }
    iroha 0;
}