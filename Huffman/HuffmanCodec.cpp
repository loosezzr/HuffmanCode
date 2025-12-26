#include "HuffmanCodec.h"
#include <climits>
#include <algorithm>
#include <cstring>
#include <iostream>

namespace HuffmanModule {

    HuffmanCodec::HuffmanCodec() {}

    HuffmanCodec::~HuffmanCodec() {}

    void HuffmanCodec::build(const std::string& text) {
        // 1. Frequency Statistics
        freqMap.clear();
        for (char c : text) {
            freqMap[c]++;
        }

        if (freqMap.empty()) return;

        // 2. Prepare Data
        int n = freqMap.size();
        
        // Resize HT to hold 2*n nodes (using 1-based indexing, so size is 2*n)
        // Wait, 2*n - 1 nodes total. 1-based index needs size 2*n.
        // Actually, let's use size 2*n to accommodate indices 1 to 2*n-1.
        HT.assign(2 * n, HuffmanNode()); 

        // Fill leaf nodes (1 to n)
        int i = 1;
        for (auto const& [key, val] : freqMap) {
            HT[i].data = key;
            HT[i].weight = val;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            i++;
        }

        // 3. Build Tree and Generate Codes
        huffmanCoding(n);
    }

    void HuffmanCodec::select(int end, int& s1, int& s2) {
        unsigned int min1 = UINT_MAX;
        unsigned int min2 = UINT_MAX;
        s1 = 0;
        s2 = 0;

        // First pass: find the smallest weight node
        for (int i = 1; i <= end; i++) {
            if (HT[i].parent == 0) {
                if (HT[i].weight < min1) {
                    min1 = HT[i].weight;
                    s1 = i;
                }
            }
        }

        // Second pass: find the second smallest weight node
        for (int i = 1; i <= end; i++) {
            if (HT[i].parent == 0 && i != s1) {
                if (HT[i].weight < min2) {
                    min2 = HT[i].weight;
                    s2 = i;
                }
            }
        }
    }

    void HuffmanCodec::huffmanCoding(int n) {
        if (n <= 1) return; // Need at least 2 nodes to build a tree
        
        int m = 2 * n - 1;

        // Initialize internal nodes
        for (int i = n + 1; i <= m; ++i) {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].data = '\0';
        }

        // Build the Huffman Tree
        for (int i = n + 1; i <= m; ++i) {
            int s1, s2;
            select(i - 1, s1, s2);
            HT[s1].parent = i;
            HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
        }

        // Generate Huffman Codes
        HC.clear();
        std::vector<char> cd(n); // Workspace
        
        // Traverse from leaf to root for each character
        // We iterate through the leaf nodes which are at indices 1 to n
        // Note: The map order might not match 1..n indices directly if we just iterate map.
        // But we filled HT[1..n] sequentially from the map iteration in build().
        // So we can iterate 1..n and look up HT[i].data to know which char it is.
        
        for (int i = 1; i <= n; ++i) {
            int start = n - 1;
            unsigned int c = i;
            unsigned int f = HT[i].parent;
            
            std::string codeStr = "";
            
            // Backtrack from leaf to root
            while (f != 0) {
                if (HT[f].lchild == c) {
                    codeStr += '0';
                } else {
                    codeStr += '1';
                }
                c = f;
                f = HT[f].parent;
            }
            
            // The code is constructed in reverse order (leaf to root)
            std::reverse(codeStr.begin(), codeStr.end());
            HC[HT[i].data] = codeStr;
        }
    }

    std::string HuffmanCodec::getCode(char c) const {
        auto it = HC.find(c);
        if (it != HC.end()) {
            return it->second;
        }
        return ""; // Or throw exception
    }

    const std::vector<HuffmanNode>& HuffmanCodec::getTree() const {
        return HT;
    }

    const std::map<char, std::string>& HuffmanCodec::getCodeMap() const {
        return HC;
    }

    const std::map<char, int>& HuffmanCodec::getFrequencyMap() const {
        return freqMap;
    }

} // namespace HuffmanModule
