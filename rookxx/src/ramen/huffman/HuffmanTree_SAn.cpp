#include "ramen/huffman/HuffmanTree_SAn.h"

#include <cmath>
#include <iostream>

#include "ramen/ArrUtil.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanTree_SAn::HuffmanTree_SAn(const HuffmanTree& tree) :
    f_Tree(tree),
    f_NumPGens(0), f_NumParents(0), f_PGens_Parent(nullptr), f_PGens_Size(nullptr),
    f_LargestPGenSize(0), f_MaxLeafValue(0), f_MaxLeafFreq(0)
{
    // Number of parent generations
    f_NumPGens = m_ComputeNumPGens(tree.root()); // Should always be >= 1
    // Number of parents
    f_PGens_Size = ArrUtil::createNull<size_t>(f_NumPGens);
    ArrUtil::nullify(f_PGens_Size, f_NumPGens);
    m_CountParents(f_Tree.root());
    // Parents
    f_PGens_Parent = ArrUtil::create<Parent*>(f_NumPGens);
    for (size_t i = 0; i < f_NumPGens; i++)
    {
        size_t pgenSize = f_PGens_Size[i];
        f_PGens_Parent[i] = ArrUtil::createNull<Parent>(pgenSize);
        if (f_LargestPGenSize < pgenSize) f_LargestPGenSize = pgenSize;
    }
    m_AnalyzeParent(f_Tree.root());
}

HuffmanTree_SAn::~HuffmanTree_SAn()
{
    if (f_PGens_Parent)
    {
        for (size_t i = 0; i < f_NumPGens; i++)
        {
            if (f_PGens_Parent[i])
                delete[] f_PGens_Parent[i];
        }
        delete[] f_PGens_Parent;
    }
    if (f_PGens_Size)
    {
        delete[] f_PGens_Size;
    }
}

#pragma endregion

#pragma region properties

size_t HuffmanTree_SAn::numPGens() const { return f_NumPGens; }

size_t HuffmanTree_SAn::numParents() const { return f_NumParents; }

size_t HuffmanTree_SAn::largestPGenSize() const { return f_LargestPGenSize; }

uint8_t HuffmanTree_SAn::maxLeafValue() const { return f_MaxLeafValue; }

size_t HuffmanTree_SAn::maxLeafFreq() const { return f_MaxLeafFreq; }

#pragma endregion

#pragma region helper

size_t HuffmanTree_SAn::m_ComputeNumPGens(const HuffmanNode& node, size_t pgen)
{
    // Make sure node is a parent node
    if (!node.isParent()) return pgen;
    // Cast as parent
    const HuffmanParent& parent = *static_cast<const HuffmanParent*>(&node);
    // Check children
    size_t child0 = pgen + 1;
    size_t child1 = pgen + 1;
    if (parent.child0()) child0 = m_ComputeNumPGens(*parent.child0(), child0);
    if (parent.child1()) child1 = m_ComputeNumPGens(*parent.child1(), child1);
    return std::max(child0, child1);
}

void HuffmanTree_SAn::m_CountParents(const HuffmanNode& node, size_t pgen)
{
    // Make sure node is a parent node
    if (!node.isParent()) return;
    // Cast as parent
    const HuffmanParent& parent = *static_cast<const HuffmanParent*>(&node);
    f_NumParents += 1;
    f_PGens_Size[pgen] += 1;
    // Check children
    if (parent.child0()) m_CountParents(*parent.child0(), pgen + 1);
    if (parent.child1()) m_CountParents(*parent.child1(), pgen + 1);
}

void HuffmanTree_SAn::m_AnalyzeParent(const HuffmanParent& parent, size_t pgen, size_t* pgenOffsets)
{
    // Fix offsets
    bool delOffsets = !pgenOffsets;
    if (delOffsets) pgenOffsets = ArrUtil::createNull<size_t>(f_NumPGens);
    // Parent
    f_PGens_Parent[pgen][pgenOffsets[pgen]++] = 
    {
        .child0 = m_AnalyzeChild(parent.child0(), pgen + 1, pgenOffsets),
        .child1 = m_AnalyzeChild(parent.child1(), pgen + 1, pgenOffsets),
    };
    // Delete offsets (if neccessary)
    if (delOffsets) delete[] pgenOffsets;
}

HuffmanTree_SAn::Child HuffmanTree_SAn::m_AnalyzeChild(const HuffmanNode* node, size_t pgen, size_t* pgenOffsets)
{
    if (!node)
    {
        return { .isParent = true, .valInd = ~(size_t)0, };
    }
    else if (node->isParent())
    {
        const HuffmanParent& parent = *static_cast<const HuffmanParent*>(node);
        size_t index = pgenOffsets[pgen];
        m_AnalyzeParent(parent, pgen, pgenOffsets);
        return { .isParent = true, .valInd = index, };
    }
    else if (node->type() == HuffmanNodeType::Leaf)
    {
        const HuffmanLeaf& leaf = *static_cast<const HuffmanLeaf*>(node);
        if (f_MaxLeafValue < leaf.value()) f_MaxLeafValue = leaf.value();
        if (f_MaxLeafFreq < leaf.freq()) f_MaxLeafFreq = leaf.freq();
        return { .isParent = false, .valInd = leaf.value(), .freq = leaf.freq(), };
    }
    return { };
}

#pragma endregion

#pragma region functions

HuffmanTree_SAn::Parent HuffmanTree_SAn::getParent(size_t pgen, size_t index) const
{
    return f_PGens_Parent[pgen][index];
}

size_t HuffmanTree_SAn::getSize(size_t pgen) const
{
    return f_PGens_Size[pgen];
}

#pragma endregion