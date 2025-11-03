#include "ramen/huffman/HuffmanTree.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanTree::HuffmanTree()
{

}

HuffmanTree::~HuffmanTree()
{

}

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
    return false;
}

#pragma endregion