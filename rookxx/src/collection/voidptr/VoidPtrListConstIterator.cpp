#include "collection/voidptr/VoidPtrListConstIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrListConstIterator::VoidPtrListConstIterator(const VoidPtrList* list)
{
    f_List = list;
    f_Index = 0;
    f_Current = (f_Index >= f_List->size()) ? nullptr : (*f_List)[f_Index];
}

VoidPtrListConstIterator::VoidPtrListConstIterator(const VoidPtrListConstIterator& src)
{
    f_List = src.f_List;
    f_Index = src.f_Index;
    f_Current = src.f_Current;
}

VoidPtrListConstIterator::VoidPtrListConstIterator(VoidPtrListConstIterator&& src)
{
    f_List = src.f_List;
    f_Index = src.f_Index;
    f_Current = src.f_Current;
}

VoidPtrListConstIterator::~VoidPtrListConstIterator() { }

#pragma endregion

#pragma region assignment

VoidPtrListConstIterator& VoidPtrListConstIterator::operator=(const VoidPtrListConstIterator& src)
{
    if (this != &src)
    {
        f_List = src.f_List;
        f_Index = src.f_Index;
        f_Current = src.f_Current;
    }
    return *this;
}

VoidPtrListConstIterator& VoidPtrListConstIterator::operator=(VoidPtrListConstIterator&& src)
{
    if (this != &src)
    {
        f_List = src.f_List;
        f_Index = src.f_Index;
        f_Current = src.f_Current;
    }
    return *this;
}

#pragma endregion

#pragma region functions

bool VoidPtrListConstIterator::notAtEnd() const
{
    return (f_Index < f_List->size());
}

void VoidPtrListConstIterator::next()
{
    if (f_Index >= f_List->size())
        return;
    if (++f_Index < f_List->size())
        f_Current = (*f_List)[f_Index];
    else f_Current = nullptr;
}

const void* VoidPtrListConstIterator::current()
{
    return f_Current;
}

#pragma endregion