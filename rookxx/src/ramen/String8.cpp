#include "ramen/String8.h"

using namespace rookxx::ramen;

#pragma region init

String8::String8() : StringTemplate<uint8_t>()
{ }

String8::String8(size_t length) : StringTemplate<uint8_t>(length)
{ }

String8::String8(const char* cstr) : StringTemplate<uint8_t>(cstr)
{ }

String8::~String8() 
{ }

String8::String8(const String8& src) : StringTemplate<uint8_t>(src)
{ }

String8::String8(String8&& src) : StringTemplate<uint8_t>(std::move(src))
{ }

String8& String8::operator=(const String8& src)
{
    StringTemplate<uint8_t>::operator=(src);
    return *this;
}

String8& String8::operator=(String8&& src)
{
    StringTemplate<uint8_t>::operator=(std::move(src));
    return *this;
}

#pragma endregion

#pragma region operators

String8::operator char*() const
{
    char* result = new char[length() + 1];
    char* optr = result;
    for (size_t i = 0; i < length(); i++)
        *(optr++) = (char)(*this)[i];
    *optr = 0;
    return result;
}

#pragma endregion