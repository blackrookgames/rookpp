#include "ramen/DataWriter.h"

#pragma region macros

#define mc_Write(ptr, value, big, bfunc, lfunc) \
    if (big) bfunc(ptr, value); else lfunc(ptr, value);
#define mc_WriteMask(ptr, value) \
    *((ptr)++) = (uint8_t)((value) & 0xFF);
#define mc_WriteShift(ptr, value, shift) \
    *((ptr)++) = (uint8_t)(((value) >> (shift)) & 0xFF);
#define mc_Write16L(ptr, value) \
    mc_WriteMask(ptr, value) mc_WriteShift(ptr, value, 8)
#define mc_Write16B(ptr, value) \
    mc_WriteShift(ptr, value, 8) mc_WriteMask(ptr, value)
#define mc_Write32L(ptr, value) \
    mc_WriteMask(ptr, value) mc_WriteShift(ptr, value, 8) \
    mc_WriteShift(ptr, value, 16) mc_WriteShift(ptr, value, 24)
#define mc_Write32B(ptr, value) \
    mc_WriteShift(ptr, value, 24) mc_WriteShift(ptr, value, 16) \
    mc_WriteShift(ptr, value, 8) mc_WriteMask(ptr, value)
#define mc_Write64L(ptr, value) \
    mc_WriteMask(ptr, value) mc_WriteShift(ptr, value, 8) \
    mc_WriteShift(ptr, value, 16) mc_WriteShift(ptr, value, 24) \
    mc_WriteShift(ptr, value, 32) mc_WriteShift(ptr, value, 40) \
    mc_WriteShift(ptr, value, 48) mc_WriteShift(ptr, value, 56)
#define mc_Write64B(ptr, value) \
    mc_WriteShift(ptr, value, 56) mc_WriteShift(ptr, value, 48) \
    mc_WriteShift(ptr, value, 40) mc_WriteShift(ptr, value, 32) \
    mc_WriteShift(ptr, value, 24) mc_WriteShift(ptr, value, 16) \
    mc_WriteShift(ptr, value, 8) mc_WriteMask(ptr, value)

#pragma endregion

using namespace rookxx::ramen;

#pragma region UInt16

void DataWriter::writeU16(uint8_t*& ptr, uint16_t value, bool big) { mc_Write(ptr, value, big, writeU16b, writeU16l) }
void DataWriter::writeU16l(uint8_t*& ptr, uint16_t value) { mc_Write16L(ptr, value) }
void DataWriter::writeU16b(uint8_t*& ptr, uint16_t value) { mc_Write16B(ptr, value) }

#pragma endregion

#pragma region Int16

void DataWriter::writeI16(uint8_t*& ptr, int16_t value, bool big) { mc_Write(ptr, value, big, writeI16b, writeI16l) }
void DataWriter::writeI16l(uint8_t*& ptr, int16_t value) { mc_Write16L(ptr, value) }
void DataWriter::writeI16b(uint8_t*& ptr, int16_t value) { mc_Write16B(ptr, value) }

#pragma endregion

#pragma region UInt32

void DataWriter::writeU32(uint8_t*& ptr, uint32_t value, bool big) { mc_Write(ptr, value, big, writeU32b, writeU32l) }
void DataWriter::writeU32l(uint8_t*& ptr, uint32_t value) { mc_Write32L(ptr, value) }
void DataWriter::writeU32b(uint8_t*& ptr, uint32_t value) { mc_Write32B(ptr, value) }

#pragma endregion

#pragma region Int32

void DataWriter::writeI32(uint8_t*& ptr, int32_t value, bool big) { mc_Write(ptr, value, big, writeI32b, writeI32l) }
void DataWriter::writeI32l(uint8_t*& ptr, int32_t value) { mc_Write32L(ptr, value) }
void DataWriter::writeI32b(uint8_t*& ptr, int32_t value) { mc_Write32B(ptr, value) }

#pragma endregion

#pragma region UInt64

void DataWriter::writeU64(uint8_t*& ptr, uint64_t value, bool big) { mc_Write(ptr, value, big, writeU64b, writeU64l) }
void DataWriter::writeU64l(uint8_t*& ptr, uint64_t value) { mc_Write64L(ptr, value) }
void DataWriter::writeU64b(uint8_t*& ptr, uint64_t value) { mc_Write64B(ptr, value) }

#pragma endregion

#pragma region Int64

void DataWriter::writeI64(uint8_t*& ptr, int64_t value, bool big) { mc_Write(ptr, value, big, writeI64b, writeI64l) }
void DataWriter::writeI64l(uint8_t*& ptr, int64_t value) { mc_Write64L(ptr, value) }
void DataWriter::writeI64b(uint8_t*& ptr, int64_t value) { mc_Write64B(ptr, value) }

#pragma endregion
