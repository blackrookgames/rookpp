#include <cstddef>
#include <cstdint>

#include "ramen/huffman/HuffmanTree.h"

#ifndef rookxx_ramen_huffman_HuffmanUtility_h
#define rookxx_ramen_huffman_HuffmanUtility_h

namespace rookxx::ramen::huffman
{
    /// @brief Utility for Huffman operations
    class HuffmanUtility : public Serializable
    {
        #pragma region encode/decode 0

        /// @brief Attempts to encode data
        /// @param idata Input data
        /// @param isize Size of input data
        /// @param tree Huffman tree to use for encoding
        /// @param odata Encoded data
        /// @param osize Size of encoded data
        /// @return Whether or not successful
        /// @note If unsuccessful, odata will be set to nullptr
        /// @note If unsuccessful, osize will be set to 0
        public: static bool encode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize);

        /// @brief Attempts to decode data
        /// @param idata Input data
        /// @param isize Size of input data
        /// @param tree Huffman tree to use for decoding
        /// @param odata Decoded data
        /// @param osize Size of decoded data
        /// @return Whether or not successful
        /// @note If unsuccessful, odata will be set to nullptr
        /// @note If unsuccessful, osize will be set to 0
        public: static bool decode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize);

        #pragma endregion
        
        #pragma region encode/decode 1

        /// @brief Attempts to encode data
        /// @param idata Input data
        /// @param isize Size of input data
        /// @param odata Encoded data, including the Huffman tree used to encode data
        /// @param osize Size of encoded data
        /// @return Whether or not successful
        /// @note If unsuccessful, odata will be set to nullptr
        /// @note If unsuccessful, osize will be set to 0
        public: static bool encode(const uint8_t* idata, size_t isize, uint8_t*& odata, size_t& osize);

        /// @brief Attempts to decode data 
        /// @param idata Input data, including the Huffman tree to used to decode data
        /// @param isize Size of input data
        /// @param odata Decoded data
        /// @param osize Size of decoded data
        /// @return Whether or not successful
        /// @note If unsuccessful, odata will be set to nullptr
        /// @note If unsuccessful, osize will be set to 0
        public: static bool decode(const uint8_t* idata, size_t isize, uint8_t*& odata, size_t& osize);

        #pragma endregion

        #pragma region tree

        /// @brief Uses uncompressed byte data to populate a Huffman tree
        /// @param tree Huffman tree to populate
        /// @param idata Uncompressed byte data
        /// @param isize Size of uncompressed byte data
        /// @note Any existing branches and leafs will be removed from the tree
        public: static void populateTree(HuffmanTree& tree, const uint8_t* idata, size_t isize);

        #pragma endregion
    };
}

#endif