#include <iostream>
#include <string>
#include <iomanip>
#include "Huffman/HuffmanCodec.h"
#include "BitStream/BitStream.h"

using namespace std;
using namespace HuffmanModule;
using namespace BitStreamModule;

void printFrequencyTable(const map<char, int>& freqMap) {
    cout << "\n=== Frequency Table ===\n";
    cout << "Char\tFreq\n";
    for (const auto& pair : freqMap) {
        char c = pair.first;
        int f = pair.second;
        if (c >= 32 && c <= 126) {
            cout << "'" << c << "'\t" << f << endl;
        } else {
            cout << "0x" << hex << uppercase << (int)(unsigned char)c << dec << "\t" << f << endl;
        }
    }
}

void printHuffmanTree(const vector<HuffmanNode>& HT) {
    cout << "\n=== Huffman Tree (Array) ===\n";
    cout << "Idx\tData\tWeight\tParent\tLChild\tRChild\n";
    for (size_t i = 1; i < HT.size(); ++i) {
        if (HT[i].weight == 0 && HT[i].parent == 0 && HT[i].lchild == 0 && HT[i].rchild == 0) continue; // Skip unused
        
        string dataDisplay = "N/A";
        if (HT[i].lchild == 0 && HT[i].rchild == 0) { // Leaf node
            if (HT[i].data >= 32 && HT[i].data <= 126) {
                dataDisplay = string("'") + HT[i].data + "'";
            } else {
                char buf[10];
                sprintf(buf, "0x%02X", (unsigned char)HT[i].data);
                dataDisplay = string(buf);
            }
        }

        cout << i << "\t" 
             << dataDisplay << "\t" 
             << HT[i].weight << "\t" 
             << HT[i].parent << "\t" 
             << HT[i].lchild << "\t" 
             << HT[i].rchild << endl;
    }
}

void printHuffmanCodes(const map<char, string>& HC) {
    cout << "\n=== Huffman Codes ===\n";
    for (const auto& pair : HC) {
        char c = pair.first;
        if (c >= 32 && c <= 126) {
            cout << "'" << c << "': " << pair.second << endl;
        } else {
            cout << "0x" << hex << uppercase << (int)(unsigned char)c << dec << ": " << pair.second << endl;
        }
    }
}

int main() {
    // 1. Input
    string inputBuffer;
    cout << "Please enter a text (ASCII):" << endl;
    getline(cin, inputBuffer);

    if (inputBuffer.empty()) {
        cout << "Empty input." << endl;
        return 0;
    }

    try {
        // 2. Huffman Coding Process
        HuffmanCodec codec;
        codec.build(inputBuffer);

        // 3. Display Statistics and Tree
        printFrequencyTable(codec.getFrequencyMap());
        printHuffmanTree(codec.getTree());
        printHuffmanCodes(codec.getCodeMap());

        // 4. Bitwise Compression
        cout << "\n=== Compression Result ===\n";
        cout << "Original String: \"" << inputBuffer << "\"" << endl;

        BitStream bitStream;
        cout << "Bit Stream: ";
        
        for (char c : inputBuffer) {
            string code = codec.getCode(c);
            cout << code; // Print as we go
            bitStream.writeBits(code);
        }
        cout << endl;

        // 5. Output Hex Dump
        const vector<uint8_t>& buffer = bitStream.getBuffer();
        size_t totalBits = bitStream.getTotalBits();
        size_t totalBytes = buffer.size();

        cout << "Total Bits: " << totalBits << endl;
        cout << "Total Bytes: " << totalBytes << endl;
        cout << "Hex Dump: ";
        for (uint8_t byte : buffer) {
            cout << hex << uppercase << setw(2) << setfill('0') << (int)byte << " ";
        }
        cout << dec << endl;

        // 6. Compression Ratio
        float originalSize = inputBuffer.length() * 8.0f;
        float compressedSize = (float)totalBits;
        float ratio = (1.0f - compressedSize / originalSize) * 100.0f;
        cout << fixed << setprecision(2) << "Compression Ratio: " << ratio << "%" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
