#include "ramen/DataReader.h"

#pragma region macros

#define mc_Read(ptr, big, bfunc, lfunc) \
    if (big) return bfunc(ptr); else return lfunc(ptr);
#define mc_ReadSetMask(type, ptr, value) \
    type value = *((ptr)++);
#define mc_ReadAddMask(ptr, value) \
    value |= *((ptr)++);
#define mc_ReadSetShift(type, ptr, value, shift) \
    type value = ((type)*((ptr)++)) << (shift);
#define mc_ReadAddShift(type, ptr, value, shift) \
    value |= ((type)*((ptr)++)) << (shift);
#define mc_Read16L(type, ptr, value) \
    mc_ReadSetMask(type, ptr, value) mc_ReadAddShift(type, ptr, value, 8) \
    return value;
#define mc_Read16B(type, ptr, value) \
    mc_ReadSetShift(type, ptr, value, 8) mc_ReadAddMask(ptr, value) \
    return value;
#define mc_Read32L(type, ptr, value) \
    mc_ReadSetMask(type, ptr, value) mc_ReadAddShift(type, ptr, value, 8) \
    mc_ReadAddShift(type, ptr, value, 16) mc_ReadAddShift(type, ptr, value, 24) \
    return value;
#define mc_Read32B(type, ptr, value) \
    mc_ReadSetShift(type, ptr, value, 24) mc_ReadAddShift(type, ptr, value, 16) \
    mc_ReadAddShift(type, ptr, value, 8) mc_ReadAddMask(ptr, value) \
    return value;
#define mc_Read64L(type, ptr, value) \
    mc_ReadSetMask(type, ptr, value) mc_ReadAddShift(type, ptr, value, 8) \
    mc_ReadAddShift(type, ptr, value, 16) mc_ReadAddShift(type, ptr, value, 24) \
    mc_ReadAddShift(type, ptr, value, 32) mc_ReadAddShift(type, ptr, value, 40) \
    mc_ReadAddShift(type, ptr, value, 48) mc_ReadAddShift(type, ptr, value, 56) \
    return value;
#define mc_Read64B(type, ptr, value) \
    mc_ReadSetShift(type, ptr, value, 56) mc_ReadAddShift(type, ptr, value, 48) \
    mc_ReadAddShift(type, ptr, value, 40) mc_ReadAddShift(type, ptr, value, 32) \
    mc_ReadAddShift(type, ptr, value, 24) mc_ReadAddShift(type, ptr, value, 16) \
    mc_ReadAddShift(type, ptr, value, 8) mc_ReadAddMask(ptr, value) \
    return value;

#pragma endregion

using namespace rookxx::ramen;

#pragma region UInt16

uint16_t DataReader::readU16(const uint8_t*& ptr, bool big) { mc_Read(ptr, big, readU16b, readU16l) }
uint16_t DataReader::readU16l(const uint8_t*& ptr) { mc_Read16L(uint16_t, ptr, value) }
uint16_t DataReader::readU16b(const uint8_t*& ptr) { mc_Read16B(uint16_t, ptr, value) }

#pragma endregion

#pragma region Int16

int16_t DataReader::readI16(const uint8_t*& ptr, bool big) { mc_Read(ptr, big, readI16b, readI16l) }
int16_t DataReader::readI16l(const uint8_t*& ptr) { mc_Read16L(int16_t, ptr, value) }
int16_t DataReader::readI16b(const uint8_t*& ptr) { mc_Read16B(int16_t, ptr, value) }

#pragma endregion

#pragma region UInt32

uint32_t DataReader::readU32(const uint8_t*& ptr, bool big) { mc_Read(ptr, big, readU32b, readU32l) }
uint32_t DataReader::readU32l(const uint8_t*& ptr) { mc_Read32L(uint32_t, ptr, value) }
uint32_t DataReader::readU32b(const uint8_t*& ptr) { mc_Read32B(uint32_t, ptr, value) }

#pragma endregion

#pragma region Int32

int32_t DataReader::readI32(const uint8_t*& ptr, bool big) { mc_Read(ptr, big, readI32b, readI32l) }
int32_t DataReader::readI32l(const uint8_t*& ptr) { mc_Read32L(int32_t, ptr, value) }
int32_t DataReader::readI32b(const uint8_t*& ptr) { mc_Read32B(int32_t, ptr, value) }

#pragma endregion

#pragma region UInt64

uint64_t DataReader::readU64(const uint8_t*& ptr, bool big) { mc_Read(ptr, big, readU64b, readU64l) }
uint64_t DataReader::readU64l(const uint8_t*& ptr) { mc_Read64L(uint64_t, ptr, value) }
uint64_t DataReader::readU64b(const uint8_t*& ptr) { mc_Read64B(uint64_t, ptr, value) }

#pragma endregion

#pragma region Int64

int64_t DataReader::readI64(const uint8_t*& ptr, bool big) { mc_Read(ptr, big, readI64b, readI64l) }
int64_t DataReader::readI64l(const uint8_t*& ptr) { mc_Read64L(int64_t, ptr, value) }
int64_t DataReader::readI64b(const uint8_t*& ptr) { mc_Read64B(int64_t, ptr, value) }

#pragma endregion
