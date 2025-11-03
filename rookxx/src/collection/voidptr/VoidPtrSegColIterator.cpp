#include "collection/voidptr/VoidPtrSegColIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrSegColIterator::VoidPtrSegColIterator()
{
    f_SegCol = nullptr;
    f_Prev = nullptr;
    f_Curr = nullptr;
}

VoidPtrSegColIterator::VoidPtrSegColIterator(const VoidPtrSegColIterator& src)
{
    f_SegCol = src.f_SegCol;
    f_Prev = src.f_Prev;
    f_Curr = src.f_Curr;
}

VoidPtrSegColIterator::VoidPtrSegColIterator(VoidPtrSegColIterator&& src)
{
    f_SegCol = src.f_SegCol;
    f_Prev = src.f_Prev;
    f_Curr = src.f_Curr;
}

VoidPtrSegColIterator::~VoidPtrSegColIterator()
{
    f_SegCol = nullptr;
    f_Prev = nullptr;
    f_Curr = nullptr;
}

#pragma endregion

#pragma region assignment

VoidPtrSegColIterator& VoidPtrSegColIterator::operator=(const VoidPtrSegColIterator& src)
{
    if (this != &src)
    {
        f_SegCol = src.f_SegCol;
        f_Prev = src.f_Prev;
        f_Curr = src.f_Curr;
    }
    return *this;
}

VoidPtrSegColIterator& VoidPtrSegColIterator::operator=(VoidPtrSegColIterator&& src)
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

bool VoidPtrSegColIterator::notAtEnd() const
{
    return f_Curr;
}

void VoidPtrSegColIterator::next()
{
    if (!f_Curr) return;
    f_Prev = f_Curr;
    f_Curr = f_Curr->next();
}

void* VoidPtrSegColIterator::current()
{
    return f_Curr->data();
}

#pragma endregion