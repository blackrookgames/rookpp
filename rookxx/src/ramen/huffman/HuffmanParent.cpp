#include "ramen/huffman/HuffmanParent.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanParent::HuffmanParent() : 
    HuffmanParent(HuffmanNodeType::Branch)
{ }

HuffmanParent::HuffmanParent(HuffmanNodeType type) :
    f_Type(type),
    f_Freq(0),
    f_Child0(nullptr),
    f_Child1(nullptr)
{ }

HuffmanParent::~HuffmanParent()
{
    // Unparent children
    if (f_Child0) f_Child0->f_Parent = nullptr;
    if (f_Child1) f_Child1->f_Parent = nullptr;
}

#pragma endregion

#pragma region properties

HuffmanNodeType HuffmanParent::type() const { return f_Type; }

bool HuffmanParent::isParent() const { return true; }

size_t HuffmanParent::freq() const { return f_Freq; }

HuffmanNode* HuffmanParent::child0() { return f_Child0; }
const HuffmanNode* HuffmanParent::child0() const { return f_Child0; }

HuffmanNode* HuffmanParent::child1() { return f_Child1; }
const HuffmanNode* HuffmanParent::child1() const { return f_Child1; }

#pragma endregion

#pragma region helper

bool HuffmanParent::m_SetChild(HuffmanNode* node, HuffmanNode*& field, bool index)
{
    // Make sure node is valid
    if (node)
    {
        // Make sure node is not a root node
        if (node->type() == HuffmanNodeType::Root)
            return false;
        // Make sure node doesn't already have a parent
        if (node->f_Parent)
            return false;
    }
    // Unparent current child
    if (field) field->f_Parent = nullptr;
    // Parent new child
    field = node;
    if (field)
    {
        field->f_Parent = this;
        field->f_Index = index;
    }
    // Update frequency
    m_UpdateFreq();
    // Success!!!
    return true;
}

void HuffmanParent::m_UpdateFreq()
{
    // Update this
    f_Freq = 0;
    if (f_Child0) f_Freq += f_Child0->freq();
    if (f_Child1) f_Freq += f_Child1->freq();
    // Update parent
    if (f_Parent) f_Parent->m_UpdateFreq();
}

#pragma endregion

#pragma region operators

HuffmanNode* HuffmanParent::operator[](bool index)
{
    return index ? f_Child1 : f_Child0;
}

#pragma endregion

#pragma region function

bool HuffmanParent::setChild0(HuffmanNode* node)
{
    return m_SetChild(node, f_Child0, false);
}

bool HuffmanParent::setChild1(HuffmanNode* node)
{
    return m_SetChild(node, f_Child1, true);
}

#pragma endregion