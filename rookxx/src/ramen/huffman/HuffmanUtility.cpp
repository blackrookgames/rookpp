#include "ramen/huffman/HuffmanUtility.h"

#include "ramen/SmartReader.h"
#include "ramen/SmartWriter.h"

using namespace rookxx::ramen::huffman;

#pragma region encode/decode 0

bool HuffmanUtility::encode(const uint8_t* idata, size_t isize, const HuffmanTree& tree, uint8_t*& odata, size_t& osize)
{
    // TODO: Add code
    odata = nullptr;
    osize = 0;
    return false;
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
    // TODO: Add code
    odata = nullptr;
    osize = 0;
    /*
    SmartWriter sw;
    // Construct tree
    HuffmanTree tree = constructTree(idata, isize);
    encode(idata, isize, tree, odata, osize);
    */
    return false;
}

bool HuffmanUtility::decode(const uint8_t* idata, size_t isize, uint8_t*& odata, size_t& osize)
{
    odata = nullptr;
    osize = 0;
    SmartReader sr(idata, isize);
    // Decode tree
    HuffmanTree tree;
    if (!tree.deserialize(sr)) return false;
    // Decode data
    return decode(sr.pos(), sr.end() - sr.beg(), odata, osize);
}

#pragma endregion

#pragma region tree

/*
HuffmanTree& HuffmanUtility::constructTree(const uint8_t* idata, size_t isize)
{

}
*/

#pragma endregion