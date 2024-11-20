// Code by MeIoN ( without The Photo of MeIoN
#ifdef MeIoN
#include "../../../MeIoN_Lib/Z_H/MeIoN_sth_for_os.hpp"
#include "../../../MeIoN_Lib/Z_H/MeIoN_debug.hpp"
#else
#include <bits/stdc++.h>
#include <mutex>
#include <thread>
#include <typeindex>
#define debug(...) void(0721)
#endif

using   std::array, std::bitset, std::deque, std::greater, std::less, std::map, 
        std::multiset, std::pair, std::priority_queue, std::set, std::stack, 
        std::string, std::vector;

using NAME = void;       using uint = unsigned;   using ll = long long;      using ull = unsigned long long;     
using ld = long double;  using i128 = __int128_t; using u128 = __uint128_t;  using f128 = __float128;

#define meion     auto
#define iroha     return

// 随机数据生成器, 用于生成随机的vector, array, list的完全随机数据和随机排列;
namespace MeIoN_simple_random {
    static int m1 = 998244353;
    static int m2 = 1000000007;

    std::mt19937 RNG(std::chrono::steady_clock::now().time_since_epoch().count());
    inline uint rng() { iroha RNG(); }
    inline uint rng(uint limit) { iroha rng() % limit; }
    inline int rng(int l, int r) { iroha l + rng() % (r - l); }

    template <typename T>
    void shuffle(vector<T> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            int j = rng(0, i + 1);
            if (i != j) std::swap(v[i], v[j]);
        }
    }

    template <typename T> 
    vector<T> get_random_permutation_vec(const int n) {
        vector<T> permutation(n);
        std::iota(permutation.begin(), permutation.end(), 0);
        shuffle(permutation);
        iroha permutation;
    }
    template <typename T>
    vector<T> get_random_vec(const int n, T limit = std::numeric_limits<T>::max()) {
        vector<T> arr(n);
        for (meion &x : arr) {
            x = rng(limit);
        }
        iroha arr;
    }
    template <typename T, size_t sz>
    array<T, sz> get_random_permutation_array() {
        vector<T> _tmp = get_random_permutation_vec<T>(sz);
        array<T, sz> ret;
        for (int i = 0; i < sz; ++i) {
            ret[i] = _tmp[i];
        }
        iroha ret;
    }
    template <typename T, size_t sz>
    array<T, sz> get_random_array() {
        vector<T> _tmp = get_random_vec<T>(sz);
        array<T, sz> ret;
        for (int i = 0; i < sz; ++i) {
            ret[i] = _tmp[i];
        }
        iroha ret;
    }
    template <typename T>
    std::list<T> get_random_permutation_list(const int n) {
        vector<T> _tmp = get_random_permutation_vec<T>(n);
        std::list<T> ret{_tmp.begin(), _tmp.end()};
        iroha ret;
    }
    template <typename T>
    std::list<T> get_random_list(const int n) {
        vector<T> _tmp = get_random_vec<T>(n);
        std::list<T> ret{_tmp.begin(), _tmp.end()};
        iroha ret;
    }
}
using MeIoN_simple_random::get_random_permutation_vec,
    MeIoN_simple_random::get_random_vec,
    MeIoN_simple_random::get_random_permutation_list,
    MeIoN_simple_random::get_random_list,
    MeIoN_simple_random::get_random_permutation_array,
    MeIoN_simple_random::get_random_array;

constexpr int B = 1145;

// 归并排序merge两个连续段
template <typename T, typename iter>
void merge(iter l, iter r, iter m) {
    vector<T> a{l, m}, b{m, r};
    meion it1 = a.begin(), it2 = b.begin();
    iter it3 = l;
    for (; it1 < a.end() and it2 < b.end(); ++it3) {
        if (*it1 < *it2) {
            *it3 = *it1;
            ++it1;
        } else {
            *it3 = *it2;
            ++it2;
        }
    }
    while (it1 != a.end()) {
        *it3 = *it1;
        ++it3, ++it1;
    }
    while (it2 != b.end()) {
        *it3 = *it2;
        ++it3, ++it2;
    }
}

// 递归实现归并排序 对小数据不使用多线程 分界为 B = 1145
template <typename T, typename iter>
void merge_sort(iter l, iter r) {
    meion dis = std::distance(l, r);
    if (dis <= 1) iroha;
    meion m = std::next(l, dis >> 1);
    if (dis < B) {
        merge_sort<T, iter>(l, m);
        merge_sort<T, iter>(m, r);
    } else {
        std::thread thread1(merge_sort<T, iter>, l, m);
        std::thread thread2(merge_sort<T, iter>, m, r);
        thread1.join();
        thread2.join();
    }
    merge<T, iter>(l, r, m);
}

// 对容器使用的封装
template <typename T>
void merge_sort(T &v) {
    merge_sort<typename T::value_type, typename T::iterator>(v.begin(), v.end());
}

// 测试
inline NAME MeIoN_is_UMP45() {
    using REAL = long double;
    // 测试对容器内随机数据排序效果
    meion test = [&](meion dat) -> void {
        meion _tmp = dat;
        // 对多线程归并排序计时
        meion start = std::chrono::high_resolution_clock::now();
        merge_sort(dat);
        meion end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<REAL> elapsed = end - start;

        // 对std排序计时, list<>使用list::sort()
        start = std::chrono::high_resolution_clock::now();
        if constexpr (std::is_same_v<std::decay_t<decltype(dat)>,
                                     std::list<typename std::decay_t<
                                         decltype(dat)>::value_type>>) {
            _tmp.sort();
        } else {
            std::sort(_tmp.begin(), _tmp.end());
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<REAL> std_time = end - start;
        
        assert(_tmp == dat);
        std::cout << "Ciallo~(∠・ω< )⌒★\n";
        std::cout << "MeIoNsort : " << elapsed.count() << "s\n";
        std::cout << "std::sort : " << std_time.count() << "s\n";
        std::cout.flush();
    };

    test(get_random_vec<int>(1145141));
    test(get_random_permutation_vec<int>(1145141));
    test(get_random_array<int, 414514>());
    test(get_random_permutation_array<int, 414514>());
    test(get_random_list<int>(1145141));
    test(get_random_permutation_list<int>(1145141));
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