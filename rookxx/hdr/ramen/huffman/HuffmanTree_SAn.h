#include "ramen/huffman/HuffmanTree.h"

#ifndef rookxx_ramen_huffman_HuffmanTree_SAn_h
#define rookxx_ramen_huffman_HuffmanTree_SAn_h

namespace rookxx::ramen::huffman
{
    /// @brief Represents an analysis for serializing a Huffman-style tree
    class HuffmanTree_SAn
    {
        #pragma region nested

        public: struct Child
        {
            /// @brief Whether or not the child is also a parent
            bool isParent;
            /// @brief If child is a parent, this is index (within the next generation) 
            /// of its parental information. \
            /// @brief If child is not a parent, this is a represented byte value
            size_t valInd;
            /// @brief Frequency
            /// @note Meaningless is child also a parent
            size_t freq;
        };

        public: struct Parent
        {
            /// @brief Information about child 0
            Child child0;
            /// @brief Information about child 1
            Child child1;
        };

        #pragma endregion

        #pragma region init

        /// @brief Constructor for HuffmanTree_SAn
        /// @param tree Huffman tree analyze
        /// @note Also accessed by HuffmanTree
        private: HuffmanTree_SAn(const HuffmanTree& tree);

        /// @brief Destructor for HuffmanTree_SAn
        /// @note Also accessed by HuffmanTree
        private: ~HuffmanTree_SAn();

        // We won't need these
        public: HuffmanTree_SAn(const HuffmanTree_SAn& src) = delete;
        public: HuffmanTree_SAn(HuffmanTree_SAn&& src) = delete;
        public: HuffmanTree_SAn& operator=(const HuffmanTree_SAn& src) = delete;
        public: HuffmanTree_SAn& operator=(HuffmanTree_SAn&& src) = delete;

        #pragma endregion

        #pragma region friends

        friend HuffmanTree;

        #pragma endregion

        #pragma region fields

        private: const HuffmanTree& f_Tree;
        
        private: size_t f_NumPGens;
        private: size_t f_NumParents;
        private: Parent** f_PGens_Parent;
        private: size_t* f_PGens_Size;

        private: size_t f_LargestPGenSize;
        private: uint8_t f_MaxLeafValue;
        private: size_t f_MaxLeafFreq;

        #pragma endregion

        #pragma region properties

        /// @brief Number of parent generations (always >= 1)
        public: size_t numPGens() const;

        /// @brief Total number of parent nodes (always >= 1)
        public: size_t numParents() const;

        /// @brief Size of the largest parent generation (always >= 1)
        public: size_t largestPGenSize() const;

        /// @brief Maximum leaf value
        public: uint8_t maxLeafValue() const;

        /// @brief Maximum leaf frequency
        public: size_t maxLeafFreq() const;

        #pragma endregion

        #pragma region helper

        private: static size_t m_ComputeNumPGens(const HuffmanNode& node, size_t pgen = 0);

        // Assume f_NumPGens has been properly initialized
        // Assume f_PGens_Size has been properly initialized
        private: void m_CountParents(const HuffmanNode& node, size_t pgen = 0);

        // Assume f_NumPGens has been properly initialized
        // Assume f_PGens_Parents has been properly initialized
        // Assume f_PGens_Size has been properly initialized
        private: void m_AnalyzeParent(const HuffmanParent& parent, size_t pgen = 0, size_t* pgenOffsets = nullptr);

        // Assume f_NumPGens has been properly initialized
        // Assume f_PGens_Parents has been properly initialized
        // Assume f_PGens_Size has been properly initialized
        // Assume pgenOffsets
        // Assume size of pgenOffsets == f_NumPGens
        private: Child m_AnalyzeChild(const HuffmanNode* node, size_t pgen, size_t* pgenOffsets);

        #pragma endregion

        #pragma region functions

        /// @brief Gets information about the parent at the specified location
        /// @param pgen Parent generation
        /// @param index Index within parent generation
        /// @return Information about the parent at the specified location
        public: Parent getParent(size_t pgen, size_t index) const;

        /// @brief Gets the size of the specified parent generation
        /// @param pgen Parent generation
        /// @return The size of the specified parent generation
        public: size_t getSize(size_t pgen) const;

        #pragma endregion
    };
}

#endif