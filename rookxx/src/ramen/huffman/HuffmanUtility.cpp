#include "ramen/huffman/HuffmanUtility.h"

#include <iostream>
#include <vector>

#include "ramen/ArrUtil.h"
#include "ramen/SmartReader.h"
#include "ramen/SmartWriter.h"

#pragma region macros

#define mc_NullArray(type, name, size) \
    type name[size]; ArrUtil::nullify(name, size);

#pragma endregion

using namespace rookxx::ramen::huffman;

#pragma region helper

size_t m_GetDepth(const HuffmanNode& node, size_t currentDepth = 0)
{
    // Make sure node is parent
    if (!node.isParent()) return currentDepth;
    // Cast as parent
    const HuffmanParent& parent = *static_cast<const HuffmanParent*>(&node);
    size_t child0 = currentDepth;
    size_t child1 = currentDepth;
    if (parent.child0()) child0 = m_GetDepth(*parent.child0(), child0 + 1);
    if (parent.child1()) child1 = m_GetDepth(*parent.child1(), child1 + 1);
    return std::max(child0, child1);
}

#pragma endregion

#pragma region encode/decode 0

bool HuffmanUtility::encode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize)
{
    odata = nullptr;
    osize = 0;
    bool success = false;
    {
        // Get depth
        size_t depth = m_GetDepth(tree.root());
        // TODO: Add code
    }
    success = true;
    return success;
}

bool HuffmanUtility::decode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize)
{
    // TODO: Add code
    odata = nullptr;
    osize = 0;
    return false;
}

#pragma endregion

#pragma region encode/decode 1

bool HuffmanUtility::encode(const uint8_t* idata, size_t isize, uint8_t*& odata, size_t& osize)
{
    odata = nullptr;
    osize = 0;
    bool success = false;
    uint8_t* tdata = nullptr;
    size_t tsize = 0;
    uint8_t* edata = nullptr;
    size_t esize = 0;
    {
        // Construct tree
        HuffmanTree tree;
        populateTree(tree, idata, isize);
        if (!tree.serialize(tdata, tsize))
            goto finish;
        // Encode data
        if (!encode(idata, isize, tree, edata, esize))
            goto finish;
        // Finalize
        osize = tsize + esize;
        odata = ArrUtil::create<uint8_t>(osize);
        if (odata)
        {
            memcpy(odata, tdata, tsize);
            memcpy(odata + tsize, edata, esize);
        }
    }
    success = true;
finish:
    if (tdata) delete[] tdata;
    if (edata) delete[] edata;
    return success;
}

bool HuffmanUtility::decode(const uint8_t* idata, size_t isize, uint8_t*& odata, size_t& osize)
{
    odata = nullptr;
    osize = 0;
    SmartReader sr(idata, isize);
    // Decode tree
    HuffmanTree tree;
    if (!tree.deserialize(sr))
    return false;
    // Decode data
    return decode(sr.pos(), sr.end() - sr.beg(), odata, osize);
}

#pragma endregion

#pragma region tree

void HuffmanUtility::populateTree(HuffmanTree& tree, const uint8_t* idata, size_t isize)
{
    const uint8_t* istop = idata + isize;
    // Reset tree
    tree.root().setChild0(nullptr);
    tree.root().setChild1(nullptr);
    // Count frequencies
    size_t freqs[256];
    size_t leafCount = 0;
    ArrUtil::nullify(freqs, 256);
    {
        for (const uint8_t* iptr = idata; iptr < istop; ++iptr)
        {
            if (freqs[*iptr]++ == 0)
                ++leafCount;
        }
    }
    if (leafCount == 0)
        return;
    // Create queue
    std::vector<HuffmanNode*> queue;
    queue.reserve(leafCount);
    {
        for (uint16_t i = 0; i < 256; ++i)
        {
            uint8_t freq = freqs[i];
            if (freq == 0) continue;
            // Create leaf
            HuffmanLeaf* leaf = new HuffmanLeaf(i, freq, true);
            // Insert into queue
            auto pos = queue.begin();
            while (pos != queue.end())
            {
                if (leaf->freq() <= (*pos)->freq())
                    break;
                ++pos;
            }
            queue.insert(pos, leaf);
        }
    }
    if (leafCount == 1)
    {
        tree.root().setChild0(queue[0]);
        return;
    }
    // Build tree
    while (queue.size() > 2)
    {
        // Remove first two nodes
        HuffmanNode* node0 = *queue.begin();
        queue.erase(queue.begin());
        HuffmanNode* node1 = *queue.begin();
        queue.erase(queue.begin());
        // Create parent
        HuffmanParent* parent = new huffman::HuffmanParent(true);
        parent->setChild0(node0);
        parent->setChild1(node1);
        // Insert parent into queue
        auto pos = queue.begin();
        while (pos != queue.end())
        {
            if (parent->freq() <= (*pos)->freq())
                break;
            ++pos;
        }
        queue.insert(pos, parent);
    }
    tree.root().setChild0(queue[0]);
    tree.root().setChild1(queue[1]);
}

#pragma endregion