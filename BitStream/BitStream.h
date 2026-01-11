#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>

/**
 * @file BitStream.h
 * @brief Interface for bit-level I/O operations.
 */

namespace BitStreamModule {

    /**
     * @class BitStream
     * @brief Manages a buffer for writing and reading bits.
     */
    class BitStream {
    public:
        BitStream();
        ~BitStream();

        /**
         * @brief Writes a single bit to the stream.
         * @param bit The bit to write (0 or 1).
         */
        void writeBit(int bit);

        /**
         * @brief Writes a string of '0's and '1's to the stream.
         * @param bitString The string representing bits.
         */
        void writeBits(const std::string& bitString);

        /**
         * @brief Gets the internal buffer.
         * @return Pointer to the buffer data.
         */
        const std::vector<uint8_t>& getBuffer() const;

        /**
         * @brief Gets the total number of bits written.
         * @return Total bits.
         */
        size_t getTotalBits() const;

        /**
         * @brief Clears the stream.
         */
        void clear();

    private:
        std::vector<uint8_t> buffer; ///< Storage for bits
        size_t bitCount;             ///< Current number of bits written
    };

} // namespace BitStreamModule
