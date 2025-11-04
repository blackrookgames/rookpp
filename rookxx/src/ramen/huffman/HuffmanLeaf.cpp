#include "ramen/huffman/HuffmanLeaf.h"

#include "ramen/huffman/HuffmanParent.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanLeaf::HuffmanLeaf() : 
    HuffmanLeaf(0, 0)
{ }

HuffmanLeaf::HuffmanLeaf(uint8_t value, size_t freq) :
    f_Value(value), f_Freq(freq)
{ }

HuffmanLeaf::~HuffmanLeaf()
{ }

#pragma endregion

#pragma region properties

HuffmanNodeType HuffmanLeaf::type() const { return HuffmanNodeType::Leaf; }

bool HuffmanLeaf::isParent() const { return false; }

uint8_t HuffmanLeaf::value() const { return f_Value; }
void HuffmanLeaf::value(uint8_t val) { f_Value = val; }

size_t HuffmanLeaf::freq() const { return f_Freq; }
void HuffmanLeaf::freq(size_t val)
{
    f_Freq = val;
    if (parent()) parent()->m_UpdateFreq();
}

#pragma endregion