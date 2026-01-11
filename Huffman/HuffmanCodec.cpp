#include "HuffmanCodec.h"
#include <climits>
#include <algorithm>
#include <cstring>
#include <iostream>

namespace HuffmanModule {

    HuffmanCodec::HuffmanCodec() {}

    HuffmanCodec::~HuffmanCodec() {}

    // 核心函数
    void HuffmanCodec::build(const std::string& text) {
        // 1. 频率统计：扫描文本字符出现次数
        freqMap.clear();
        for (char c : text) {
            freqMap[c]++;
        }

        if (freqMap.empty()) return;

        // 2. 数据初始化：2n-1个节点，使用1-based索引
        int n = freqMap.size();
        HT.assign(2 * n, HuffmanNode());

        // 填充叶子节点（索引 1 至 n）
        int i = 1;
        for (auto const& [key, val] : freqMap) {
            HT[i].data = key;
            HT[i].weight = val;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            i++;
        }

        // 3. 构造哈夫曼树并生成编码
        huffmanCoding(n);
    }

    // 辅助函数：从HT[1...end]中选择parent为0且权重最小的两个节点
    void HuffmanCodec::select(int end, int& s1, int& s2) {
        unsigned int min1 = UINT_MAX;
        unsigned int min2 = UINT_MAX;
        s1 = 0;
        s2 = 0;

        // 寻找第一极小值
        for (int i = 1; i <= end; i++) {
            if (HT[i].parent == 0) {
                if (HT[i].weight < min1) {
                    min1 = HT[i].weight;
                    s1 = i;
                }
            }
        }

        // 寻找第二极小值
        for (int i = 1; i <= end; i++) {
            if (HT[i].parent == 0 && i != s1) {
                if (HT[i].weight < min2) {
                    min2 = HT[i].weight;
                    s2 = i;
                }
            }
        }
    }

    // 参考教材算法实现：构树与编码生成
    void HuffmanCodec::huffmanCoding(int n) {
        if (n <= 1) return;

        int m = 2 * n - 1;

        // 初始化非叶子节点（n+1 至 m）
        for (int i = n + 1; i <= m; ++i) {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].data = '\0';
        }

        // 构树逻辑：合并节点
        for (int i = n + 1; i <= m; ++i) {
            int s1, s2;
            select(i - 1, s1, s2);
            HT[s1].parent = i;
            HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
        }

        // 生成编码表：从叶子逆向回溯至根
        HC.clear();
        for (int i = 1; i <= n; ++i) {
            unsigned int c = i;
            unsigned int f = HT[i].parent;
            std::string codeStr = "";

            while (f != 0) {
                if (HT[f].lchild == c) {
                    codeStr += '0'; // 左分支编码0
                } else {
                    codeStr += '1'; // 右分支编码1
                }
                c = f;
                f = HT[f].parent;
            }

            // 逆向回溯的结果需要翻转
            std::reverse(codeStr.begin(), codeStr.end());
            HC[HT[i].data] = codeStr;
        }
    }

    // 外部接口：获取指定字符编码
    std::string HuffmanCodec::getCode(char c) const {
        auto it = HC.find(c);
        return (it != HC.end()) ? it->second : "";
    }

    // 外部接口：获取树、编码表、频率表（用于可视化渲染）
    const std::vector<HuffmanNode>& HuffmanCodec::getTree() const { return HT; }
    const std::map<char, std::string>& HuffmanCodec::getCodeMap() const { return HC; }
    const std::map<char, int>& HuffmanCodec::getFrequencyMap() const { return freqMap; }

} // namespace HuffmanModule