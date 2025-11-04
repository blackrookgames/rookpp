#include "ramen/huffman/HuffmanNode.h"

#include "ramen/huffman/HuffmanParent.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanNode::HuffmanNode() : 
    f_Parent(nullptr), f_Index(false)
{ }

HuffmanNode::~HuffmanNode()
{
    if (f_Parent)
    {
        if (f_Index)
            f_Parent->setChild1(nullptr);
        else
            f_Parent->setChild0(nullptr);
    }
}

#pragma endregion

#pragma region properties

HuffmanParent* HuffmanNode::parent() { return f_Parent; }
const HuffmanParent* HuffmanNode::parent() const { return f_Parent; }

bool HuffmanNode::index() const { return f_Index; }

#pragma endregion