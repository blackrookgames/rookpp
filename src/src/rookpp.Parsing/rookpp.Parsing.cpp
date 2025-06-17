#include <cstdio>
#include "rookpp.Parsing.h"

using namespace rookpp;

Parsing::Parsing() { }

bool gotoFirst(char **ptrptr)
{
findSign:
    //Null
    if (**ptrptr == 0) return false;
    //Minus
    if (**ptrptr == 0x2D) goto findDigit;
    //Non-whitespace
    if (**ptrptr > 0x20) return false;
    //Next
    (*ptrptr)++;
    goto findSign;

findDigit:
    (*ptrptr)++;
    //Null
    if (**ptrptr == 0) return true;
    //Non-whitespace
    if (**ptrptr > 0x20) return true;
    //Next
    goto findDigit;
}

bool gotoEnd(char **ptrptr)
{
loop:
    if (**ptrptr == 0) return true;
    if (**ptrptr > 0x20) return false;
    (*ptrptr)++;
    goto loop;
}

bool Parsing::tryParseUInt8(const char *str, uint8_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    if (gotoFirst(&ptr)) return false;
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 2) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 8) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        uint8_t prev = 0;
        uint8_t inc = 0;
        *result = 0;
        while(*ptr > 0x20)
        {
            //Shift digits
            inc = *result;
            for (uint8_t i = 1; i < 10; i++)
            {
                prev = *result;
                *result += inc;
                //Check for overflow
                if (*result < prev) return false;
            }
            //Check character
            if (*ptr >= 0x30 && *ptr <= 0x39)
                *result += *ptr - 0x30;
            else return false;
            //Next
            ptr++;
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseInt8(const char *str, int8_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    bool isNeg = gotoFirst(&ptr);
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 2) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 8) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        int8_t prev = 0;
        int8_t inc = 0;
        *result = 0;
        if (isNeg)
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result > prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result -= *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        else
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result < prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result += *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseUInt16(const char *str, uint16_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    if (gotoFirst(&ptr)) return false;
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 4) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 16) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        uint16_t prev = 0;
        uint16_t inc = 0;
        *result = 0;
        while(*ptr > 0x20)
        {
            //Shift digits
            inc = *result;
            for (uint8_t i = 1; i < 10; i++)
            {
                prev = *result;
                *result += inc;
                //Check for overflow
                if (*result < prev) return false;
            }
            //Check character
            if (*ptr >= 0x30 && *ptr <= 0x39)
                *result += *ptr - 0x30;
            else return false;
            //Next
            ptr++;
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseInt16(const char *str, int16_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    bool isNeg = gotoFirst(&ptr);
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 4) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 16) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        int16_t prev = 0;
        int16_t inc = 0;
        *result = 0;
        if (isNeg)
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result > prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result -= *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        else
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result < prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result += *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseUInt32(const char *str, uint32_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    if (gotoFirst(&ptr)) return false;
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 8) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 32) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        uint32_t prev = 0;
        uint32_t inc = 0;
        *result = 0;
        while(*ptr > 0x20)
        {
            //Shift digits
            inc = *result;
            for (uint8_t i = 1; i < 10; i++)
            {
                prev = *result;
                *result += inc;
                //Check for overflow
                if (*result < prev) return false;
            }
            //Check character
            if (*ptr >= 0x30 && *ptr <= 0x39)
                *result += *ptr - 0x30;
            else return false;
            //Next
            ptr++;
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseInt32(const char *str, int32_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    bool isNeg = gotoFirst(&ptr);
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 8) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 32) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        int32_t prev = 0;
        int32_t inc = 0;
        *result = 0;
        if (isNeg)
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result > prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result -= *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        else
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result < prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result += *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseUInt64(const char *str, uint64_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    if (gotoFirst(&ptr)) return false;
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 16) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 64) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        uint64_t prev = 0;
        uint64_t inc = 0;
        *result = 0;
        while(*ptr > 0x20)
        {
            //Shift digits
            inc = *result;
            for (uint8_t i = 1; i < 10; i++)
            {
                prev = *result;
                *result += inc;
                //Check for overflow
                if (*result < prev) return false;
            }
            //Check character
            if (*ptr >= 0x30 && *ptr <= 0x39)
                *result += *ptr - 0x30;
            else return false;
            //Next
            ptr++;
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseInt64(const char *str, int64_t *result)
{
    *result = 0;
    char *ptr = (char*)str;
    bool isNeg = gotoFirst(&ptr);
    if (*ptr == 0) return false;
    if (*ptr == 0x30)
    {
        ptr++;
        //Check if hexadecimal
        if (*ptr == 0x58 || *ptr == 0x78)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextHex;
                //Push result
                if (++digit > 16) return false;
                *result <<= 4;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result |= *ptr - 0x30;
                else if (*ptr >= 0x41 && *ptr <= 0x46)
                    *result |= (*ptr - 0x41) + 10;
                else if (*ptr >= 0x61 && *ptr <= 0x66)
                    *result |= (*ptr - 0x61) + 10;
                else return false;
                //Next
            nextHex:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        //Check if binary
        if (*ptr == 0x42 || *ptr == 0x62)
        {
            ptr++;
            if (isNeg) return false;
            uint8_t digit = 0;
            while(*ptr > 0x20)
            {
                //Skip if insigificant zero
                if (digit == 0 && *ptr == 0x30)
                    goto nextBin;
                //Push result
                if (++digit > 64) return false;
                *result <<= 1;
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x31)
                    *result |= *ptr - 0x30;
                else return false;
                //Next
            nextBin:
                ptr++;
            }
            return gotoEnd(&ptr);
        }
        ptr--;
    }
    //Parse as decimal
    {
        int64_t prev = 0;
        int64_t inc = 0;
        *result = 0;
        if (isNeg)
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result > prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result -= *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        else
        {
            while(*ptr > 0x20)
            {
                //Shift digits
                inc = *result;
                for (uint8_t i = 1; i < 10; i++)
                {
                    prev = *result;
                    *result += inc;
                    //Check for overflow
                    if (*result < prev) return false;
                }
                //Check character
                if (*ptr >= 0x30 && *ptr <= 0x39)
                    *result += *ptr - 0x30;
                else return false;
                //Next
                ptr++;
            }
        }
        return gotoEnd(&ptr);
    }
}

bool Parsing::tryParseSingle(const char *str, float *result)
{
    double rawResult = 0.0;
    if (!tryParseDouble(str, &rawResult))
        return false;
    *result = rawResult;
    return true;
}

bool Parsing::tryParseDouble(const char *str, double *result)
{
    *result = 0.0;
    char *ptr = (char*)str;
    double multiplier = 1.0;
    if (gotoFirst(&ptr))
    {
    _int1:
        //Integer part
        if (*ptr <= 0x20) goto _end1;
        if (*ptr == 0x2E) goto _frac1;
        //Shift digits
        *result *= 10.0;
        //Check character
        if (*ptr >= 0x30 && *ptr <= 0x39)
            *result -= (double)(*ptr - 0x30);
        else return false;
        //Next
        ptr++;
        goto _int1;
    _frac1:
        //Fractional part
        ptr++;
        if (*ptr <= 0x20) goto _end1;
        //Shift multiplier
        multiplier *= 0.1;
        //Check character
        if (*ptr >= 0x30 && *ptr <= 0x39)
            *result -= (double)(*ptr - 0x30) * multiplier;
        else return false;
        //Next
        goto _frac1;
    _end1:
        //Return
        return gotoEnd(&ptr);
    }
    else
    {
    _int0:
        //Integer part
        if (*ptr <= 0x20) goto _end0;
        if (*ptr == 0x2E) goto _frac0;
        //Shift digits
        *result *= 10.0;
        //Check character
        if (*ptr >= 0x30 && *ptr <= 0x39)
            *result += (double)(*ptr - 0x30);
        else return false;
        //Next
        ptr++;
        goto _int0;
    _frac0:
        //Fractional part
        ptr++;
        if (*ptr <= 0x20) goto _end0;
        //Shift multiplier
        multiplier *= 0.1;
        //Check character
        if (*ptr >= 0x30 && *ptr <= 0x39)
            *result += (double)(*ptr - 0x30) * multiplier;
        else return false;
        //Next
        goto _frac0;
    _end0:
        //Return
        return gotoEnd(&ptr);
    }
}
