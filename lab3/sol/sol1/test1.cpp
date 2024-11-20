// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include "../../../MeIoN_Lib/Z_H/MeIoN_sth_for_os.hpp"
#include "../../../MeIoN_Lib/Z_H/MeIoN_debug.hpp"
#else
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <mutex>
#include <thread>
#include <list>
#include <typeindex>
#include <type_traits>
#define debug(...) void(0721)
#endif

#define meion auto
#define iroha return

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

void child_process(int writepip[], int readpip[], const std::string &word) {
    close(writepip[1]);
    close(readpip[0]);

    const std::string formated_word = format(word);
    
    static char ch_recieve_buffer[0721 << 16];
    int l = 0, r;
    // 分块读取父进程发送的数据
    while (read(writepip[0], ch_recieve_buffer + l, buffer_size) > 0) {
        l += buffer_size;
    }
    close(writepip[0]);
    std::cerr << "CH rec success" << std::endl;

    // meion st = std::chrono::high_resolution_clock::now();

    std::istringstream fin(ch_recieve_buffer); // 将接收到的数据存储为输入流
    std::string ok_lines;
    std::string line;
    while (std::getline(fin, line)) {
        std::string formated_line = format(line);
        // 将匹配行加入结果
        if (check_line(formated_line, formated_word)) {
            ok_lines += line;
            ok_lines += '\n';
        }
    }

    // 计算处理字符串的耗时
    // meion ed = std::chrono::high_resolution_clock::now(); 
    // std::chrono::duration<double> elapsed = ed - st; 
    // std::cerr << "check time: " << elapsed.count() << "s\n";

    // 将结果分块写回给父进程
    const char* ret_buffer = ok_lines.c_str();
    l = 0, r = ok_lines.size();
    while (l < r) {
        int sz = std::min(buffer_size, r - l);
        write(readpip[1], ret_buffer + l, sz);
        l += sz;
    }
    close(readpip[1]);
    std::cerr << "CH send success" << std::endl;
}

void parent_process(int writepip[], int readpip[], const std::string &path) {
    close(writepip[0]);
    close(readpip[1]);

    std::ifstream file(path);
    if (not file.is_open()) {
        iroha std::cerr << "file open fail" << std::endl, void();
    }
    std::string s((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
    file.close();

    const char* file_buffer = s.c_str();

    // 将文件内容分块写入子进程
    int l = 0;
    int r = s.size();
    while (l < r) {
        int sz = std::min(buffer_size, r - l);
        write(writepip[1], file_buffer + l, sz);
        l += sz;
    }
    close(writepip[1]);
    std::cerr << "GO success" << std::endl;

    // 分块读取子进程数据
    static char pa_recieve_buffer[0721 << 16];
    l = 0;
    while (read(readpip[0], pa_recieve_buffer + l, buffer_size) > 0) {
        l += buffer_size;
    }
    close(readpip[0]);
    
    std::cerr << "REC success" << std::endl;

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
    const std::string formated_word = format(word);
    int to_parent_cedrus_deodara[2] = {};
    int to_child_deodara_cedrus[2] = {};

    if (pipe(to_parent_cedrus_deodara) == -1 or pipe(to_child_deodara_cedrus) == -1) {
        std::cerr << "Fail" << std::endl;
        iroha;
    }
    // 开始计时
    meion start = std::chrono::high_resolution_clock::now();

    pid_t pid = fork();
    if (pid == 0) {
        child_process(to_child_deodara_cedrus, to_parent_cedrus_deodara, word);
        iroha ;
    } else if (pid > 0) {
        parent_process(to_child_deodara_cedrus, to_parent_cedrus_deodara, path);
        waitpid(pid, nullptr, 0);
    } else {
        std::cerr << "Fail" << std::endl;
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