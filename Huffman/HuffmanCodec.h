#pragma once

#include "HuffmanNode.h"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

/**
 * @file HuffmanCodec.h
 * @brief 哈夫曼编解码核心接口
 */

namespace HuffmanModule {

    /**
     * @class HuffmanCodec
     * @brief 哈夫曼树构建与编码生成类
     */
    class HuffmanCodec {
    public:
        HuffmanCodec();
        ~HuffmanCodec();

        /**
         * @brief 构建哈夫曼树并生成编码表
         * @param text 输入的待分析西文文本
         */
        void build(const std::string& text);

        /**
         * @brief 获取指定字符的哈夫曼编码
         * @param c 目标字符
         * @return 二进制编码字符串 (如 "101")
         */
        std::string getCode(char c) const;

        /**
         * @brief 获取哈夫曼树（数组形式存储）
         */
        const std::vector<HuffmanNode>& getTree() const;

        /**
         * @brief 获取字符编码映射表
         */
        const std::map<char, std::string>& getCodeMap() const;

        /**
         * @brief 获取字符频率映射表
         */
        const std::map<char, int>& getFrequencyMap() const;

    private:
        std::vector<HuffmanNode> HT;        ///< 哈夫曼树存储数组
        std::map<char, std::string> HC;     ///< 哈夫曼编码映射表
        std::map<char, int> freqMap;        ///< 字符频率统计表

        /**
         * @brief 选取权值最小的两个节点 (Select 算法)
         * @param end 当前搜索边界下标
         * @param s1 最小节点下标输出
         * @param s2 次小节点下标输出
         */
        void select(int end, int& s1, int& s2);

        /**
         * @brief 核心哈夫曼编码算法（参考课本算法 6.12）
         * @param n 叶子节点数量
         */
        void huffmanCoding(int n);
    };

} // namespace HuffmanModule