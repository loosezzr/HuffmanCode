#pragma once

/**
 * @struct HuffmanNode
 * @brief 哈夫曼树节点结构体
 * * 课本定义：使用静态三叉链表存储结构
 */
struct HuffmanNode {
    unsigned int weight; ///< 权值（字符出现频率）
    unsigned int parent; ///< 父节点下标
    unsigned int lchild; ///< 左孩子下标
    unsigned int rchild; ///< 右孩子下标
    char data;           ///< 节点数据（仅叶子节点有效）

    /**
     * @brief 默认构造函数，初始化为零或空
     */
    HuffmanNode() : weight(0), parent(0), lchild(0), rchild(0), data('\0') {}
};