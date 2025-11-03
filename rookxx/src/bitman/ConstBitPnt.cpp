#include "bitman/ConstBitPnt.h"

#define mc_MSB 0b10000000
#define mc_LSB 0b00000001
#define mc_Value ((*f_Loc & f_Mask) != 0)

using namespace rookxx::bitman;

#pragma region init

ConstBitPnt::ConstBitPnt()
{
    f_Loc = nullptr;
    f_Mask = mc_MSB;
    f_Value = false;
}

ConstBitPnt::ConstBitPnt(const void* loc, uint8_t offset)
{
    f_Loc = (uint8_t*)loc + ((offset & 0b11111000) >> 3);
    f_Mask = mc_MSB >> (offset & 0b00000111);
    f_Value = mc_Value;
}

ConstBitPnt::ConstBitPnt(const ConstBitPnt& src)
{
    f_Loc = src.f_Loc;
    f_Mask = src.f_Mask;
    f_Value = src.f_Value;
}

ConstBitPnt::~ConstBitPnt() { }

ConstBitPnt& ConstBitPnt::operator=(const ConstBitPnt& src)
{
    if (this != &src)
    {
        f_Loc = src.f_Loc;
        f_Mask = src.f_Mask;
        f_Value = src.f_Value;
    }
    return *this;
}

#pragma endregion

#pragma region operators

ConstBitPnt::operator bool() const { return f_Value; }

#pragma endregion

#pragma region helper

void ConstBitPnt::m_Inc()
{
    if (f_Mask != mc_LSB) f_Mask >>= 1;
    else { ++f_Loc; f_Mask = mc_MSB; }
    f_Value = mc_Value;
}

void ConstBitPnt::m_Dec()
{
    if (f_Mask != mc_MSB) f_Mask <<= 1;
    else { --f_Loc; f_Mask = mc_LSB; }
    f_Value = mc_Value;
}

#pragma endregion