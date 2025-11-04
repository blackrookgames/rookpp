#include "TreePrinter.h"

#include <cmath>
#include <cstdint>
#include <iostream>

namespace huffman = rookxx::ramen::huffman;

void TreePrinter::run(const huffman::HuffmanTree& tree)
{
    // Get depth
    size_t depth = m_GetDepth(tree.root());
    // Grid
    size_t gridW = ((1 << depth) * 2) - 1;
    size_t gridH = depth + 1;
    size_t gridS = gridW * gridH;
    const huffman::HuffmanNode* grid[gridS];
    for (size_t i = 0; i < gridS; i++)
        grid[i] = nullptr;
    m_PlaceOnGrid(tree.root(), grid, gridW);
    // Create print
    static const size_t nodeW = 12;
    static const size_t nodeH = 5;
    size_t printW = nodeW * gridW;
    size_t printH = nodeH * gridH;
    size_t printS = printW * printH;
    char print[printS];
    for (size_t i = 0; i < printS; i++)
        print[i] = ' ';
    for (size_t y = 0; y < gridH; y++)
    {
        for (size_t x = 0; x < gridW; x++)
        {
            const huffman::HuffmanNode* cell = grid[x + y * gridW];
            if (!cell) continue;
            // Draw node
            {
                char* yptr = print + (x * nodeW + y * nodeH * printW);
                // Top
                for (size_t xx = 0; xx < nodeW; xx++)
                    yptr[xx] = '#';
                yptr += printW;
                // Frequency
                for (size_t xx = 2; xx < nodeW; xx++)
                    yptr[xx - 1] = ' ';
                yptr[0] = '#';
                yptr[nodeW - 1] = '#';
                {
                    size_t freq = cell->freq();
                    for (size_t xx = nodeW - 3; xx > 2; xx--)
                    {
                        yptr[xx] = '0' + (char)(freq % 10);
                        freq /= 10;
                        if (freq == 0) break;
                    }
                }
                yptr += printW;
                // Value
                for (size_t xx = 2; xx < nodeW; xx++)
                    yptr[xx - 1] = ' ';
                yptr[0] = '#';
                yptr[nodeW - 1] = '#';
                if (cell->type() == huffman::HuffmanNodeType::Leaf)
                {
                    const huffman::HuffmanLeaf& leaf = *static_cast<const huffman::HuffmanLeaf*>(cell);
                    uint8_t value = leaf.value();
                    for (size_t xx = 0; xx < 8; xx++)
                        yptr[2 + xx] = '0' + (char)((value >> (7 - xx)) & 1);
                }
                yptr += printW;
                // Bottom
                for (size_t xx = 0; xx < nodeW; xx++)
                    yptr[xx] = '#';
                yptr += printW;
            }
            // Connection
            if (y > 0)
            {
                char* optr = print + (x * nodeW + (y * nodeH - 1) * printW);
                // Up 0
                optr += cell->index() ? (nodeW / 2) : (nodeW - 1 - (nodeW / 2));
                *optr = '#';
                // Up 1
                optr -= printW;
                *optr = '#';
                // Up 2
                optr -= printW;
                *optr = '#';
                // Sideways
                size_t inc = cell->index() ? (-1) : 1;
                while (true)
                {
                    optr += inc;
                    if (*optr != ' ') break;
                    *optr = '#';
                }
            }
        }
    }
    // Print
    for (size_t y = 0; y < printH; y++)
    {
        for (size_t x = 0; x < printW; x++)
        {
            std::cout << print[x + y * printW];
        }
        std::cout << std::endl;
    }
}

size_t TreePrinter::m_GetDepth(const huffman::HuffmanParent& parent, size_t start)
{
    size_t depth0 = start;
    size_t depth1 = start;
    // Does the parent have children?
    if (parent.child0()) depth0 = m_GetDepth(*parent.child0(), depth0 + 1);
    if (parent.child1()) depth1 = m_GetDepth(*parent.child1(), depth1 + 1);
    // Return
    return std::max(depth0, depth1);
}

size_t TreePrinter::m_GetDepth(const huffman::HuffmanNode& node, size_t start)
{
    // Is the node a parent?
    if (!node.isParent()) return start;
    // Does the node have children?
    return m_GetDepth(*static_cast<const huffman::HuffmanParent*>(&node), start);
}

void TreePrinter::m_PlaceOnGrid(const huffman::HuffmanNode& node, const huffman::HuffmanNode** grid, 
    size_t gridW, size_t gen, size_t offset, size_t width)
{
    // Fix width
    if (width == ~(size_t)0) width = gridW / 2;
    // Place
    grid[offset + width + gridW * gen] = &node;
    // Place children
    if (node.isParent())
    {
        const huffman::HuffmanParent* parent = static_cast<const huffman::HuffmanParent*>(&node);
        if (parent->child0()) m_PlaceOnGrid(*parent->child0(), grid, gridW, gen + 1, offset, width / 2);
        if (parent->child1()) m_PlaceOnGrid(*parent->child1(), grid, gridW, gen + 1, offset + width + 1, width / 2);
    }
}