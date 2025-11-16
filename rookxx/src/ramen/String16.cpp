#include "ramen/String16.h"

#include <iostream>

using namespace rookxx::ramen;

#pragma region init

String16::String16() : StringTemplate<uint16_t>()
{ }

String16::String16(size_t length) : StringTemplate<uint16_t>(length)
{ }

String16::String16(const char* cstr) : StringTemplate<uint16_t>(cstr)
{ }

String16::~String16() 
{ }

String16::String16(const String16& src) : StringTemplate<uint16_t>(src)
{ }

String16::String16(String16&& src) : StringTemplate<uint16_t>(std::move(src))
{ }

String16& String16::operator=(const String16& src)
{
    StringTemplate<uint16_t>::operator=(src);
    return *this;
}

String16& String16::operator=(String16&& src)
{
    StringTemplate<uint16_t>::operator=(std::move(src));
    return *this;
}

#pragma endregion

#pragma region operators

String16::operator char*() const
{
    char* result = new char[length() + 1];
    char* optr = result;
    for (size_t i = 0; i < length(); i++)
        *(optr++) = (char)(*this)[i];
    *optr = 0;
    return result;
}

#pragma endregion

#pragma region functions

String16 String16::combine(const String16& other) const
{
    const uint16_t* iptr;
    // Create new string
    String16 newStr(length() + other.length());
    uint16_t* optr = newStr.p_Chars();
    // Copy from this
    iptr = p_Chars();
    for (size_t i = 0; i < length(); ++i)
        *(optr++) = *(iptr++);
    // Copy from other
    iptr = other.p_Chars();
    for (size_t i = 0; i < other.length(); ++i)
        *(optr++) = *(iptr++);
    // Return result
    return newStr;
}

String16 String16::append(uint16_t c) const
{
    // Create new string
    String16 newStr(length() + 1);
    uint16_t* optr = newStr.p_Chars();
    // Copy from this
    const uint16_t* iptr = p_Chars();
    for (size_t i = 0; i < length(); ++i)
        *(optr++) = *(iptr++);
    // Add character
    *(optr++) = c;
    // Return result
    return newStr;
}

String16 String16::prepend(uint16_t c) const
{
    // Create new string
    String16 newStr(length() + 1);
    uint16_t* optr = newStr.p_Chars();
    // Add character
    *(optr++) = c;
    // Copy from this
    const uint16_t* iptr = p_Chars();
    for (size_t i = 0; i < length(); ++i)
        *(optr++) = *(iptr++);
    // Return result
    return newStr;
}

#pragma endregion