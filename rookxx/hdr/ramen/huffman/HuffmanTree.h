#include <cstddef>
#include <cstdint>

#include "ramen/Serializable.h"

#ifndef rookxx_ramen_huffman_HuffmanTree_h
#define rookxx_ramen_huffman_HuffmanTree_h

namespace rookxx::ramen::huffman
{
    /// @brief Represents a serializable Huffman-style node tree
    class HuffmanTree : public Serializable
    {
        #pragma region init

        /// @brief Constructor for HuffmanTree
        public: HuffmanTree();

        /// @brief Destructor for HuffmanTree
        public: ~HuffmanTree();

        // We won't need these
        public: HuffmanTree(const HuffmanTree& src) = delete;
        public: HuffmanTree(HuffmanTree&& src) = delete;
        public: HuffmanTree& operator=(const HuffmanTree& src) = delete;
        public: HuffmanTree& operator=(HuffmanTree&& src) = delete;

        #pragma endregion

        #pragma region serialization

        /// @brief Attempts to serialize the Huffman-style node tree
        /// @param data Serialized byte data
        /// @param size Size of serialized byte data
        /// @return Whether or not successful
        /// @note If serialization fails, data will be set to nullptr
        /// @note If serialization fails, size will be set to zero
        public: virtual bool serialize(uint8_t*& data, size_t& size) const override;
        
        /// @brief Attempts to the Huffman-style node tree by deserializing byte data
        /// @param data Serialized byte data
        /// @param size Size of serialized byte data
        /// @return Whether or not successful
        public: virtual bool deserialize(const uint8_t* data, size_t size) override;

        #pragma endregion
    };
}

#endif