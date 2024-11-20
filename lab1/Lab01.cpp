// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include <MeIoN_H.hpp>
#include <MeIoN_debug.hpp>
#include <MeIoN_sth_for_os.hpp>
#else
#include <bits/stdc++.h>
#include <sys/wait.h>
#define debug(...) void(0721)
#endif

using   std::vector, std::array, std::pair, std::set, std::map, std::tuple, 
        std::bitset, std::unordered_map, std::multiset, std::priority_queue, 
        std::string, std::stack, std::less, std::greater;

constexpr int MAX_LINE = 80, Print_Count = 10;

inline void MeIoN_is_UMP45() {
    char *args[MAX_LINE / 2 + 1];
    static string MeIoN_Input;
    int MYGO = 1;
    vector<string> history;

    // simple flush
    auto flush = [] ()->void { std::cout.flush(); };

    // trans input to tokens
    auto get_token = [&] (const string &input)->vector<string> {
        static string token;
        std::istringstream _tmp(input);
        vector<string> tokens;

        while (std::getline(_tmp, token, ' ')) {
            tokens.emplace_back(token);
        }

        return tokens;
    };

    // too long ? 
    auto check_length = [&] (const string &input)->bool {
        if (input.length() > MAX_LINE) {
            std::cerr << "Input is too long\n";
            return false;
        }
        return true;
    };

    // show the history
    auto print_history = [&] ()->void {
        std::cout <<"Show History" << std::endl;
        for (int i = std::max(0, (int)history.size() - Print_Count); i < history.size(); ++i) {
            std::cout << i + 1 << ' ' << history[i] << std::endl;
        }
    };

    // get history command
    auto get_history = [&] (int id)->string {
        --id;
        if (id > -1 and id < history.size()) {
            return history[id];
        }
        std::cerr << "Get Command Fail\n";
        flush();
        return "";
    };

    while (MYGO == 1) {
        std::cout << "psh> ";
        flush();

        std::getline(std::cin, MeIoN_Input);

        // Special Command
        if (MeIoN_Input == "history") {
            print_history();
            continue;
        } else if (MeIoN_Input == "!!") {
            if (history.empty()) {
                std::cerr << "No Command\n";
                flush();
                continue;
            }
            MeIoN_Input = history.back();
        } else if (MeIoN_Input[0] == '!' and MeIoN_Input.length() > 1) {
            const int id = std::stoi(MeIoN_Input.substr(1));
            MeIoN_Input = get_history(id);
        }

        // INV Command
        if (MeIoN_Input.empty()) {
            continue;
        }
        if (not check_length(MeIoN_Input)) {
            continue;
        }
        vector tokens = get_token(MeIoN_Input);
        if (tokens.size() > MAX_LINE / 2) {
            std::cerr << "Too Many Tokens\n";
            flush();
            continue;
        }

        // Pre_work
        history.emplace_back(MeIoN_Input);
        bool flag = tokens.back() == "&";
        if (flag) tokens.pop_back();
        static int i;
        for (i = 0; string &token : tokens) {
            args[i] = token.data();
        ++i; }
        args[i] = nullptr;

        if (tokens[0] == "exit") {
            MYGO = 0;
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "Fork Fail\n";
            flush();
            return;
        } else if (pid == 0) {
            execvp(args[0], args);
            std::cerr << "Exec Fail\n";
            flush();
            return;
        } else {
            if (not flag) {
                waitpid(pid, nullptr, 0);
            } else {
                std::cout << "parallel, pid : " << pid << std::endl;
            }
        }
    }

}
// 日々を貪り尽くしてきた
int main() {
    std::cin.tie(0)->sync_with_stdio(false);
    int T = 1;
    while (T--) {
        MeIoN_is_UMP45();
    }
    return 0;
}