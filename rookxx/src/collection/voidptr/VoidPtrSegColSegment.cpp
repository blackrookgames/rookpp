#include "collection/voidptr/VoidPtrSegColSegment.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrSegColSegment::VoidPtrSegColSegment()
{
    f_Data = nullptr;
    f_Next = nullptr;
}

VoidPtrSegColSegment::VoidPtrSegColSegment(const VoidPtrSegColSegment& src)
{
    f_Data = src.f_Data;
    f_Next = src.f_Next;
}

VoidPtrSegColSegment::VoidPtrSegColSegment(VoidPtrSegColSegment&& src)
{
    f_Data = src.f_Data;
    f_Next = src.f_Next;
}

VoidPtrSegColSegment::~VoidPtrSegColSegment() { }

#pragma endregion

#pragma region assignment

VoidPtrSegColSegment& VoidPtrSegColSegment::operator=(const VoidPtrSegColSegment& src)
{
    if (this != &src)
    {
        f_Data = src.f_Data;
        f_Next = src.f_Next;
    }
    return *this;
}

VoidPtrSegColSegment& VoidPtrSegColSegment::operator=(VoidPtrSegColSegment&& src)
{
    if (this != &src)
    {
        f_Data = src.f_Data;
        f_Next = src.f_Next;
    }
    return *this;
}

#pragma endregion

#pragma region properties

void* VoidPtrSegColSegment::data() { return f_Data; }
const void* VoidPtrSegColSegment::data() const { return f_Data; }
void VoidPtrSegColSegment::data(void* value) { f_Data = value; }

VoidPtrSegColSegment* VoidPtrSegColSegment::next() { return f_Next; }
const VoidPtrSegColSegment* VoidPtrSegColSegment::next() const { return f_Next; }
void VoidPtrSegColSegment::next(VoidPtrSegColSegment* value) { f_Next = value; }

#pragma endregion