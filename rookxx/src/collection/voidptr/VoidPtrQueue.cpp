#include "collection/voidptr/VoidPtrQueue.h"

#include <utility>

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrQueue::VoidPtrQueue() : VoidPtrSegCol() 
{ }

VoidPtrQueue::VoidPtrQueue(const VoidPtrQueue& src) : VoidPtrSegCol(src) 
{ }

VoidPtrQueue::VoidPtrQueue(VoidPtrQueue&& src) : VoidPtrSegCol(std::move(src)) 
{ }

VoidPtrQueue::~VoidPtrQueue() { }

#pragma endregion

#pragma region properties

void* VoidPtrQueue::front() { return f_First->data(); }
const void* VoidPtrQueue::front() const { return f_First->data(); }

#pragma endregion

#pragma region functions

void VoidPtrQueue::push(void* ptr)
{
    // Create new segment
    VoidPtrSegColSegment* seg = new VoidPtrSegColSegment();
    seg->data(ptr);
    seg->next(nullptr);
    // Update first
    if (!f_First) f_First = seg;
    // Update last
    if (f_Last) f_Last->next(seg);
    f_Last = seg;
    // Update size
    f_Size++;
}

void* VoidPtrQueue::pop()
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