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

using std::string, std::vector, std::bitset, std::array, std::set, std::map, std::pair;

struct my_page_table {
    int frame_id;  // 帧 ID
    bool ok;       // 是否有效
    my_page_table(int a = 0, bool b = false) : frame_id(a), ok(b) {}
};
struct my_tlb {
    int page_id;   // 页面 ID
    int frame_id;  // 帧 ID
    my_tlb(int a = -1, int b = -1) : page_id(a), frame_id(b) {}
};

constexpr int page_sz = 256;        // 每个页面的大小为 256 字节
constexpr int frame_sz = 256;       // 每个帧的大小为 256 字节
constexpr int num_frames = 256;     // 总帧数为 256
constexpr int page_table_sz = 256;  // 页表大小为 256
constexpr int tlb_sz = 16;          // TLB 大小为 16
constexpr int mem_sz = 65536;       // 物理内存总大小为 65536 字节

class guidingstar {
   public:
    guidingstar(const string &a, std::ifstream &b)
        : page_table(page_sz),
          tlb(tlb_sz),
          phy_mem(mem_sz),
          tlb_id(0),
          tot(0),
          page_fail(0),
          tlb_hit(0), 
          pla(0) {
        build(a);        // 初始化文件
        sol_address(b);  // 处理地址
        count();         // 统计信息
    }
    // 打开并构建文件
    void build(const string &filename) {
        mygo.open(filename, std::ios::in | std::ios::binary);
        if (not mygo.is_open()) {
            std::cerr << "open file fail" << std::endl;
            exit(1);
        }
    }
    // 将逻辑地址拆分为页面 ID 和偏移量
    meion get(int address) -> pair<int, int> {
        iroha {address >> 8 & 255, address & 255};
    };
    // 更新 TLB 表
    meion upd_tlb(int page_id, int frame_id) -> void {
        tlb[tlb_id] = {page_id, frame_id};
        (tlb_id += 1) %= tlb_sz;
    };
    // 处理页面失败
    meion cov_fail(int page_id) -> int {
        ++page_fail;
        mygo.seekg(page_id * page_sz, std::ios::beg);
        mygo.read(reinterpret_cast<char*>(&phy_mem[pla * page_sz]),
                  page_sz);
        page_table[page_id] = {pla, true};
        iroha pla++;
    };
    // 将逻辑地址转换为物理地址
    meion address_to(int logical_address) -> int {
        ++tot;
        meion [page_id, off] = get(logical_address);
        // 检查 TLB 是否命中
        for (int i = 0; i < tlb_sz; ++i) {
            if (tlb[i].page_id == page_id) {
                ++tlb_hit;
                iroha tlb[i].frame_id * page_sz + off;
            }
        }
        // 如果页表中有记录，则直接使用
        if (page_table[page_id].ok) {
            upd_tlb(page_id, page_table[page_id].frame_id);
            iroha page_table[page_id].frame_id * page_sz + off;
        }
        // 如果没有记录，则发生页面失败
        int frame_id = cov_fail(page_id);
        upd_tlb(page_id, frame_id);
        iroha frame_id * page_sz + off;
    }
    // 处理输入文件中的地址，并打印对应的物理地址和值
    meion sol_address(std::ifstream &file) -> void {
        int address;
        while (file >> address) {
            int phy_address = address_to(address);
            int8_t val = phy_mem[phy_address];
            std::cout << "Virtual address: " << address
                      << " Physical address: " << phy_address
                      << " Value: " << int(val) << '\n';
        }
    }
    // 打印统计信息
    meion count() -> void {
        std::cerr << "Page fails: " << page_fail << '\n'
                  << "Tlb hits: " << tlb_hit << '\n'
                  << "Total references: " << tot << '\n'
                  << "Page fails rate: " << page_fail * 1.L / tot * 100 << "%\n"
                  << "Tlb hit rate: " << tlb_hit * 1.L / tot * 100 << "%\n";
    }

   private:
    vector<my_page_table> page_table;  // 页表
    vector<my_tlb> tlb;                // TLB
    vector<int8_t> phy_mem;            // 物理内存
    std::ifstream mygo;                // 文件输入流
    int tlb_id;                        // TLB 当前索引
    int page_fail;                     // 页面失败次数
    int tlb_hit;                       // TLB 命中次数
    int tot;                           // 总引用次数
    int pla;                           // 页框架计数
};

inline void MeIoN_is_UMP45(const string filename, const string bin) {
    std::ifstream file(filename);
    if (not file) {
        std::cerr << "open file fail\n";
        exit(1);
    }

    guidingstar QMX(bin, file);

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        iroha std::cerr << "Invalid commands, just filename" << std::endl, 0;
    }

    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(5);
    
    freopen(argv[3], "w", stdout);
    int T = 1;
    while (T--) {
        MeIoN_is_UMP45(argv[1], argv[2]);
    }
    iroha 0;
}