#include "collection/voidptr/VoidPtrSegCol.h"

#include <utility>

#include "collection/voidptr/VoidPtrSegColConstIterator.h"
#include "collection/voidptr/VoidPtrSegColIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrSegCol::VoidPtrSegCol()
{
    f_First = nullptr;
    f_Last = nullptr;
    f_Size = 0;
}

VoidPtrSegCol::VoidPtrSegCol(const VoidPtrSegCol& src)
{
    m_CopyFrom(src);
}

VoidPtrSegCol::VoidPtrSegCol(VoidPtrSegCol&& src)
{
    m_MoveFrom(std::move(src));
}

VoidPtrSegCol::~VoidPtrSegCol()
{
    m_Reset();
}

#pragma endregion

#pragma region assignment

VoidPtrSegCol& VoidPtrSegCol::operator=(const VoidPtrSegCol& src)
{
    if (this != &src)
    {
        m_Reset();
        m_CopyFrom(src);
    }
    return *this;
}

VoidPtrSegCol& VoidPtrSegCol::operator=(VoidPtrSegCol&& src)
{
    if (this != &src)
    {
        m_Reset();
        m_MoveFrom(std::move(src));
    }
    return *this;
}

#pragma endregion

#pragma region properties

size_t VoidPtrSegCol::size() const { return f_Size; }

#pragma endregion

#pragma region helper

void VoidPtrSegCol::m_CopyFrom(const VoidPtrSegCol& src)
{
    if (src.f_First)
    {
        f_First = new VoidPtrSegColSegment();
        VoidPtrSegColSegment* iseg = src.f_First;
        f_Last = f_First;
        while (true)
        {
            // Set data
            f_Last->data(iseg->data());
            // Set next
            iseg = iseg->next();
            if (iseg)
            {
                VoidPtrSegColSegment* next = new VoidPtrSegColSegment();
                f_Last->next(next);
                f_Last = next;
            }
            else
            {
                f_Last->next(nullptr);
                break;
            }
        }
    }
    else
    {
        f_First = nullptr;
        f_Last = nullptr;
    }
    f_Size = src.f_Size;
}
        
void VoidPtrSegCol::m_MoveFrom(VoidPtrSegCol&& src)
{
    f_First = src.f_First;
    f_Last = src.f_Last;
    f_Size = src.f_Size;
    src.f_First = nullptr;
    src.f_Last = nullptr;
    src.f_Size = 0;
}
        
void VoidPtrSegCol::m_Reset()
{
    while (f_First)
    {
        VoidPtrSegColSegment* next = f_First->next();
        delete f_First;
        f_First = next;
    }
    f_Last = nullptr;
    f_Size = 0;
}

#pragma endregion

#pragma region functions

void VoidPtrSegCol::insert(VoidPtrSegColIterator& position, void* ptr)
{
    if (position.f_SegCol != this) return;
    // Create new segment
    VoidPtrSegColSegment* newSeg = new VoidPtrSegColSegment();
    newSeg->data(ptr);
    newSeg->next(position.f_Curr);
    // Update current segment
    position.f_Curr = newSeg;
    if (!newSeg->next()) f_Last = newSeg;
    // Update previous segment
    if (position.f_Prev) position.f_Prev->next(newSeg);
    else f_First = newSeg;
    // Update size
    f_Size++;
}

void VoidPtrSegCol::remove(VoidPtrSegColIterator& position)
{
    if (position.f_SegCol != this) return;
    // Extract segment
    VoidPtrSegColSegment* seg = position.f_Curr;
    if (!seg) return;
    // Update current segment
    position.f_Curr = seg->next();
    if (!position.f_Curr) f_Last = position.f_Prev;
    // Update previous segment
    if (position.f_Prev) position.f_Prev->next(position.f_Curr);
    else f_First = position.f_Curr;
    // Delete segment
    delete seg;
    // Update size
    f_Size--;
}

void VoidPtrSegCol::clear()
{
    m_Reset();
}

VoidPtrSegColIterator VoidPtrSegCol::getIterator()
{
    VoidPtrSegColIterator iterator;
    iterator.f_SegCol = this;
    iterator.f_Curr = f_First;
    iterator.f_Prev = nullptr;
    return iterator;
}

VoidPtrSegColConstIterator VoidPtrSegCol::getIterator() const
{
    VoidPtrSegColConstIterator iterator;
    iterator.f_SegCol = this;
    iterator.f_Curr = f_First;
    iterator.f_Prev = nullptr;
    return iterator;
}

#pragma endregion