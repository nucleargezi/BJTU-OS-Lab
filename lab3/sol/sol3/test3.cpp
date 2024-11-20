// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include "../../../MeIoN_Lib/Z_H/MeIoN_debug.hpp"
#include "../../../MeIoN_Lib/Z_H/MeIoN_sth_for_os.hpp"
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

// 定义共享内存大小和键值
constexpr int shm_size = 0721 << 16, 
              shm_file_content_key = 0721, 
              shm_result_key = 2887;

// 线程数据结构
struct thread_data {
    std::vector<std::string> lines; // 当前线程处理的行
    std::vector<std::string> res;   // 线程处理后筛选的结果
    std::string word;               // 关键字
    pthread_mutex_t *mutex;         // 线程锁
};

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
    iroha ok;
}

// 线程工作函数：处理分配的行并筛选出包含关键字的行
void *mygo(void *arg) {
    thread_data *data = static_cast<thread_data *>(arg);
    for (const auto &line : data->lines) {
        if (check_line(line, data->word)) {
            pthread_mutex_lock(data->mutex);
            data->res.emplace_back(line);
            pthread_mutex_unlock(data->mutex);
        }
    }
    iroha nullptr;
}

void child_process(const std::string formated_word) {

    // 获取文件内容的共享内存
    int shm_file_id = shmget(shm_file_content_key, shm_size, 0666);
    if (shm_file_id == -1) {
        iroha std::cerr << "child: get mem fail" << std::endl, void();
    }

    // 附加共享内存
    char *shm_file_ptr = static_cast<char *>(shmat(shm_file_id, nullptr, 0));
    if (shm_file_ptr == (char *)(-1)) {
        iroha std::cerr << "child: attach mem fail" << std::endl, void();
    }

    // 读取共享内存中的内容
    std::istringstream fin(shm_file_ptr);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fin, line)) {
        lines.emplace_back(line);
    }

    // 多线程处理
    static constexpr int n = 1 << 2;  // 线程数
    std::array<pthread_t, n> threads;
    std::array<thread_data, n> thread_data;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);

    size_t sz = lines.size() / n;
    for (int i = 0; i < n; ++i) {
        size_t l = i * sz, r = (i + 1 == n ? lines.size() : l + sz);
        thread_data[i] = {
            std::vector<std::string> {lines.begin() + l, lines.begin() + r},
            {},
            formated_word,
            &mutex};
        pthread_create(&threads[i], nullptr, mygo, &thread_data[i]);
    }
    for (int i = 0; i < n; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // 将结果写入共享内存
    std::ostringstream fout;
    for (int i = 0; i < n; ++i) {
        for (const meion &s : thread_data[i].res) {
            fout << s << '\n';
        }
    }
    int shm_result_id = shmget(shm_result_key, shm_size, IPC_CREAT | 0666);
    char *shm_result_ptr =
        static_cast<char *>(shmat(shm_result_id, nullptr, 0));
    snprintf(shm_result_ptr, shm_size, "%s", fout.str().c_str());

    // 释放资源
    shmdt(shm_file_ptr);
    shmdt(shm_result_ptr);
    pthread_mutex_destroy(&mutex);
}

// 主进程函数，负责文件读取、共享内存初始化和子进程管理
inline void MeIoN_is_UMP45(const std::string &path, const std::string &word) {
    const std::string formated_word = format(word);
    std::ifstream file(path);
    if (not file.is_open()) {
        iroha std::cerr << "file open fail" << std::endl, void();
    }

    meion start = std::chrono::high_resolution_clock::now();

    std::string s((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
    file.close();

    // 初始化共享内存
    int shm_file_id = shmget(shm_file_content_key, shm_size, IPC_CREAT | 0666);
    if (shm_file_id == -1) {
        iroha std::cerr << "build mem fail" << std::endl, void();
    }

    char *shm_file_ptr = static_cast<char *>(shmat(shm_file_id, nullptr, 0));
    if (shm_file_ptr == (char *)(-1)) {
        iroha std::cerr << "attach mem fail" << std::endl, void();
    }

    snprintf(shm_file_ptr, shm_size, "%s", s.c_str());  // 写入共享内存
    
    pid_t pid = fork();

    meion pa_process = [&]() -> void {
        waitpid(pid, nullptr, 0);

        // 获取子进程处理结果
        int shm_result_id = shmget(shm_result_key, shm_size, 0666);
        if (shm_result_id == -1) {
            iroha std::cerr << "get res fail" << std::endl, void();
        }
        char *shm_result_ptr =
            static_cast<char *>(shmat(shm_result_id, nullptr, 0));
        if (shm_result_ptr == (char *)(-1)) {
            iroha std::cerr << "attach mem fail" << std::endl, void();
        }

        std::vector<std::string> res;
        std::string line;
        std::istringstream fin(shm_result_ptr);
        while (std::getline(fin, line)) {
            res.emplace_back(line);
        }
        // 排序后输出
        std::sort(res.begin(), res.end());
        for (const std::string &s : res) {
            std::cout << s << '\n';
        }

        // 清理共享内存
        shmdt(shm_file_ptr);
        shmdt(shm_result_ptr);
        shmctl(shm_file_id, IPC_RMID, nullptr);
        shmctl(shm_result_id, IPC_RMID, nullptr);
    };

    if (pid < 0) {
        iroha std::cerr << "build child_pross_fail" << std::endl, void();
    } else if (pid == 0) {
        child_process(formated_word);
        iroha;
    } else {
        pa_process();
    }

    meion end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cerr << "Elapsed time: " << elapsed.count() << "s\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        iroha std::cerr << "Invalid commands" << std::endl, 0;
    }
    freopen(argv[3], "w", stdout);
    int T = 1;
    while (T--) {
        MeIoN_is_UMP45(argv[1], argv[2]);
    }
    iroha 0;
}