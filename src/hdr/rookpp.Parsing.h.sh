src=$1
rm -fr $src

auto() {
    local indent=$1
    local suffix=$2
    local literal=$3
    local aa=$4
    local desc=$5
    local float=$6
    echo -e "${indent}/// @brief Attempts to parse $aa $desc from the specified string"
    echo -e "${indent}/// @param str String to parse"
    echo -e "${indent}/// @param result Resulting $desc"
    echo -e "${indent}/// @return Whether or not successful"
    if [ $float = 1 ]; then
        echo -e "${indent}/// @note This function does not check for overflow"
    else
        echo -e "${indent}/// @note This function also supports hexadecimal and binary notation"
    fi
    echo -e "${indent}public: static bool tryParse$suffix(const char *str, $literal *result);"
}

echo -e "#include <cstdint>" >>$src
echo -e "" >>$src
echo -e "#pragma once" >>$src
echo -e "#ifndef __ROOKPP_PARSING_H__" >>$src
echo -e "#define __ROOKPP_PARSING_H__" >>$src
echo -e "namespace rookpp" >>$src
echo -e "{" >>$src
echo -e "\t/// @brief Utility for parsing character strings into other value types" >>$src
echo -e "\tclass Parsing" >>$src
echo -e "\t{" >>$src
echo -e "\t\t/// @brief Dummy constructor to prevent instances of Parsing" >>$src
echo -e "\t\tprivate: Parsing();" >>$src

echo -e "\t\t" >>$src
echo "$(auto "\t\t" "UInt8" "uint8_t" "an" "8-bit unsigned integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "Int8" "int8_t" "an" "8-bit signed integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "UInt16" "uint16_t" "a" "16-bit unsigned integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "Int16" "int16_t" "a" "16-bit signed integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "UInt32" "uint32_t" "a" "32-bit unsigned integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "Int32" "int32_t" "a" "32-bit signed integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "UInt64" "uint64_t" "a" "64-bit unsigned integer" 0)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "Int64" "int64_t" "a" "64-bit signed integer" 0)" >>$src

echo -e "\t\t" >>$src
echo "$(auto "\t\t" "Single" "float" "a" "single-precision floating-point" 1)" >>$src
echo -e "\t\t" >>$src
echo "$(auto "\t\t" "Double" "double" "a" "double-precision floating-point" 1)" >>$src

echo -e "\t};" >>$src
echo -e "}" >>$src
echo -e "#endif" >>$src
