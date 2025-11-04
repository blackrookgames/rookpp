#include "ramen/huffman/HuffmanTree.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanTree::HuffmanTree() : 
    f_Root(HuffmanNodeType::Root)
{ }

HuffmanTree::~HuffmanTree()
{ }

#pragma endregion

#pragma region serialization

bool HuffmanTree::serialize(uint8_t*& data, size_t& size) const
{
    data = nullptr;
    size = 0;
    return false;
}

bool HuffmanTree::deserialize(const uint8_t* data, size_t size)
{
    f_Root.setChild0(nullptr);
    f_Root.setChild1(nullptr);
    return false;
}

#pragma endregion

#pragma region properties

HuffmanParent& HuffmanTree::root() { return f_Root; }
const HuffmanParent& HuffmanTree::root() const { return f_Root; }

#pragma endregion