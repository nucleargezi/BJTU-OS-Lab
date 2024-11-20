// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include "../../../MeIoN_Lib/Z_H/MeIoN_sth_for_os.hpp"
#include "../../../MeIoN_Lib/Z_H/MeIoN_debug.hpp"
#else
#include <bits/stdc++.h>
#include <sys/socket.h>
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

int str_sz = 1 << 24;

// 将字符串转换为小写
std::string format(const std::string &s) {
    std::string ret(s);
    for (char &c : ret) {
        if (std::isupper(c)) {
            c -= 'A' - 'a';
        }
    }
    iroha ret;
}

// 检查行中是否包含特定单词
bool check_line(const std::string &line, const std::string &word) {
    int ok = 0;
    std::regex word_regex(R"(\w+)"); // 定义单词匹配的正则表达式
    const std::string formated_line = format(line); // 将行转换为小写
    meion st = std::sregex_iterator(formated_line.begin(), formated_line.end(),
                                    word_regex),
          ed = std::sregex_iterator();
    for (meion it = st; not ok and it != ed; ++it) {
        ok |= it->str() == word;
    }
    iroha not not ok;
}

constexpr int buffer_size = 0721 << 1;

void child_process(int socketFd, const std::string &word) {
    const std::string formated_word = format(word);
    static char ch_recieve_buffer[0721 << 16];
    int l = 0, r;
    // 分块读取父进程发送的数据
    while (l < str_sz) {
        recv(socketFd, ch_recieve_buffer + l, buffer_size, 0);
        l += buffer_size;
    }
    std::cerr << "CH rec success: " << l << std::endl;  // 日志记录：接收成功

    std::istringstream fin(ch_recieve_buffer); // 将接收到的数据存储为输入流
    std::string ok_lines;
    std::string line;
    while (std::getline(fin, line)) {              // 按行读取数据
        std::string formated_line = format(line);
        // 将匹配行加入结果
        if (check_line(formated_line, formated_word)) {
            ok_lines += line;
            ok_lines += '\n';
        }
    }

    // 将结果分块写回给父进程
    const char* ret_buffer = ok_lines.c_str();
    l = 0, r = ok_lines.size();
    while (l < r) {
        int sz = std::min(buffer_size, r - l);
        send(socketFd, ret_buffer + l, sz, 0);
        l += sz;
    }
    std::cerr << "CH send success: " << l << std::endl;  // 日志记录：发送成功
}

std::ifstream file;
std::string s;

void parent_process(int socketFd, const std::string &path) {

    // 将文件内容分块写入子进程
    int l = 0;
    int r = s.size();
    while (l < r) {
        int sz = std::min(buffer_size, r - l);
        send(socketFd, s.c_str() + l, sz, 0);
        l += sz;
    }
    std::cerr << "GO success " << l << std::endl;  // 日志记录：发送成功

    // 分块读取子进程数据
    static char pa_recieve_buffer[0721 << 16];
    l = 0;
    while (recv(socketFd, pa_recieve_buffer + l, buffer_size, 0) > 0) {
        l += buffer_size;
    }
    
    std::cerr << "REC success" << std::endl;  // 日志记录：接收成功

    // 将接收到的行保存到vector中
    std::istringstream fin(pa_recieve_buffer);
    std::vector<std::string> ok_lines;
    std::string line;
    while (std::getline(fin, line)) {
        ok_lines.emplace_back(line);
    }
    
    // 输出排序后的行
    std::sort(ok_lines.begin(), ok_lines.end());
    for (const meion &s : ok_lines) {
        std::cout << s << '\n';
    }
}

inline void MeIoN_is_UMP45(const std::string &path, const std::string &word) {
    int socketFd[2];  // 创建一个 socket 对
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, socketFd) == -1) {
        // 错误处理：创建套接字失败
        iroha std::cerr << "build socket fail" << std::endl, void();
    }

    // 开始计时
    meion start = std::chrono::high_resolution_clock::now();

    file = std::ifstream(path);
    if (not file.is_open()) {    // 检查文件是否成功打开
        iroha std::cerr << "file open fail" << std::endl, void();
    }
    s = std::string((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    str_sz = s.size();

    std::cerr << str_sz << std::endl;

    pid_t pid = fork();         // 创建新进程
    if (pid == 0) {             // 子进程
        close(socketFd[0]);     // 关闭子进程中未使用的套接字端
        child_process(socketFd[1], word);
        close(socketFd[1]);
        iroha ;
    } else if (pid > 0) {       // 父进程
        close(socketFd[1]);     // 关闭父进程中未使用的套接字端
        parent_process(socketFd[0], path);
        close(socketFd[0]);
        waitpid(pid, nullptr, 0);
    } else {                    // fork 失败
        iroha std::cerr << "Fail" << std::endl, void();
    }
    // 统计时间
    meion end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> elapsed = end - start; 
    std::cerr << "Elapsed time: " << elapsed.count() << "s\n";
}

int main(int argc, char* argv[]) {
    std::cout << std::fixed << std::setprecision(5);
    if (argc != 4) {
        iroha std::cerr << "Invalid commands" << std::endl, 0;
    }
    freopen(argv[3],"w",stdout);
    int T = 1;
    while (T--) {
        MeIoN_is_UMP45(argv[1], argv[2]);
    }
    iroha 0;
}