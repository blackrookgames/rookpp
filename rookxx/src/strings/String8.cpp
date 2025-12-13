#include "strings/String8.h"

using namespace rookxx::strings;

String8::String8() : StringTemplate<uint8_t, size_t>()
{ }

String8::String8(size_t length) : StringTemplate<uint8_t, size_t>(length)
{ }

String8::String8(const char* cstr) : StringTemplate<uint8_t, size_t>(cstr)
{ }

String8::~String8()
{ }