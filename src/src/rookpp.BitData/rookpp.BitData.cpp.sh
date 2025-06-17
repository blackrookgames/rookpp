src=$1
rm -fr $src

echo -e "#include \"rookpp.BitData.h\"" >>$src
echo -e "" >>$src
echo -e "rookpp::BitData::BitData() { }" >>$src
echo -e "" >>$src

autoRead() {
    local literal="$1"
    local uliteral="$2"
    local byteCount=$3
    local bigEndian=$4
    #Declare
    if [ ! -z "$uliteral" ]; then
        echo -e -n "\t$uliteral value = 0;" >>$src
    else
        echo -e -n "\t$literal value = 0;" >>$src
    fi
    #Pointer
    if [ $bigEndian = 1 ]; then
        echo -e "\tuint8_t *ptr = (uint8_t*)data;" >>$src
    else
        echo -e "\tuint8_t *ptr = (uint8_t*)data + $(expr $byteCount - 1);" >>$src
    fi
    for i in $(seq 1 $byteCount); do
        #Or
        if [ $bigEndian = 1 ]; then
            echo -e -n "\t\tvalue |= *(ptr++);" >>$src
        else
            echo -e -n "\t\tvalue |= *(ptr--);" >>$src
        fi
        #Shift
        if [ ! $i = $byteCount ]; then
            echo -e -n " value <<= 8;" >>$src
        fi
        echo -e "" >>$src
    done
    #Return
    if [ -z "$uliteral" ]; then
        echo -e "\treturn value;" >>$src
    else
        echo -e "\treturn ($literal)value;" >>$src
    fi
}

autoWrite() {
    local literal="$1"
    local uliteral="$2"
    local byteCount=$3
    local bigEndian=$4
    #Declare
    local valueVar="value"
    if [ ! -z "$uliteral" ]; then
        valueVar="uvalue"
        echo -e "\t$uliteral uvalue = ($uliteral)value;" >>$src
    fi
    #for header
    if [ $bigEndian = 1 ]; then
        echo -e "\tuint8_t *ptr = (uint8_t*)data + $(expr $byteCount - 1);" >>$src
    else
        echo -e "\tuint8_t *ptr = (uint8_t*)data;" >>$src
    fi
    echo -e "\tfor (uint8_t i = 0; i < ${byteCount}; i++)" >>$src
    echo -e "\t{" >>$src
    #for body
    if [ $bigEndian = 1 ]; then
        echo -e "\t\t*(ptr--) = (uint8_t)($valueVar & 0xFF);" >>$src
    else
        echo -e "\t\t*(ptr++) = (uint8_t)($valueVar & 0xFF);" >>$src
    fi
    echo -e "\t\t$valueVar >>= 8;" >>$src
    #for footer
    echo -e "\t}" >>$src
}

auto() {
    local suffix="$1"
    local literal="$2"
    local uliteral="$3"
    local byteCount=$4
    #Read
    echo -e "$literal rookpp::BitData::read${suffix}(void *data, bool bigEndian)" >>$src
    echo -e "{" >>$src
    echo -e "\tif(bigEndian) return read${suffix}B(data);" >>$src
    echo -e "\telse return read${suffix}L(data);" >>$src
    echo -e "}" >>$src
    echo -e "" >>$src
    echo -e "$literal rookpp::BitData::read${suffix}L(void *data)" >>$src
    echo -e "{" >>$src
    autoRead "$literal" "$uliteral" "$byteCount" 0
    echo -e "}" >>$src
    echo -e "" >>$src
    echo -e "$literal rookpp::BitData::read${suffix}B(void *data)" >>$src
    echo -e "{" >>$src
    autoRead "$literal" "$uliteral" "$byteCount" 1
    echo -e "}" >>$src
    echo -e "" >>$src
    #Write
    echo -e "void rookpp::BitData::write${suffix}(void *data, bool bigEndian, $literal value)" >>$src
    echo -e "{" >>$src
    echo -e "\tif(bigEndian) write${suffix}B(data, value);" >>$src
    echo -e "\telse write${suffix}L(data, value);" >>$src
    echo -e "}" >>$src
    echo -e "" >>$src
    echo -e "void rookpp::BitData::write${suffix}L(void *data, $literal value)" >>$src
    echo -e "{" >>$src
    autoWrite "$literal" "$uliteral" "$byteCount" 0
    echo -e "}" >>$src
    echo -e "" >>$src
    echo -e "void rookpp::BitData::write${suffix}B(void *data, $literal value)" >>$src
    echo -e "{" >>$src
    autoWrite "$literal" "$uliteral" "$byteCount" 1
    echo -e "}" >>$src
}
auto "UInt16" "uint16_t" "" 2
echo -e "" >>$src
auto "Int16" "int16_t" "uint16_t" 2
echo -e "" >>$src
auto "UInt32" "uint32_t" "" 4
echo -e "" >>$src
auto "Int32" "int32_t" "uint32_t" 4
echo -e "" >>$src
auto "UInt64" "uint64_t" "" 8
echo -e "" >>$src
auto "Int64" "int64_t" "uint64_t" 8