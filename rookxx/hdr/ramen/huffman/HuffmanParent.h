#include <cstddef>
#include <cstdint>

#include "ramen/huffman/HuffmanNode.h"

#ifndef rookxx_ramen_huffman_HuffmanParent_h
#define rookxx_ramen_huffman_HuffmanParent_h

namespace rookxx::ramen::huffman
{
#ifndef rookxx_ramen_huffman_HuffmanLeaf_h
    class HuffmanLeaf;
#endif

#ifndef rookxx_ramen_huffman_HuffmanTree_h
    class HuffmanTree;
#endif

    /// @brief Represents a parent node within a Huffman-style node tree
    class HuffmanParent : public HuffmanNode
    {
        #pragma region init

        /// @brief Constructor for HuffmanParent
        /// @param deleteWhenDisowned Whether or not the node should be deleted when it's disowned by its parent
        public: HuffmanParent(bool deleteWhenDisowned = false);

        /// @brief Constructor for HuffmanParent
        /// @param type Node type
        /// @param deleteWhenDisowned Whether or not the node should be deleted when it's disowned by its parent
        /// @note Also accessed HuffmanTree
        private: HuffmanParent(HuffmanNodeType type, bool deleteWhenDisowned = false);
        
        /// @brief Destructor for HuffmanParent
        public: virtual ~HuffmanParent();

        // We won't need these
        public: HuffmanParent(const HuffmanParent& src) = delete;
        private: HuffmanParent(HuffmanParent&& src) = delete;
        public: HuffmanParent& operator=(const HuffmanParent& src) = delete;
        public: HuffmanParent& operator=(HuffmanParent&& src) = delete;

        #pragma endregion

        #pragma region friends

        friend HuffmanLeaf;
        friend HuffmanTree;

        #pragma endregion

        #pragma region fields

        private: HuffmanNodeType f_Type;

        private: size_t f_Freq;
        private: HuffmanNode* f_Child0;
        private: HuffmanNode* f_Child1;

        #pragma endregion

        #pragma region properties

        /// @brief Node type
        public: HuffmanNodeType type() const override;

        /// @brief Whether or not the node is also a parent node
        /// @note This will always return true
        public: virtual bool isParent() const override;

        /// @brief Frequency
        public: size_t freq() const override;

        /// @brief Child node 0
        public: HuffmanNode* child0();
        /// @brief Child node 0
        public: const HuffmanNode* child0() const;

        /// @brief Child node 1
        public: HuffmanNode* child1();
        /// @brief Child node 1
        public: const HuffmanNode* child1() const;

        #pragma endregion

        #pragma region helper

        private: void m_Parent(HuffmanNode* node, bool index);
        
        private: void m_Unparent(HuffmanNode* node);

        private: bool m_SetChild(HuffmanNode* node, HuffmanNode*& field, bool index);

        // Also accessed by HuffmanLeaf
        private: void m_UpdateFreq();

        #pragma endregion

        #pragma region operators

        /// @brief Gets the child at the specified "index"
        /// @param index Child "index"
        /// @return If index is false, child node 0 is returned. \
        /// @return If index is true, child node 1 is returned.
        public: HuffmanNode* operator[](bool index);

        /// @brief Gets the child at the specified "index"
        /// @param index Child "index"
        /// @return If index is false, child node 0 is returned. \
        /// @return If index is true, child node 1 is returned.
        public: const HuffmanNode* operator[](bool index) const;

        #pragma endregion

        #pragma region function

        /// @brief Attempts to set the specified node as child node 0
        /// @param node Child node (use nullptr to disown child 0)
        /// @return Whether or not successful
        /// @note Only leaf nodes and branch nodes can be child nodes
        public: bool setChild0(HuffmanNode* node);

        /// @brief Attempts to set the specified node as child node 1
        /// @param node Child node (use nullptr to disown child 1)
        /// @return Whether or not successful
        /// @note Only leaf nodes and branch nodes can be child nodes
        public: bool setChild1(HuffmanNode* node);

        #pragma endregion
    };
}

#endif