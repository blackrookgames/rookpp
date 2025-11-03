#include "collection/voidptr/VoidPtrList.h"

#include "collection/voidptr/VoidPtrListIterator.h"
#include "collection/voidptr/VoidPtrListConstIterator.h"

using namespace rookxx::collection::voidptr;

#define mc_NewArray(newCapacity) ((newCapacity == 0) ? nullptr : new void*[newCapacity])

#pragma region init

VoidPtrList::VoidPtrList()
{
    f_Array = nullptr;
    f_Capacity = 0;
    f_Size = 0;
}

VoidPtrList::VoidPtrList(const VoidPtrList& src)
{
    f_Array = mc_NewArray(src.f_Capacity);
    f_Capacity = src.f_Capacity;
    f_Size = src.f_Size;
    if (f_Array) m_Copy(src.f_Array, f_Array, f_Size, f_Size);
}

VoidPtrList::VoidPtrList(VoidPtrList&& src)
{
    f_Array = src.f_Array;
    f_Capacity = src.f_Capacity;
    f_Size = src.f_Size;
    src.f_Array = nullptr;
    src.f_Capacity = 0;
    src.f_Size = 0;
}

VoidPtrList::~VoidPtrList()
{
    if (f_Array) delete[] f_Array;
    f_Array = nullptr;
    f_Capacity = 0;
    f_Size = 0;
}

#pragma endregion

#pragma region assignment

VoidPtrList& VoidPtrList::operator=(const VoidPtrList& src)
{
    if (this != &src)
    {
        f_Array = mc_NewArray(src.f_Capacity);
        f_Capacity = src.f_Capacity;
        f_Size = src.f_Size;
        if (f_Array) m_Copy(src.f_Array, f_Array, f_Size, f_Size);
    }
    return *this;
}

VoidPtrList& VoidPtrList::operator=(VoidPtrList&& src)
{
    if (this != &src)
    {
        f_Array = src.f_Array;
        f_Capacity = src.f_Capacity;
        f_Size = src.f_Size;
        src.f_Array = nullptr;
        src.f_Capacity = 0;
        src.f_Size = 0;
    }
    return *this;
}

#pragma endregion

#pragma region properties

size_t VoidPtrList::capacity() const { return f_Capacity; }

size_t VoidPtrList::size() const { return f_Size; }

#pragma endregion

#pragma region operators

void*& VoidPtrList::operator[](size_t index)
{
    return f_Array[index];
}

const void* VoidPtrList::operator[](size_t index) const
{
    return f_Array[index];
}

#pragma endregion

#pragma region helpers

void VoidPtrList::m_Copy(void** src, void** dest, size_t count, size_t index)
{
    void** iptr = src + count - 1;
    void** optr = dest + count;
    // Copy elements after gap
    while (count > index)
    {
        *(optr--) = *(iptr--);
        count--;
    }
    // Copy elements before gap
    optr--;
    while (count > 0)
    {
        *(optr--) = *(iptr--);
        count--;
    }
}

void VoidPtrList::m_SetCapacity(size_t newCapacity)
{
    void** newArray = mc_NewArray(newCapacity);
    if (f_Array)
    {
        m_Copy(f_Array, newArray, f_Size, f_Size);
        delete[] f_Array;
    }
    f_Array = newArray;
    f_Capacity = newCapacity;
}

size_t VoidPtrList::m_NewCapacity() const
{
    // Increase capacity
    size_t newCapacity = (f_Capacity << 1) | 1;
    // Adjust in case of overflow
    if (newCapacity < f_Capacity)
        newCapacity = ~((size_t)0);
    // Return
    return newCapacity;
}

void VoidPtrList::m_RemoveGap(void** array, size_t oldCount, size_t index)
{
    void** optr = array + index;
    void** iptr = optr + 1;
    while (--oldCount > index)
        *(optr++) = *(iptr++);
}

void VoidPtrList::m_InsertGap(void** array, size_t oldCount, size_t index)
{
    void** optr = array + oldCount;
    void** iptr = optr - 1;
    while (oldCount-- > index)
        *(optr--) = *(iptr--);
}

#pragma endregion

#pragma region functions

void VoidPtrList::reserve(size_t minCapacity)
{
    if (f_Capacity < minCapacity)
        m_SetCapacity(minCapacity);
}

void VoidPtrList::shrink()
{
    if (f_Capacity != f_Size)
        m_SetCapacity(f_Size);
}

void VoidPtrList::add(void* ptr)
{
    if (f_Size == f_Capacity)
        m_SetCapacity(m_NewCapacity());
    f_Array[f_Size++] = ptr;
}

void VoidPtrList::insert(size_t index, void* ptr)
{
    if (index > f_Size) return;
    if (f_Size == f_Capacity)
    {
        size_t newCapacity = m_NewCapacity();
        void** newArray = new void*[newCapacity];
        if (f_Array)
            m_Copy(f_Array, newArray, f_Size, index);
        delete[] f_Array;
        f_Array = newArray;
        f_Capacity = newCapacity;
    }
    else m_InsertGap(f_Array, f_Size, index);
    f_Array[index] = ptr;
    f_Size++;
}

void VoidPtrList::remove(size_t index)
{
    if (index >= f_Size) return;
    m_RemoveGap(f_Array, f_Size, index);
    f_Size--;
}

void VoidPtrList::clear()
{
    f_Size = 0;
}

VoidPtrListIterator VoidPtrList::getIterator()
{
    VoidPtrListIterator iterator(this);
    return iterator;
}

VoidPtrListConstIterator VoidPtrList::getIterator() const
{
    VoidPtrListConstIterator iterator(this);
    return iterator;
}

#pragma endregion