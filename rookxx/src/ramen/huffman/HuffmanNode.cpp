#include "ramen/huffman/HuffmanNode.h"

#include "ramen/huffman/HuffmanParent.h"

using namespace rookxx::ramen::huffman;

#pragma region init

HuffmanNode::HuffmanNode(bool deleteWhenDisowned) : 
    f_Deleted(false), 
    f_Parent(nullptr), 
    f_Index(false),
    f_DeleteWhenDisowned(deleteWhenDisowned)
{ }

HuffmanNode::~HuffmanNode()
{
    // Mark as deleted
    f_Deleted = true;
    // Get disowned by parent
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

bool HuffmanNode::deleteWhenDisowned() const { return f_DeleteWhenDisowned; }
void HuffmanNode::deleteWhenDisowned(bool value) { f_DeleteWhenDisowned = value; }

#pragma endregion