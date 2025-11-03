#include "ramen/SmartWriter.h"

#include <cmath>
#include <cstring>

#include "ramen/DataWriter.h"

#pragma region macros

#define mc_NewArray(size) \
    (((size) == 0) ? nullptr : (new uint8_t[size]))

#define mc_Write(type, func, value) \
{ \
    if (!f_Valid) return; \
    m_UpdateSize(sizeof(type)); \
    DataWriter::func(f_Pos, value); \
}

#define mc_Write2(type, func, value, big) \
{ \
    if (!f_Valid) return; \
    m_UpdateSize(sizeof(type)); \
    DataWriter::func(f_Pos, value, big); \
}

#pragma endregion

using namespace rookxx::ramen;

#pragma region init

SmartWriter::SmartWriter() :
    f_Valid(true),
    f_Beg(nullptr),
    f_Cap(nullptr),
    f_End(nullptr),
    f_Pos(nullptr)
{ }

SmartWriter::~SmartWriter()
{
    m_Reset();
}

void SmartWriter::m_Reset()
{
    if (f_Beg) delete[] f_Beg;
    f_Valid = true;
    f_Beg = nullptr;
    f_Cap = nullptr;
    f_End = nullptr;
    f_Pos = nullptr;
}

#pragma endregion

#pragma region properties

bool SmartWriter::valid() const { return f_Valid; }

uint8_t* SmartWriter::beg() { return f_Beg; }

const uint8_t* SmartWriter::beg() const { return f_Beg; }

uint8_t* SmartWriter::end() { return f_End; }

const uint8_t* SmartWriter::end() const { return f_End; }

uint8_t* SmartWriter::pos() { return f_Pos; }

const uint8_t* SmartWriter::pos() const { return f_Pos; }

#pragma endregion

#pragma region helper

void SmartWriter::m_Realloc(size_t newCap)
{
    // Old
    uint8_t* oldBeg = f_Beg;
    size_t oldCap = f_Cap - f_Beg;
    size_t oldEnd = f_End - f_Beg;
    size_t oldPos = f_Pos - f_Beg;
    // New
    f_Beg = mc_NewArray(newCap);
    f_Cap = f_Beg + newCap;
    f_End = f_Beg + std::min(oldEnd, newCap);
    f_Pos = f_Beg + oldPos;
    f_Valid = f_Pos <= f_End;
    // Copy
    if (oldBeg)
    {
        if (f_Beg)
            memcpy(f_Beg, oldBeg, std::min(oldCap, newCap));
        delete[] oldBeg;
    }
}

void SmartWriter::m_UpdateSize(size_t inc)
{
    if ((f_Pos + inc) <= f_End)
        return;
    if ((f_Pos + inc) > f_Cap)
    {
        size_t minCap = (f_Pos + inc) - f_Beg;
        size_t newCap = f_Cap - f_Beg;
        while (newCap < minCap)
            newCap = (newCap << 1) | 1;
        m_Realloc(newCap);
    }
    f_End = f_Pos + inc;
}

#pragma endregion

#pragma region functions

void SmartWriter::flush(uint8_t*& data, size_t& size)
{
    size = f_End - f_Beg;
    data = mc_NewArray(size);
    if (data) memcpy(data, f_Beg, size);
    m_Reset();
}

void SmartWriter::clear()
{
    memset(f_Beg, 0, f_Cap - f_Beg);
    f_End = f_Beg;
    f_Pos = f_Beg;
}

size_t SmartWriter::getCapacity() const
{
    return f_Cap - f_Beg;
}

size_t SmartWriter::getSize() const
{
    return f_End - f_Beg;
}

size_t SmartWriter::tell() const
{
    return f_Pos - f_Beg;
}

void SmartWriter::seek(size_t pos)
{
    f_Pos = f_Beg + pos;
    f_Valid = f_Pos <= f_End;
}

void SmartWriter::reserve(size_t size)
{
    if ((f_Beg + size) > f_Cap)
        m_Realloc(size);
}

void SmartWriter::shrink()
{
    if (f_End < f_Cap)
        m_Realloc(f_End - f_Beg);
}

#pragma endregion

#pragma region Misc

void SmartWriter::write(const uint8_t* buffer, size_t size)
{
    if (!f_Valid) return;
    m_UpdateSize(size);
    memcpy(f_Pos, buffer, size);
    f_Pos += size;
}

void SmartWriter::writeU8(uint8_t value)
{
    if (!f_Valid) return;
    m_UpdateSize(1);
    *(f_Pos++) = value;
}

void SmartWriter::writeI8(int8_t value)
{
    if (!f_Valid) return;
    m_UpdateSize(1);
    *(f_Pos++) = (uint8_t)value;
}

#pragma endregion

#pragma region UInt16

void SmartWriter::writeU16(uint16_t value, bool big) mc_Write2(uint16_t, writeU16, value, big)
void SmartWriter::writeU16l(uint16_t value) mc_Write(uint16_t, writeU16l, value)
void SmartWriter::writeU16b(uint16_t value) mc_Write(uint16_t, writeU16b, value)

#pragma endregion

#pragma region Int16

void SmartWriter::writeI16(int16_t value, bool big) mc_Write2(int16_t, writeI16, value, big)
void SmartWriter::writeI16l(int16_t value) mc_Write(int16_t, writeI16l, value)
void SmartWriter::writeI16b(int16_t value) mc_Write(int16_t, writeI16b, value)

#pragma endregion

#pragma region UInt32

void SmartWriter::writeU32(uint32_t value, bool big) mc_Write2(uint32_t, writeU32, value, big)
void SmartWriter::writeU32l(uint32_t value) mc_Write(uint32_t, writeU32l, value)
void SmartWriter::writeU32b(uint32_t value) mc_Write(uint32_t, writeU32b, value)

#pragma endregion

#pragma region Int32

void SmartWriter::writeI32(int32_t value, bool big) mc_Write2(int32_t, writeI32, value, big)
void SmartWriter::writeI32l(int32_t value) mc_Write(int32_t, writeI32l, value)
void SmartWriter::writeI32b(int32_t value) mc_Write(int32_t, writeI32b, value)

#pragma endregion

#pragma region UInt64

void SmartWriter::writeU64(uint64_t value, bool big) mc_Write2(uint64_t, writeU64, value, big)
void SmartWriter::writeU64l(uint64_t value) mc_Write(uint64_t, writeU64l, value)
void SmartWriter::writeU64b(uint64_t value) mc_Write(uint64_t, writeU64b, value)

#pragma endregion

#pragma region Int64

void SmartWriter::writeI64(int64_t value, bool big) mc_Write2(int64_t, writeI64, value, big)
void SmartWriter::writeI64l(int64_t value) mc_Write(int64_t, writeI64l, value)
void SmartWriter::writeI64b(int64_t value) mc_Write(int64_t, writeI64b, value)

#pragma endregion