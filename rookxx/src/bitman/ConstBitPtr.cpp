#include "bitman/ConstBitPtr.h"

using namespace rookxx::bitman;

#pragma region init

ConstBitPtr::ConstBitPtr()
{
    f_Pnt = new ConstBitPnt();
}

ConstBitPtr::ConstBitPtr(const void* loc, uint8_t offset)
{
    f_Pnt = new ConstBitPnt(loc, offset);
}

ConstBitPtr::ConstBitPtr(const ConstBitPtr& src)
{
    f_Pnt = new ConstBitPnt(*src.f_Pnt);
}

ConstBitPtr::ConstBitPtr(ConstBitPtr&& src)
{
    f_Pnt = src.f_Pnt;
    src.f_Pnt = nullptr;
}

ConstBitPtr::~ConstBitPtr()
{
    if (f_Pnt) delete f_Pnt;
}

ConstBitPtr& ConstBitPtr::operator=(const ConstBitPtr& src)
{
    if (this != &src)
    {
        *f_Pnt = *src.f_Pnt;
    }
    return *this;
}

ConstBitPtr& ConstBitPtr::operator=(ConstBitPtr&& src)
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

const uint8_t* ConstBitPtr::p_Loc() const { return f_Pnt->f_Loc; }

uint8_t ConstBitPtr::p_Mask() const { return f_Pnt->f_Mask; }

#pragma endregion

#pragma region operator

ConstBitPnt& ConstBitPtr::operator*() { return *f_Pnt; }

const ConstBitPnt& ConstBitPtr::operator*() const { return *f_Pnt; }

ConstBitPtr& ConstBitPtr::operator++()
{
    f_Pnt->m_Inc();
    return *this;
}

ConstBitPtr ConstBitPtr::operator++(int)
{
    ConstBitPtr tmp(*this);
    f_Pnt->m_Inc();
    return tmp;
}

ConstBitPtr& ConstBitPtr::operator--()
{
    f_Pnt->m_Dec();
    return *this;
}

ConstBitPtr ConstBitPtr::operator--(int)
{
    ConstBitPtr tmp(*this);
    f_Pnt->m_Dec();
    return tmp;
}

#pragma endregion