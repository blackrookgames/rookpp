#include "collection/voidptr/VoidPtrConstIterator.h"

using namespace rookxx::collection::voidptr;

#pragma region init

VoidPtrConstIterator::VoidPtrConstIterator() { }

VoidPtrConstIterator::~VoidPtrConstIterator() { }

#pragma endregion

#pragma region operators

VoidPtrConstIterator::operator bool() { return notAtEnd(); }

VoidPtrConstIterator::operator bool() const { return notAtEnd(); }

const void* VoidPtrConstIterator::operator*() { return current(); }

#pragma endregion