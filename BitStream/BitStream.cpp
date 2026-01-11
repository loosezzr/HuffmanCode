#include "BitStream.h"

namespace BitStreamModule {

    BitStream::BitStream() : bitCount(0) {}

    BitStream::~BitStream() {}

    //写入单个比特
    void BitStream::writeBit(int bit) {
        size_t byteIndex = bitCount / 8;       // 计算当前字节索引
        size_t bitOffset = 7 - (bitCount % 8); // 从高位(MSB)向低位(LSB)填充

        if (byteIndex >= buffer.size()) {
            buffer.push_back(0); // 空间不足时追加新字节
        }

        if (bit) {
            buffer[byteIndex] |= (1 << bitOffset);  // 置1
        } else {
            buffer[byteIndex] &= ~(1 << bitOffset); // 置0
        }

        bitCount++;
    }

    /**
     写入比特字符串（如 "1101"）
     bitString 仅包含 '0' 或 '1' 的字符串
     */
    void BitStream::writeBits(const std::string& bitString) {
        for (char c : bitString) {
            if (c == '0') {
                writeBit(0);
            } else if (c == '1') {
                writeBit(1);
            } else {
                throw std::invalid_argument("比特字符串必须只包含 '0' 或 '1'");
            }
        }
    }

    /**
     获取压缩后的二进制缓冲区
     */
    const std::vector<uint8_t>& BitStream::getBuffer() const {
        return buffer;
    }

    /**
     获取总比特数
     */
    size_t BitStream::getTotalBits() const {
        return bitCount;
    }

    /**
     重置缓冲区
     */
    void BitStream::clear() {
        buffer.clear();
        bitCount = 0;
    }

} // namespace BitStreamModule