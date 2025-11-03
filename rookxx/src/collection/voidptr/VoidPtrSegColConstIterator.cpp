#include "collection/voidptr/VoidPtrSegColConstIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrSegColConstIterator::VoidPtrSegColConstIterator()
{
    f_SegCol = nullptr;
    f_Prev = nullptr;
    f_Curr = nullptr;
}

VoidPtrSegColConstIterator::VoidPtrSegColConstIterator(const VoidPtrSegColConstIterator& src)
{
    f_SegCol = src.f_SegCol;
    f_Prev = src.f_Prev;
    f_Curr = src.f_Curr;
}

VoidPtrSegColConstIterator::VoidPtrSegColConstIterator(VoidPtrSegColConstIterator&& src)
{
    f_SegCol = src.f_SegCol;
    f_Prev = src.f_Prev;
    f_Curr = src.f_Curr;
}

VoidPtrSegColConstIterator::~VoidPtrSegColConstIterator()
{
    f_SegCol = nullptr;
    f_Prev = nullptr;
    f_Curr = nullptr;
}

#pragma endregion

#pragma region assignment

VoidPtrSegColConstIterator& VoidPtrSegColConstIterator::operator=(const VoidPtrSegColConstIterator& src)
{
    if (this != &src)
    {
        f_SegCol = src.f_SegCol;
        f_Prev = src.f_Prev;
        f_Curr = src.f_Curr;
    }
    return *this;
}

VoidPtrSegColConstIterator& VoidPtrSegColConstIterator::operator=(VoidPtrSegColConstIterator&& src)
{
    if (this != &src)
    {
        f_SegCol = src.f_SegCol;
        f_Prev = src.f_Prev;
        f_Curr = src.f_Curr;
    }
    return *this;
}

#pragma endregion

#pragma region functions

bool VoidPtrSegColConstIterator::notAtEnd() const
{
    return f_Curr;
}

void VoidPtrSegColConstIterator::next()
{
    if (!f_Curr) return;
    f_Prev = f_Curr;
    f_Curr = f_Curr->next();
}

const void* VoidPtrSegColConstIterator::current()
{
    return f_Curr->data();
}

#pragma endregion