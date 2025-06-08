src=$1
rm -fr $src


echo -e "#include <cstdio>" >>$src #TODO: Remove
echo -e "#include \"rookpp.Parsing.h\"" >>$src
echo -e "" >>$src
echo -e "using namespace rookpp;" >>$src

echo -e "" >>$src
echo -e "Parsing::Parsing() { }" >>$src

#This function moves a pointer to the next non-whitespace character that isn't a minus sign
#This function returns whether or not a minus sign was encountered
echo -e "" >>$src
echo -e "bool gotoFirst(char **ptrptr)" >>$src
echo -e "{" >>$src
echo -e "findSign:" >>$src
echo -e "    //Null" >>$src
echo -e "    if (**ptrptr == 0) return false;" >>$src
echo -e "    //Minus" >>$src
echo -e "    if (**ptrptr == 0x2D) goto findDigit;" >>$src
echo -e "    //Non-whitespace" >>$src
echo -e "    if (**ptrptr > 0x20) return false;" >>$src
echo -e "    //Next" >>$src
echo -e "    (*ptrptr)++;" >>$src
echo -e "    goto findSign;" >>$src
echo -e "" >>$src
echo -e "findDigit:" >>$src
echo -e "    (*ptrptr)++;" >>$src
echo -e "    //Null" >>$src
echo -e "    if (**ptrptr == 0) return true;" >>$src
echo -e "    //Non-whitespace" >>$src
echo -e "    if (**ptrptr > 0x20) return true;" >>$src
echo -e "    //Next" >>$src
echo -e "    goto findDigit;" >>$src
echo -e "}" >>$src

#This function moves a pointer to the end of the string
#This function only returns true if no non-whitespace characters are found
echo -e "" >>$src
echo -e "bool gotoEnd(char **ptrptr)" >>$src
echo -e "{" >>$src
echo -e "loop:" >>$src
echo -e "    if (**ptrptr == 0) return true;" >>$src
echo -e "    if (**ptrptr > 0x20) return false;" >>$src
echo -e "    (*ptrptr)++;" >>$src
echo -e "    goto loop;" >>$src
echo -e "}" >>$src

auto_int_dec_loop() {
    local indent=$1
    local neg=$2
    echo -e "${indent}while(*ptr > 0x20)"
    echo -e "${indent}{"
    echo -e "${indent}    //Shift digits"
    echo -e "${indent}    inc = *result;"
    echo -e "${indent}    for (uint8_t i = 1; i < 10; i++)"
    echo -e "${indent}    {"
    echo -e "${indent}        prev = *result;"
    echo -e "${indent}        *result += inc;"
    echo -e "${indent}        //Check for overflow"
    if [ $neg = 1 ]; then
        echo -e "${indent}        if (*result > prev) return false;"
    else
        echo -e "${indent}        if (*result < prev) return false;"
    fi
    echo -e "${indent}    }"
    echo -e "${indent}    //Check character"
    echo -e "${indent}    if (*ptr >= 0x30 && *ptr <= 0x39)"
    if [ $neg = 1 ]; then
        echo -e "${indent}        *result -= *ptr - 0x30;"
    else
        echo -e "${indent}        *result += *ptr - 0x30;"
    fi
    echo -e "${indent}    else return false;"
    echo -e "${indent}    //Next"
    echo -e "${indent}    ptr++;"
    echo -e "${indent}}"
}

auto_int_dec() {
    local literal=$1
    local signed=$2
    echo -e "    {"
    echo -e "        $literal prev = 0;"
    echo -e "        $literal inc = 0;"
    echo -e "        *result = 0;"
    if [ $signed = 1 ]; then
        echo -e "        if (isNeg)"
        echo -e "        {"
        auto_int_dec_loop "            " 1
        echo -e "        }"
        echo -e "        else"
        echo -e "        {"
        auto_int_dec_loop "            " 0
        echo -e "        }"
    else
        auto_int_dec_loop "        " 0
    fi
    echo -e "        return gotoEnd(&ptr);"
    echo -e "    }"
}

auto_int_hex() {
    local maxDigits=$1
    local signed=$2
    echo -e "        if (*ptr == 0x58 || *ptr == 0x78)"
    echo -e "        {"
    echo -e "            ptr++;"
    if [ $signed = 1 ]; then
        echo -e "            if (isNeg) return false;"
    fi
    echo -e "            uint8_t digit = 0;"
    echo -e "            while(*ptr > 0x20)"
    echo -e "            {"
    echo -e "                //Skip if insigificant zero"
    echo -e "                if (digit == 0 && *ptr == 0x30)"
    echo -e "                    goto nextHex;"
    echo -e "                //Push result"
    echo -e "                if (++digit > $maxDigits) return false;"
    echo -e "                *result <<= 4;"
    echo -e "                //Check character"
    echo -e "                if (*ptr >= 0x30 && *ptr <= 0x39)"
    echo -e "                    *result |= *ptr - 0x30;"
    echo -e "                else if (*ptr >= 0x41 && *ptr <= 0x46)"
    echo -e "                    *result |= (*ptr - 0x41) + 10;"
    echo -e "                else if (*ptr >= 0x61 && *ptr <= 0x66)"
    echo -e "                    *result |= (*ptr - 0x61) + 10;"
    echo -e "                else return false;"
    echo -e "                //Next"
    echo -e "            nextHex:"
    echo -e "                ptr++;"
    echo -e "            }"
    echo -e "            return gotoEnd(&ptr);"
    echo -e "        }"
}

auto_int_bin() {
    local maxDigits=$1
    local signed=$2
    echo -e "        if (*ptr == 0x42 || *ptr == 0x62)"
    echo -e "        {"
    echo -e "            ptr++;"
    if [ $signed = 1 ]; then
        echo -e "            if (isNeg) return false;"
    fi
    echo -e "            uint8_t digit = 0;"
    echo -e "            while(*ptr > 0x20)"
    echo -e "            {"
    echo -e "                //Skip if insigificant zero"
    echo -e "                if (digit == 0 && *ptr == 0x30)"
    echo -e "                    goto nextBin;"
    echo -e "                //Push result"
    echo -e "                if (++digit > $maxDigits) return false;"
    echo -e "                *result <<= 1;"
    echo -e "                //Check character"
    echo -e "                if (*ptr >= 0x30 && *ptr <= 0x31)"
    echo -e "                    *result |= *ptr - 0x30;"
    echo -e "                else return false;"
    echo -e "                //Next"
    echo -e "            nextBin:"
    echo -e "                ptr++;"
    echo -e "            }"
    echo -e "            return gotoEnd(&ptr);"
    echo -e "        }"
}

auto_int() {
    local suffix=$1
    local literal=$2
    local byteCount=$3
    local signed=$4
    echo -e "bool Parsing::tryParse$suffix(const char *str, $literal *result)"
    echo -e "{"
    echo -e "    *result = 0;"
    echo -e "    char *ptr = (char*)str;"
    if [ $signed = 1 ]; then
        echo -e "    bool isNeg = gotoFirst(&ptr);"
    else
        echo -e "    if (gotoFirst(&ptr)) return false;"
    fi
    echo -e "    if (*ptr == 0) return false;"
    echo -e "    if (*ptr == 0x30)"
    echo -e "    {"
    echo -e "        ptr++;"
    echo -e "        //Check if hexadecimal"
    echo "$(auto_int_hex $(expr $byteCount \* 2) $signed)"
    echo -e "        //Check if binary"
    echo "$(auto_int_bin $(expr $byteCount \* 8) $signed)"
    echo -e "        ptr--;"
    echo -e "    }"
    echo -e "    //Parse as decimal"
    echo "$(auto_int_dec "$literal" $signed)"
    echo -e "}"
}

auto_single() {
    echo -e "bool Parsing::tryParseSingle(const char *str, float *result)"
    echo -e "{"
    echo -e "    double rawResult = 0.0;"
    echo -e "    if (!tryParseDouble(str, &rawResult))"
    echo -e "        return false;"
    echo -e "    *result = rawResult;"
    echo -e "    return true;"
    echo -e "}"
}

auto_double_loop() {
    local neg=$1
    #Integer part
    echo -e "    _int$neg:"
    echo -e "        //Integer part"
    echo -e "        if (*ptr <= 0x20) goto _end$neg;"
    echo -e "        if (*ptr == 0x2E) goto _frac$neg;"
    echo -e "        //Shift digits"
    echo -e "        *result *= 10.0;"
    echo -e "        //Check character"
    echo -e "        if (*ptr >= 0x30 && *ptr <= 0x39)"
    if [ $neg = 1 ]; then
        echo -e "            *result -= (double)(*ptr - 0x30);"
    else
        echo -e "            *result += (double)(*ptr - 0x30);"
    fi
    echo -e "        else return false;"
    echo -e "        //Next"
    echo -e "        ptr++;"
    echo -e "        goto _int$neg;"
    #Fractional part
    echo -e "    _frac$neg:"
    echo -e "        //Fractional part"
    echo -e "        ptr++;"
    echo -e "        if (*ptr <= 0x20) goto _end$neg;"
    echo -e "        //Shift multiplier"
    echo -e "        multiplier *= 0.1;"
    echo -e "        //Check character"
    echo -e "        if (*ptr >= 0x30 && *ptr <= 0x39)"
    if [ $neg = 1 ]; then
        echo -e "            *result -= (double)(*ptr - 0x30) * multiplier;"
    else
        echo -e "            *result += (double)(*ptr - 0x30) * multiplier;"
    fi
    echo -e "        else return false;"
    echo -e "        //Next"
    echo -e "        goto _frac$neg;"
    #Return
    echo -e "    _end$neg:"
    echo -e "        //Return"
    echo -e "        return gotoEnd(&ptr);"
}

auto_double() {
    echo -e "bool Parsing::tryParseDouble(const char *str, double *result)"
    echo -e "{"
    echo -e "    *result = 0.0;"
    echo -e "    char *ptr = (char*)str;"
    echo -e "    double multiplier = 1.0;"
    echo -e "    if (gotoFirst(&ptr))"
    echo -e "    {"
    echo "$(auto_double_loop 1)"
    echo -e "    }"
    echo -e "    else"
    echo -e "    {"
    echo "$(auto_double_loop 0)"
    echo -e "    }"
    echo -e "}"
}

echo -e "" >>$src
echo "$(auto_int "UInt8" "uint8_t" 1 0)" >>$src
echo -e "" >>$src
echo "$(auto_int "Int8" "int8_t" 1 1)" >>$src
echo -e "" >>$src
echo "$(auto_int "UInt16" "uint16_t" 2 0)" >>$src
echo -e "" >>$src
echo "$(auto_int "Int16" "int16_t" 2 1)" >>$src
echo -e "" >>$src
echo "$(auto_int "UInt32" "uint32_t" 4 0)" >>$src
echo -e "" >>$src
echo "$(auto_int "Int32" "int32_t" 4 1)" >>$src
echo -e "" >>$src
echo "$(auto_int "UInt64" "uint64_t" 8 0)" >>$src
echo -e "" >>$src
echo "$(auto_int "Int64" "int64_t" 8 1)" >>$src

echo -e "" >>$src
echo "$(auto_single)" >>$src
echo -e "" >>$src
echo "$(auto_double)" >>$src