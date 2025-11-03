#include "bitman/BitPtr.h"

using namespace rookxx::bitman;

#pragma region init

BitPtr::BitPtr()
{
    f_Pnt = new BitPnt();
}

BitPtr::BitPtr(void* loc, uint8_t offset)
{
    f_Pnt = new BitPnt(loc, offset);
}

BitPtr::BitPtr(const BitPtr& src)
{
    f_Pnt = new BitPnt(*src.f_Pnt);
}

BitPtr::BitPtr(BitPtr&& src)
{
    f_Pnt = src.f_Pnt;
    src.f_Pnt = nullptr;
}

BitPtr::~BitPtr()
{
    if (f_Pnt) delete f_Pnt;
}

BitPtr& BitPtr::operator=(const BitPtr& src)
{
    if (this != &src)
    {
        *f_Pnt = *src.f_Pnt;
    }
    return *this;
}

BitPtr& BitPtr::operator=(BitPtr&& src)
{
    if (this != &src)
    {
        if (f_Pnt) delete f_Pnt;
        f_Pnt = src.f_Pnt;
        src.f_Pnt = nullptr;
    }
    return *this;
}

#pragma endregion

#pragma region helper

const uint8_t* BitPtr::p_Loc() const { return f_Pnt->f_Loc; }

uint8_t BitPtr::p_Mask() const { return f_Pnt->f_Mask; }

#pragma endregion

#pragma region operator

BitPnt& BitPtr::operator*() { return *f_Pnt; }

const BitPnt& BitPtr::operator*() const { return *f_Pnt; }

BitPtr& BitPtr::operator++()
{
    f_Pnt->m_Inc();
    return *this;
}

BitPtr BitPtr::operator++(int)
{
    BitPtr tmp(*this);
    f_Pnt->m_Inc();
    return tmp;
}

BitPtr& BitPtr::operator--()
{
    f_Pnt->m_Dec();
    return *this;
}

BitPtr BitPtr::operator--(int)
{
    BitPtr tmp(*this);
    f_Pnt->m_Dec();
    return tmp;
}

#pragma endregion