#pragma once

#include "HuffmanNode.h"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

/**
 * @file HuffmanCodec.h
 * @brief Public interface for Huffman Coding algorithm.
 */

namespace HuffmanModule {

    /**
     * @class HuffmanCodec
     * @brief Core class for Huffman Tree construction and Code generation.
     */
    class HuffmanCodec {
    public:
        HuffmanCodec();
        ~HuffmanCodec();

        /**
         * @brief Builds the Huffman Tree and generates codes based on input text.
         * @param text The input ASCII text to analyze.
         */
        void build(const std::string& text);

        /**
         * @brief Gets the generated Huffman Code for a specific character.
         * @param c The character to look up.
         * @return The binary string code (e.g., "101").
         */
        std::string getCode(char c) const;

        /**
         * @brief Gets the internal Huffman Tree (array representation).
         * @return Constant reference to the tree vector.
         */
        const std::vector<HuffmanNode>& getTree() const;

        /**
         * @brief Gets the map of characters to their Huffman Codes.
         * @return Map of char -> string code.
         */
        const std::map<char, std::string>& getCodeMap() const;

        /**
         * @brief Gets the frequency map of the input text.
         * @return Map of char -> frequency.
         */
        const std::map<char, int>& getFrequencyMap() const;

    private:
        std::vector<HuffmanNode> HT;        ///< Huffman Tree stored as array
        std::map<char, std::string> HC;     ///< Huffman Codes map
        std::map<char, int> freqMap;        ///< Frequency map

        /**
         * @brief Selects two nodes with smallest weights.
         * @param end The current search boundary index.
         * @param s1 Output index of the smallest node.
         * @param s2 Output index of the second smallest node.
         */
        void select(int end, int& s1, int& s2);

        /**
         * @brief Core Huffman Coding algorithm (Algorithm 6.12).
         * @param n Number of leaf nodes.
         */
        void huffmanCoding(int n);
    };

} // namespace HuffmanModule
