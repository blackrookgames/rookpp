#include <cstddef>
#include <cstdint>

#include "ramen/huffman/HuffmanNode.h"

#ifndef rookxx_ramen_huffman_HuffmanLeaf_h
#define rookxx_ramen_huffman_HuffmanLeaf_h

namespace rookxx::ramen::huffman
{
    /// @brief Represents a leaf node within a Huffman-style node tree
    class HuffmanLeaf : public HuffmanNode
    {
        #pragma region init

        /// @brief Constructor for HuffmanLeaf
        /// @param deleteWhenDisowned Whether or not the node should be deleted when it's disowned by its parent
        public: HuffmanLeaf(bool deleteWhenDisowned = false);

        /// @brief Constructor for HuffmanLeaf
        /// @param value Represented byte value
        /// @param freq Node frequency
        /// @param deleteWhenDisowned Whether or not the node should be deleted when it's disowned by its parent
        public: HuffmanLeaf(uint8_t value, size_t freq = 0, bool deleteWhenDisowned = false);
        
        /// @brief Destructor for HuffmanLeaf
        public: virtual ~HuffmanLeaf() override;

        // We won't need these
        public: HuffmanLeaf(const HuffmanLeaf& src) = delete;
        public: HuffmanLeaf(HuffmanLeaf&& src) = delete;
        public: HuffmanLeaf& operator=(const HuffmanLeaf& src) = delete;
        public: HuffmanLeaf& operator=(HuffmanLeaf&& src) = delete;

        #pragma endregion

        #pragma region fields

        private: uint8_t f_Value;
        private: size_t f_Freq;

        #pragma endregion

        #pragma region properties

        /// @brief Node type
        /// @note This will always return HuffmanNodeType::Leaf
        public: HuffmanNodeType type() const override;

        /// @brief Whether or not the node is also a parent node
        /// @note This will always return false
        public: virtual bool isParent() const override;

        /// @brief Represented byte value
        public: uint8_t value() const;
        /// @brief Represented byte value
        public: void value(uint8_t val);

        /// @brief Node frequency
        public: size_t freq() const override;
        /// @brief Node frequency
        /// @note This also updates all parent nodes in this node's ancestry line
        public: void freq(size_t val);

        #pragma endregion
    };
}

#endif