#include "BitStream.h"

namespace BitStreamModule {

    BitStream::BitStream() : bitCount(0) {}

    BitStream::~BitStream() {}

    void BitStream::writeBit(int bit) {
        size_t byteIndex = bitCount / 8;
        size_t bitOffset = 7 - (bitCount % 8); // Fill from MSB to LSB

        if (byteIndex >= buffer.size()) {
            buffer.push_back(0); // Add new byte if needed
        }

        if (bit) {
            buffer[byteIndex] |= (1 << bitOffset);
        } else {
            buffer[byteIndex] &= ~(1 << bitOffset);
        }

        bitCount++;
    }

    void BitStream::writeBits(const std::string& bitString) {
        for (char c : bitString) {
            if (c == '0') {
                writeBit(0);
            } else if (c == '1') {
                writeBit(1);
            } else {
                throw std::invalid_argument("Bit string must contain only '0' or '1'.");
            }
        }
    }

    const std::vector<uint8_t>& BitStream::getBuffer() const {
        return buffer;
    }

    size_t BitStream::getTotalBits() const {
        return bitCount;
    }

    void BitStream::clear() {
        buffer.clear();
        bitCount = 0;
    }

} // namespace BitStreamModule
