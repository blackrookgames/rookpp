#include <cstddef>
#include <cstdint>

#include "ramen/huffman/HuffmanNodeType.h"

#ifndef rookxx_ramen_huffman_HuffmanNode_h
#define rookxx_ramen_huffman_HuffmanNode_h

namespace rookxx::ramen::huffman
{
#ifndef rookxx_ramen_huffman_HuffmanParent_h
    class HuffmanParent;
#endif

    /// @brief Represents a node within a Huffman-style node tree
    class HuffmanNode
    {
        // TODO: Allow nodes to be deleted by tree to prevent memory leaks
        // When tree is loading new data
        // When tree is being deleted

        #pragma region init

        /// @brief Constructor for HuffmanNode
        public: HuffmanNode();
        
        /// @brief Destructor for HuffmanNode
        public: virtual ~HuffmanNode();

        // We won't need these
        public: HuffmanNode(const HuffmanNode& src) = delete;
        public: HuffmanNode(HuffmanNode&& src) = delete;
        public: HuffmanNode& operator=(const HuffmanNode& src) = delete;
        public: HuffmanNode& operator=(HuffmanNode&& src) = delete;

        #pragma endregion

        #pragma region friends

        friend HuffmanParent;

        #pragma endregion

        #pragma region fields

        // Also accessed and modified by HuffmanParent
        private: HuffmanParent* f_Parent;

        // Also accessed and modified by HuffmanParent
        private: bool f_Index;

        #pragma endregion

        #pragma region properties

        /// @brief Node type
        public: virtual HuffmanNodeType type() const = 0;

        /// @brief Whether or not the node is also a parent node
        public: virtual bool isParent() const = 0;

        /// @brief Node frequency
        public: virtual size_t freq() const = 0;

        /// @brief Parent node
        public: HuffmanParent* parent();
        /// @brief Parent node
        public: const HuffmanParent* parent() const;

        /// @brief Child "index" \
        /// @brief If false, the node is child node 0 of its parent \
        /// @brief If true, the node is child node 1 of its parent
        /// @note This value is meaningless if the node does not have a parent
        public: bool index() const;

        #pragma endregion
    };
}

#endif