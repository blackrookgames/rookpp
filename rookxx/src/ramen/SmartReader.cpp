#include "ramen/SmartReader.h"

#include <cstring>

#include "ramen/DataReader.h"

#pragma region macros

#define mc_Read(type, func) \
{ \
    f_Valid = (f_Pos + sizeof(type)) <= f_End; \
    if (f_Valid) return DataReader::func(f_Pos); \
    f_Pos += sizeof(type); \
    return 0; \
}

#define mc_Read2(type, func, big) \
{ \
    f_Valid = (f_Pos + sizeof(type)) <= f_End; \
    if (f_Valid) return DataReader::func(f_Pos, big); \
    f_Pos += sizeof(type); \
    return 0; \
}

#pragma endregion

using namespace rookxx::ramen;

#pragma region init

SmartReader::SmartReader(const uint8_t* beg, const uint8_t* end)
{
    f_Beg = beg;
    f_End = end;
    f_Pos = f_Beg;
    f_Valid = f_Pos <= f_End;
}

SmartReader::SmartReader(const uint8_t* beg, size_t size) :
    SmartReader(beg, beg + size)
{ }

SmartReader::~SmartReader()
{ }

#pragma endregion

#pragma region properties

bool SmartReader::valid() const { return f_Valid; }

const uint8_t* SmartReader::beg() const { return f_Beg; }

const uint8_t* SmartReader::end() const { return f_End; }

const uint8_t* SmartReader::pos() const { return f_Pos; }

#pragma endregion

#pragma region functions

size_t SmartReader::getSize() const
{
    return f_End - f_Beg;
}

size_t SmartReader::tell() const
{
    return f_Pos - f_Beg;
}

void SmartReader::seek(size_t pos)
{
    f_Pos = f_Beg + pos;
    f_Valid = f_Pos <= f_End;
}

#pragma endregion

#pragma region Misc

void SmartReader::read(uint8_t* buffer, size_t size)
{
    const uint8_t* prev = f_Pos;
    f_Pos += size;
    f_Valid = f_Pos <= f_End;
    if (!f_Valid) return;
    memcpy(buffer, prev, size);
}

uint8_t SmartReader::readU8()
{
    f_Valid = f_Pos < f_End;
    if (f_Valid) return *(f_Pos++);
    f_Pos++;
    return 0;
}

int8_t SmartReader::readI8()
{
    f_Valid = f_Pos < f_End;
    if (f_Valid) return (int8_t)*(f_Pos++);
    f_Pos++;
    return 0;
}

#pragma endregion

#pragma region UInt16

uint16_t SmartReader::readU16(bool big) mc_Read2(uint16_t, readU16, big)
uint16_t SmartReader::readU16l() mc_Read(uint16_t, readU16l)
uint16_t SmartReader::readU16b() mc_Read(uint16_t, readU16b)

#pragma endregion

#pragma region Int16

int16_t SmartReader::readI16(bool big) mc_Read2(int16_t, readI16, big)
int16_t SmartReader::readI16l() mc_Read(int16_t, readI16l)
int16_t SmartReader::readI16b() mc_Read(int16_t, readI16b)

#pragma endregion

#pragma region UInt32

uint32_t SmartReader::readU32(bool big) mc_Read2(uint32_t, readU32, big)
uint32_t SmartReader::readU32l() mc_Read(uint32_t, readU32l)
uint32_t SmartReader::readU32b() mc_Read(uint32_t, readU32b)

#pragma endregion

#pragma region Int32

int32_t SmartReader::readI32(bool big) mc_Read2(int32_t, readI32, big)
int32_t SmartReader::readI32l() mc_Read(int32_t, readI32l)
int32_t SmartReader::readI32b() mc_Read(int32_t, readI32b)

#pragma endregion

#pragma region UInt64

uint64_t SmartReader::readU64(bool big) mc_Read2(uint64_t, readU64, big)
uint64_t SmartReader::readU64l() mc_Read(uint64_t, readU64l)
uint64_t SmartReader::readU64b() mc_Read(uint64_t, readU64b)

#pragma endregion

#pragma region Int64

int64_t SmartReader::readI64(bool big) mc_Read2(int64_t, readI64, big)
int64_t SmartReader::readI64l() mc_Read(int64_t, readI64l)
int64_t SmartReader::readI64b() mc_Read(int64_t, readI64b)

#pragma endregion