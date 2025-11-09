#include "ramen/huffman/HuffmanTree.h"

#ifndef TreePrinter_h
#define TreePrinter_h

class TreePrinter
{
    public: static void run(const rookxx::ramen::huffman::HuffmanTree& tree, bool printChars = false);
    private: static size_t m_GetDepth(const rookxx::ramen::huffman::HuffmanParent& parent, size_t start = 0);
    private: static size_t m_GetDepth(const rookxx::ramen::huffman::HuffmanNode& node, size_t start);
    private: static void m_PlaceOnGrid(const rookxx::ramen::huffman::HuffmanNode& node, const rookxx::ramen::huffman::HuffmanNode** grid, 
        size_t gridW, size_t gen = 0, size_t offset = 0, size_t width = ~(size_t)0);
};

#endif