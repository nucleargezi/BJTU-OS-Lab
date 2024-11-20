// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include "../../../MeIoN_Lib/Z_H/MeIoN_sth_for_os.hpp"
#include "../../../MeIoN_Lib/Z_H/MeIoN_debug.hpp"
#else
#include <bits/stdc++.h>
#include <mutex>
#include <thread>
#include <type_traits>
#define debug(...) void(0721)
#endif

using   std::array, std::bitset, std::deque, std::greater, std::less, std::map, 
        std::multiset, std::pair, std::priority_queue, std::set, std::stack, 
        std::string, std::vector;

using NAME = void;       using uint = unsigned;   using ll = long long;      using ull = unsigned long long;     
using ld = long double;  using i128 = __int128_t; using u128 = __uint128_t;  using f128 = __float128;

#define meion     auto
#define iroha     return

// 继承了一个 9 x 9 的矩阵放置信息
class sudoku_solution_validator : private array<array<int, 9>, 9> {
    using msf = sudoku_solution_validator;
    using mp = array<array<int, 9>, 9>;

    static constexpr int msk = (1 << 9) - 1;
    std::mutex my_lock;
    int ok;

    void build() { fill({}); }
    void build(const mp &v) {
        for (int i = 0; i < 9; ++i) {
            at(i) = v[i];
        }
    }

    // 修改, 防止多线程冲突
    void update() {
        std::lock_guard<std::mutex> lock(my_lock);
        ok = 0;
    }
    // 检测行是否合法
    void check_H(int p) {
        if (not ok) iroha;
        int _msk = 0;
        for (int i = 0; i < 9; ++i) {
            _msk ^= 1 << at(p)[i] - 1;
        }
        if (_msk != msk) {
            update();
        }
    }
    // 检测列是否合法
    void check_W(int p) {
        if (not ok) iroha;
        int _msk = 0;
        for (int i = 0; i < 9; ++i) {
            _msk ^= 1 << at(i)[p] - 1;
        }
        if (_msk != msk) {
            update();
        }
    }
    // 检测每个九宫格是否合法
    void check_P(int x, int y) {
        if (not ok) iroha;
        int _msk = 0;
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                _msk ^= 1 << at(i + x)[k + y] - 1;
            }
        }
        if (_msk != msk) {
            update();
        }
    }

   public:
    sudoku_solution_validator() { build(); }
    sudoku_solution_validator(const mp &v) { build(v); }

    void set_sudoku(const mp &v) { build(v); }
    // 检查
    bool validator() {
        ok = 1;
        vector<std::thread> threads;
        for (int i = 0; i < 9; ++i) {
            threads.emplace_back(&msf::check_H, this, i);
            threads.emplace_back(&msf::check_W, this, i);
        }
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                threads.emplace_back(&msf::check_P, this, i * 3, k * 3);
            }
        }
        for (meion &thread : threads) {
            thread.join();
        }
        iroha not not ok;
    }
    
    void DEBUG() {
        for (int i = 0; i < 9; ++i) {
            debug(at(i));
        }
    }
};

const array<array<int, 9>, 9> test_ok {{ // 合法
    {5, 4, 2, 8, 3, 7, 1, 6, 9},
    {9, 6, 7, 1, 5, 2, 4, 8, 3},
    {1, 8, 3, 6, 9, 4, 2, 5, 7},
    {4, 3, 6, 2, 7, 8, 5, 9, 1},
    {7, 1, 9, 5, 6, 3, 8, 2, 4},
    {2, 5, 8, 4, 1, 9, 3, 7, 6},
    {3, 2, 4, 9, 8, 6, 7, 1, 5},
    {6, 7, 5, 3, 2, 1, 9, 4, 8},
    {8, 9, 1, 7, 4, 5, 6, 3, 2}
}};
const array<array<int, 9>, 9> test_fail_H {{ // 行中重复
    {9, 5, 4, 6, 8, 3, 1, 2, 7},
    {6, 8, 7, 2, 1, 9, 5, 4, 3},
    {2, 1, 3, 5, 4, 7, 9, 6, 8},
    {3, 9, 1, 8, 6, 2, 4, 7, 5},
    {4, 7, 6, 3, 9, 5, 8, 1, 2},
    {8, 2, 5, 1, 7, 4, 3, 9, 6},
    {1, 6, 2, 9, 5, 8, 7, 3, 4},
    {7, 3, 8, 4, 2, 1, 6, 5, 9},
    {5, 4, 9, 7, 3, 6, 2, 8, 8},
}};
const array<array<int, 9>, 9> test_fail_W {{ // 列中重复
    {1, 5, 3, 9, 4, 2, 6, 7, 8},
    {9, 4, 8, 7, 6, 5, 1, 3, 2},
    {7, 6, 2, 1, 3, 8, 5, 9, 4},
    {2, 5, 6, 4, 9, 7, 3, 8, 1},
    {3, 8, 9, 2, 5, 1, 4, 6, 7},
    {4, 7, 1, 6, 8, 3, 2, 5, 9},
    {6, 9, 7, 5, 1, 4, 8, 2, 3},
    {8, 2, 4, 3, 7, 6, 9, 1, 5},
    {1, 3, 5, 8, 2, 9, 7, 4, 6},
}};
const array<array<int, 9>, 9> test_fail_P {{ // 块中重复
    {3, 8, 7, 5, 6, 1, 9, 4, 2},
    {5, 6, 2, 4, 3, 9, 8, 7, 1},
    {4, 3, 1, 8, 7, 2, 9, 5, 6},
    {1, 9, 3, 6, 5, 4, 7, 2, 8},
    {7, 2, 5, 1, 9, 8, 6, 3, 4},
    {6, 4, 8, 3, 2, 7, 1, 9, 5},
    {9, 5, 4, 9, 8, 6, 2, 1, 7},
    {2, 1, 6, 7, 4, 3, 5, 8, 9},
    {8, 7, 9, 2, 1, 5, 4, 6, 3},
}};

inline NAME MeIoN_is_UMP45() {
    for (const meion test :
         {test_ok, test_fail_H, test_fail_P, test_fail_W}) {  // 1 0 0 0
        if (sudoku_solution_validator(test).validator()) {
            std::cout << "Ciallo ~ " << std::endl;
        } else {
            std::cout << "Fail" << std::endl;
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T = 1;
    // std::cin >> T;
    while (T--) {
        MeIoN_is_UMP45();
    }
    iroha 0;
}