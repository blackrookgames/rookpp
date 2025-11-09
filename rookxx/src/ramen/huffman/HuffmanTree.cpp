#include "ramen/huffman/HuffmanTree.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

#include "bitman/BitPtr.h"
#include "bitman/ConstBitPtr.h"
#include "ramen/ArrUtil.h"
#include "ramen/huffman/HuffmanTree_SAn.h"

#pragma region macros

#define mc_BitCheck(value, mask) \
    (((value) & (mask)) != 0)

#define mc_Size_BitLenHeader \
    4 /* numPGensBitLen, largestPGenSizeBitLen, leafValBitLen, leafFrqBitLen */
#define mc_Size_NumPGens(numPGensBitLen) \
    (((numPGensBitLen) + 7) / 8)
#define mc_Size_PGenSizes(numPGens, largestPGenSizeBitLen) \
    (((numPGens) * (largestPGenSizeBitLen) + 7) / 8)
#define mc_Size_ParentNodes(totalNumParents, childBitLen) \
    (((totalNumParents) * (childBitLen) * 2 + 7) / 8)

#define mc_ChildBitLen(largestPGenSizeBitLen, leafValBitLen, leafFrqBitLen) \
    (1 + std::max(largestPGenSizeBitLen, (uint8_t)((leafValBitLen) + (leafFrqBitLen))))

#pragma endregion

using namespace rookxx::ramen::huffman;
using namespace rookxx::bitman;

#pragma region helper

struct s_BitLens
{
    uint8_t numPGensBitLen;
    uint8_t largestPGenSizeBitLen;
    uint8_t leafValBitLen;
    uint8_t leafFrqBitLen;
    uint8_t childBitLen;
};

uint8_t m_GetBitLength(size_t value)
{
    uint8_t length = 1;
    while (value >= (1 << length))
        ++length;
    return length;
}

void m_WriteChild(const HuffmanTree_SAn& san, const s_BitLens& bitLens, BitPtr& bptr, const HuffmanTree_SAn::Child& child)
{
    if (child.isParent)
    {
        uint8_t written = 0;
        // Is a parent
        *(bptr++) = true;
        written += 1;
        // Index
        {
            size_t mask = 1 << (bitLens.largestPGenSizeBitLen - 1);
            for (uint8_t j = 0; j < bitLens.largestPGenSizeBitLen; j++)
            {
                *(bptr++) = mc_BitCheck(child.valInd, mask);
                mask >>= 1;
            }
        }
        written += bitLens.largestPGenSizeBitLen;
        // Fill
        while (written < bitLens.childBitLen)
        { *(bptr++) = false; ++written; }
    }
    else
    {
        uint8_t written = 0;
        // Is not a parent
        *(bptr++) = false;
        written += 1;
        // Value
        {
            size_t mask = 1 << (bitLens.leafValBitLen - 1);
            for (uint8_t j = 0; j < bitLens.leafValBitLen; j++)
            {
                *(bptr++) = mc_BitCheck(child.valInd, mask);
                mask >>= 1;
            }
        }
        written += bitLens.leafValBitLen;
        // Frequency
        {
            size_t mask = 1 << (bitLens.leafFrqBitLen - 1);
            for (uint8_t j = 0; j < bitLens.leafFrqBitLen; j++)
            {
                *(bptr++) = mc_BitCheck(child.freq, mask);
                mask >>= 1;
            }
        }
        written += bitLens.leafFrqBitLen;
        // Fill
        while (written < bitLens.childBitLen)
        { *(bptr++) = false; ++written; }
    }
}

HuffmanTree_SAn::Child m_ReadChild(const s_BitLens& bitLens, ConstBitPtr& bptr)
{
    HuffmanTree_SAn::Child child = { .isParent = *(bptr++), };
    uint8_t written = 1;
    if (child.isParent)
    {
        // Index
        {
            child.valInd = 0;
            size_t mask = 1 << (bitLens.largestPGenSizeBitLen - 1);
            for (uint8_t j = 0; j < bitLens.largestPGenSizeBitLen; j++)
            {
                if (*(bptr++)) child.valInd |= mask;
                mask >>= 1;
            }
        }
        written += bitLens.largestPGenSizeBitLen;
        // Fill
        while (written < bitLens.childBitLen)
        { ++bptr; ++written; }
    }
    else
    {
        // Value
        {
            child.valInd = 0;
            size_t mask = 1 << (bitLens.leafValBitLen - 1);
            for (uint8_t j = 0; j < bitLens.leafValBitLen; j++)
            {
                if (*(bptr++)) child.valInd |= mask;
                mask >>= 1;
            }
        }
        written += bitLens.leafValBitLen;
        // Frequency
        {
            child.freq = 0;
            size_t mask = 1 << (bitLens.leafFrqBitLen - 1);
            for (uint8_t j = 0; j < bitLens.leafFrqBitLen; j++)
            {
                if (*(bptr++)) child.freq |= mask;
                mask >>= 1;
            }
        }
        written += bitLens.leafFrqBitLen;
        // Fill
        while (written < bitLens.childBitLen)
        { ++bptr; ++written; }
    }
    return child;
}

void m_BuildParent(
    HuffmanParent& parent, 
    const HuffmanTree_SAn::Parent* parentNodes, 
    size_t numPGens, const size_t* pGenOffsets, const size_t* pGenSizes, 
    size_t pgen = 0, size_t index = 0)
{
    // Get info
    HuffmanTree_SAn::Parent p = parentNodes[pGenOffsets[pgen] + index];
    size_t nextgen = pgen + 1;
    // Child 0
    HuffmanNode* child0 = nullptr;
    if (p.child0.isParent)
    {
        if (nextgen < numPGens && p.child0.valInd < pGenSizes[nextgen])
        {
            HuffmanParent* newParent = new HuffmanParent(true);
            m_BuildParent(*newParent, parentNodes, numPGens, pGenOffsets, pGenSizes, nextgen, p.child0.valInd);
            child0 = newParent;
        }
    }
    else
    {
        child0 = new HuffmanLeaf((uint8_t)(p.child0.valInd & 0xFF), p.child0.freq, true);
    }
    parent.setChild0(child0);
    // Child 1
    HuffmanNode* child1 = nullptr;
    if (p.child1.isParent)
    {
        if (nextgen < numPGens && p.child1.valInd < pGenSizes[nextgen])
        {
            HuffmanParent* newParent = new HuffmanParent(true);
            m_BuildParent(*newParent, parentNodes, numPGens, pGenOffsets, pGenSizes, nextgen, p.child1.valInd);
            child1 = newParent;
        }
    }
    else
    {
        child1 = new HuffmanLeaf((uint8_t)(p.child1.valInd & 0xFF), p.child1.freq, true);
    }
    parent.setChild1(child1);
}

#pragma endregion

#pragma region init

HuffmanTree::HuffmanTree() : 
    f_Root(HuffmanNodeType::Root)
{ }

HuffmanTree::~HuffmanTree()
{ }

#pragma endregion

#pragma region serialization

bool HuffmanTree::serialize(uint8_t*& data, size_t& size, bool excludeFreq) const
{
    if (f_Root.child0() || f_Root.child1())
    {
        // Analyze tree
        HuffmanTree_SAn san(*this);
        s_BitLens bitLens =
        {
            .numPGensBitLen = m_GetBitLength(san.numPGens()),
            .largestPGenSizeBitLen = m_GetBitLength(san.largestPGenSize()),
            .leafValBitLen = m_GetBitLength(san.maxLeafValue()),
            .leafFrqBitLen = excludeFreq ? (uint8_t)0 : m_GetBitLength(san.maxLeafFreq()),
        };
        bitLens.childBitLen = mc_ChildBitLen(
            bitLens.largestPGenSizeBitLen, 
            bitLens.leafValBitLen, 
            bitLens.leafFrqBitLen); // Should always be <= 129
        // Compute byte sizes
        size_t size_BitLenHeader = mc_Size_BitLenHeader;
        size_t size_NumPGens = mc_Size_NumPGens(bitLens.numPGensBitLen);
        size_t size_PGenSizes = mc_Size_PGenSizes(san.numPGens(), bitLens.largestPGenSizeBitLen);
        size_t size_ParentNodes = mc_Size_ParentNodes(san.numParents(), bitLens.childBitLen);
        // Serialize
        size = size_BitLenHeader + size_NumPGens + size_PGenSizes + size_ParentNodes;
        data = ArrUtil::createNull<uint8_t>(size);
        {
            uint8_t* optr = data;
            // Save bit lengths
            *(optr++) = bitLens.numPGensBitLen;
            *(optr++) = bitLens.largestPGenSizeBitLen;
            *(optr++) = bitLens.leafValBitLen;
            *(optr++) = bitLens.leafFrqBitLen;
            // Save number of parent generations
            {
                BitPtr bptr = optr;
                size_t mask = 1 << (bitLens.numPGensBitLen - 1);
                for (uint8_t i = 0; i < bitLens.numPGensBitLen; i++)
                {
                    *(bptr++) = mc_BitCheck(san.numPGens(), mask);
                    mask >>= 1;
                }
            }
            optr += size_NumPGens;
            // Save parent generation sizes
            {
                BitPtr bptr = optr;
                for (size_t i = 0; i < san.numPGens(); i++)
                {
                    size_t pGenSize = san.getSize(i);
                    size_t mask = 1 << (bitLens.largestPGenSizeBitLen - 1);
                    for (uint8_t j = 0; j < bitLens.largestPGenSizeBitLen; j++)
                    {
                        *(bptr++) = mc_BitCheck(pGenSize, mask);
                        mask >>= 1;
                    }
                }
            }
            optr += size_PGenSizes;
            // Save parent generations
            {
                BitPtr bptr = optr;
                for (size_t i = 0; i < san.numPGens(); i++)
                {
                    size_t pGenSize = san.getSize(i);
                    for (size_t j = 0; j < pGenSize; j++)
                    {
                        HuffmanTree_SAn::Parent parent = san.getParent(i, j);
                        m_WriteChild(san, bitLens, bptr, parent.child0);
                        m_WriteChild(san, bitLens, bptr, parent.child1);
                    }
                }
            }
            optr += size_ParentNodes;
        }
    }
    else
    {
        // This will indicate that there's no compression
        size = mc_Size_BitLenHeader;
        data = ArrUtil::createNull<uint8_t>(size);
    }
    // Success!!!
    return true;
}

bool HuffmanTree::serialize(uint8_t*& data, size_t& size) const
{
    return serialize(data, size, false);
}

bool HuffmanTree::deserialize(const uint8_t* data, size_t size)
{
    SmartReader sr(data, size);
    return deserialize(sr);
}

bool HuffmanTree::serialize(SmartWriter& sw, bool excludeFreq) const
{
    if (!sw.valid()) return false;
    uint8_t* data;
    size_t size;
    if (!serialize(data, size, excludeFreq))
        return false;
    sw.write(data, size);
    if (data) delete[] data;
    return sw.valid();
}

bool HuffmanTree::serialize(SmartWriter& sw) const
{
    return HuffmanTree::serialize(sw, false);
}

bool HuffmanTree::deserialize(SmartReader& sr)
{
    f_Root.setChild0(nullptr);
    f_Root.setChild1(nullptr);
    if (!sr.valid()) return false;
    size_t beg = sr.tell();
    {
        // Read bit lengths
        s_BitLens bitLens;
        bitLens.numPGensBitLen = sr.readU8();
        if (!sr.valid()) goto fail;
        bitLens.largestPGenSizeBitLen = sr.readU8();
        if (!sr.valid()) goto fail;
        bitLens.leafValBitLen = sr.readU8();
        if (!sr.valid()) goto fail;
        bitLens.leafFrqBitLen = sr.readU8();
        if (!sr.valid()) goto fail;
        bitLens.childBitLen = mc_ChildBitLen(
            bitLens.largestPGenSizeBitLen, 
            bitLens.leafValBitLen, 
            bitLens.leafFrqBitLen);
        if (bitLens.numPGensBitLen == 0) return true; // No parent generations to extract; just return as successful
        // Read number of parent generations
        size_t numPGens = 0;
        {
            ConstBitPtr bptr = sr.pos();
            sr.seek(sr.tell() + mc_Size_NumPGens(bitLens.numPGensBitLen));
            if (!sr.valid()) goto fail;
            size_t mask = 1 << (bitLens.numPGensBitLen - 1);
            for (uint8_t i = 0; i < bitLens.numPGensBitLen; i++)
            {
                if (*(bptr++))
                    numPGens |= mask;
                mask >>= 1;
            }
        }
        // Read generation sizes
        size_t pGenOffsets[numPGens];
        size_t pGenSizes[numPGens];
        size_t numParents = 0;
        {
            ConstBitPtr bptr = sr.pos();
            sr.seek(sr.tell() + mc_Size_PGenSizes(numPGens, bitLens.largestPGenSizeBitLen));
            if (!sr.valid()) goto fail;
            size_t* offptr = pGenOffsets;
            size_t* sizptr = pGenSizes;
            for (size_t i = 0; i < numPGens; i++)
            {
                *sizptr = 0;
                size_t mask = 1 << (bitLens.largestPGenSizeBitLen - 1);
                for (uint8_t j = 0; j < bitLens.largestPGenSizeBitLen; j++)
                {
                    if (*(bptr++))
                        *sizptr |= mask;
                    mask >>= 1;
                }
                *(offptr++) = numParents;
                numParents += *(sizptr++);
            }
        }
        // Parent nodes
        HuffmanTree_SAn::Parent parentNodes[numParents];
        {
            ConstBitPtr bptr = sr.pos();
            sr.seek(sr.tell() + mc_Size_ParentNodes(numParents, bitLens.childBitLen));
            if (!sr.valid()) goto fail;
            HuffmanTree_SAn::Parent* parptr = parentNodes;
            for (size_t i = 0; i < numParents; i++)
            {
                HuffmanTree_SAn::Parent parent;
                parent.child0 = m_ReadChild(bitLens, bptr);
                parent.child1 = m_ReadChild(bitLens, bptr);
                *(parptr++) = parent;
            }
        }
        // Build tree
        m_BuildParent(f_Root, parentNodes, numPGens, pGenOffsets, pGenSizes);
        // Success!!!
            return true;
    }
fail:
    sr.seek(beg);
    return false;
}

#pragma endregion

#pragma region properties

HuffmanParent& HuffmanTree::root() { return f_Root; }
const HuffmanParent& HuffmanTree::root() const { return f_Root; }

#pragma endregion