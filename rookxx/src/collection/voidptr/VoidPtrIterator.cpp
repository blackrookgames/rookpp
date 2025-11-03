#include "collection/voidptr/VoidPtrIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrIterator::VoidPtrIterator() { }

VoidPtrIterator::~VoidPtrIterator() { }

#pragma endregion

#pragma region operators

VoidPtrIterator::operator bool() { return notAtEnd(); }

VoidPtrIterator::operator bool() const { return notAtEnd(); }

void* VoidPtrIterator::operator*() { return current(); }

#pragma endregion