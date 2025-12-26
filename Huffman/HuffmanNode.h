#pragma once

/**
 * @file HuffmanNode.h
 * @brief Definition of the Huffman Tree Node structure.
 */

/**
 * @struct HuffmanNode
 * @brief Represents a node in the Huffman Tree.
 * 
 * Complies with the textbook definition:
 * - weight: Weight of the node (frequency).
 * - parent: Index of the parent node (0 if root/unused).
 * - lchild: Index of the left child (0 if none).
 * - rchild: Index of the right child (0 if none).
 * - data: Character data (for leaf nodes).
 */
struct HuffmanNode {
    unsigned int weight; ///< Weight of the node
    unsigned int parent; ///< Parent node index
    unsigned int lchild; ///< Left child node index
    unsigned int rchild; ///< Right child node index
    char data;           ///< Character data (useful for leaf nodes)

    /**
     * @brief Default constructor initializing all fields to 0/null.
     */
    HuffmanNode() : weight(0), parent(0), lchild(0), rchild(0), data('\0') {}
};
