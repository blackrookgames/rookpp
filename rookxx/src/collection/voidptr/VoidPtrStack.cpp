#include "collection/voidptr/VoidPtrStack.h"

#include <utility>

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrStack::VoidPtrStack() : VoidPtrSegCol() 
{ }

VoidPtrStack::VoidPtrStack(const VoidPtrStack& src) : VoidPtrSegCol(src) 
{ }

VoidPtrStack::VoidPtrStack(VoidPtrStack&& src) : VoidPtrSegCol(std::move(src)) 
{ }

VoidPtrStack::~VoidPtrStack() { }

#pragma endregion

#pragma region properties

void* VoidPtrStack::top() { return f_First->data(); }
const void* VoidPtrStack::top() const { return f_First->data(); }

#pragma endregion

#pragma region functions

void VoidPtrStack::push(void* ptr)
{
    // Create new segment
    VoidPtrSegColSegment* seg = new VoidPtrSegColSegment();
    seg->data(ptr);
    seg->next(f_First);
    // Update first
    f_First = seg;
    // Update last
    if (!seg->next()) f_Last = seg;
    // Update size
    f_Size++;
}

void* VoidPtrStack::pop()
{
    if (!f_First) return nullptr;
    // Extract segment
    VoidPtrSegColSegment* seg = f_First;
    void* data = seg->data();
    // Update first
    f_First = seg->next();
    // Update last
    if (!f_First) f_Last = nullptr;
    // Delete segment
    delete seg;
    // Update size
    f_Size--;
    // Return
    return data;
}

#pragma endregion