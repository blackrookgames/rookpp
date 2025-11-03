#include "collection/voidptr/VoidPtrListIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrListIterator::VoidPtrListIterator(VoidPtrList* list)
{
    f_List = list;
    f_Index = 0;
    f_Current = (f_Index >= f_List->size()) ? nullptr : (*f_List)[f_Index];
}

VoidPtrListIterator::VoidPtrListIterator(const VoidPtrListIterator& src)
{
    f_List = src.f_List;
    f_Index = src.f_Index;
    f_Current = src.f_Current;
}

VoidPtrListIterator::VoidPtrListIterator(VoidPtrListIterator&& src)
{
    f_List = src.f_List;
    f_Index = src.f_Index;
    f_Current = src.f_Current;
}

VoidPtrListIterator::~VoidPtrListIterator() { }

#pragma endregion

#pragma region assignment

VoidPtrListIterator& VoidPtrListIterator::operator=(const VoidPtrListIterator& src)
{
    if (this != &src)
    {
        f_List = src.f_List;
        f_Index = src.f_Index;
        f_Current = src.f_Current;
    }
    return *this;
}

VoidPtrListIterator& VoidPtrListIterator::operator=(VoidPtrListIterator&& src)
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

bool VoidPtrListIterator::notAtEnd() const
{
    return (f_Index < f_List->size());
}

void VoidPtrListIterator::next()
{
    if (f_Index >= f_List->size())
        return;
    if (++f_Index < f_List->size())
        f_Current = (*f_List)[f_Index];
    else f_Current = nullptr;
}

void* VoidPtrListIterator::current()
{
    return f_Current;
}

#pragma endregion