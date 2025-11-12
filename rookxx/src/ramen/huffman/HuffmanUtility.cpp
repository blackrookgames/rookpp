#include "ramen/huffman/HuffmanUtility.h"

#include <iostream>
#include <vector>

#include "bitman/BitPtr.h"
#include "bitman/ConstBitPtr.h"
#include "ramen/ArrUtil.h"
#include "ramen/SmartReader.h"
#include "ramen/SmartWriter.h"

#pragma region macros

#define mc_NullArray(type, name, size) \
    type name[size]; ArrUtil::nullify(name, size);

#pragma endregion

using namespace rookxx::ramen::huffman;

#pragma region helper

// Assume leafCount has been initialized to zero
void m_EvaluateTree_Phase0(
    const HuffmanNode& node, 
    size_t& depth, size_t& leafCount, 
    size_t currentDepth = 0)
{
    if (node.isParent())
    {
        const HuffmanParent& parent = *static_cast<const HuffmanParent*>(&node);
        size_t child0 = currentDepth;
        size_t child1 = currentDepth;
        if (parent.child0()) m_EvaluateTree_Phase0(*parent.child0(), child0, leafCount, child0 + 1);
        if (parent.child1()) m_EvaluateTree_Phase0(*parent.child1(), child1, leafCount, child1 + 1);
        depth = std::max(child0, child1);
    }
    else if (node.type() == HuffmanNodeType::Leaf)
    {
        ++leafCount;
        depth = currentDepth;
    }
}

void m_EvaluateTree_Phase1(
    const HuffmanNode& node,
    std::vector<const HuffmanLeaf*>& leaves_Ptr,
    std::vector<size_t>& leaves_Depth,
    size_t currentDepth = 0)
{
    if (node.isParent())
    {
        const HuffmanParent& parent = *static_cast<const HuffmanParent*>(&node);
        m_EvaluateTree_Phase1(*parent.child0(), leaves_Ptr, leaves_Depth, currentDepth + 1);
        m_EvaluateTree_Phase1(*parent.child1(), leaves_Ptr, leaves_Depth, currentDepth + 1);
    }
    else if (node.type() == HuffmanNodeType::Leaf)
    {
        leaves_Ptr.push_back(static_cast<const HuffmanLeaf*>(&node));
        leaves_Depth.push_back(currentDepth);
    }
}

void m_EvaluateTree(const HuffmanTree& tree, uint8_t*& bitTable_Bits, size_t*& bitTable_Lens, size_t& bytesPerRow)
{
    size_t depth = 0;
    size_t leafCount = 0;
    m_EvaluateTree_Phase0(tree.root(), depth, leafCount);
    std::vector<const HuffmanLeaf*> leaves_Ptr;
    std::vector<size_t> leaves_Depth;
    leaves_Ptr.reserve(leafCount);
    leaves_Depth.reserve(leafCount);
    m_EvaluateTree_Phase1(tree.root(), leaves_Ptr, leaves_Depth);
    // Create table
    bytesPerRow = (depth + 7) / 8;
    bitTable_Bits = rookxx::ramen::ArrUtil::create<uint8_t>(bytesPerRow * 256);
    bitTable_Lens = rookxx::ramen::ArrUtil::createNull<size_t>(256);
    if (bitTable_Bits)
    {
        auto lptr = leaves_Ptr.begin();
        auto dptr = leaves_Depth.begin();
        while (lptr != leaves_Ptr.end())
        {
            const HuffmanNode* node = *lptr;
            uint8_t i = (*lptr)->value();
            // Set bits
            rookxx::bitman::BitPtr optr = bitTable_Bits + ((size_t)i * bytesPerRow);
            for (size_t j = 0; j < *dptr; j++)
                ++optr;
            for (size_t j = 0; j < *dptr; j++)
            {
                *(--optr) = node->index();
                node = node->parent();
            }
            // Set length
            bitTable_Lens[i] = *dptr;
            // Next
            ++lptr; ++dptr;
        }
    }
}

#pragma endregion

#pragma region encode/decode 0

bool HuffmanUtility::encode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize)
{
    odata = nullptr;
    osize = 0;
    bool success = false;
    uint8_t* bitTable_Bits = nullptr;
    size_t* bitTable_Lens = nullptr;
    size_t bytesPerRow = 0;
    {
        const uint8_t* istop = idata + isize;
        // Create bit table
        m_EvaluateTree(tree, bitTable_Bits, bitTable_Lens, bytesPerRow);
        // Determine bit size
        size_t bitSize = 0;
        for (const uint8_t* iptr = idata; iptr < istop; ++iptr)
        {
            size_t len = bitTable_Lens[*iptr];
            if (len == 0) goto finish;
            bitSize += len;
        }
        size_t byteSize = (bitSize + 7) / 8;
        // Determine size needed to store size of uncompressed bytes
        uint8_t sizeLen = 1;
        while (isize >= (1 << sizeLen))
            ++sizeLen;
        size_t sizeByteLen = (sizeLen + 7) / 8;
        // Create output
        osize = 1 + sizeByteLen + byteSize;
        odata = ArrUtil::create<uint8_t>(osize);
        {
            uint8_t* optr = odata;
            // Size
            *(optr++) = sizeLen;
            for (uint8_t i = sizeByteLen; i > 0; --i)
                *(optr++) = (uint8_t)((isize >> ((i - 1) * 8)) & 0xFF);
            // Data
            {
                rookxx::bitman::BitPtr boptr = optr;
                for (const uint8_t* iptr = idata; iptr < istop; ++iptr)
                {
                    rookxx::bitman::BitPtr biptr = bitTable_Bits + (size_t)*iptr * bytesPerRow;
                    size_t len = bitTable_Lens[*iptr];
                    for (size_t j = 0; j < len; j++)
                        *(boptr++) = (bool)*(biptr++);
                }
            }
            optr += byteSize;
        }
    }
    success = true;
finish:
    if (bitTable_Bits) delete[] bitTable_Bits;
    if (bitTable_Lens) delete[] bitTable_Lens;
    return success;
}

bool HuffmanUtility::decode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize)
{
    odata = nullptr;
    osize = 0;
    {
        const uint8_t* iptr = idata;
        const uint8_t* istop = idata + isize;
        // Get output size of uncompressed bytes
        {
            if ((iptr + 1) > istop) goto fail;
            uint8_t sizeLen = *(iptr++);
            uint8_t sizeByteLen = (sizeLen + 7) / 8;
            if ((iptr + sizeByteLen) > istop) goto fail;
            osize = 0;
            for (size_t i = 0; i < sizeByteLen; i++)
            {
                osize <<= 8;
                osize |= *(iptr++);
            }
            osize &= ~((~(size_t)0) << sizeLen);
        }
        // Get data
        odata = ArrUtil::create<uint8_t>(osize);
        {
            rookxx::bitman::ConstBitPtr bptr = iptr;
            uint8_t* optr = odata;
            const HuffmanParent* parent = &tree.root();
            for (size_t i = (istop - iptr) * 8; i > 0; i--)
            {
                bool index = *(bptr++);
                const HuffmanNode* child = (*parent)[index];
                if (child)
                {
                    // Is child a parent?
                    if (child->isParent())
                    {
                        parent = static_cast<const HuffmanParent*>(child);
                        continue;
                    }
                    // Is child a leaf?
                    if (child->type() == HuffmanNodeType::Leaf)
                    {
                        *(optr++) = static_cast<const HuffmanLeaf*>(child)->value();
                        parent = &tree.root();
                        if ((optr - odata) >= osize)
                            break;
                        continue;
                    }
                }
                *(optr++) = 0;
                parent = &tree.root();
                if ((optr - odata) >= osize)
                    break;
            }
            while ((optr - odata) < osize)
                *(optr++) = 0;
        }
    }
    return true;
fail:
    if (odata) delete[] odata;
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
    return decode(sr.pos(), sr.end() - sr.beg(), tree, odata, osize);
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