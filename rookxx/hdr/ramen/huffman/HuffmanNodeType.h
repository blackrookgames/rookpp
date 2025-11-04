#ifndef rookxx_ramen_huffman_HuffmanNodeType_h
#define rookxx_ramen_huffman_HuffmanNodeType_h

namespace rookxx::ramen::huffman
{
    /// @brief Represents a type indentifier for Huffman-style tree nodes
    enum struct HuffmanNodeType
    {
        /// @brief Root node
        Root,
        /// @brief Branch node
        Branch,
        /// @brief Leaf node
        Leaf,
    };
}

#endif