src=$1
rm -fr $src

echo -e "#include <cstdint>" >>$src
echo -e "" >>$src
echo -e "#pragma once" >>$src
echo -e "#ifndef __ROOKPP_BITCONVERTER_H__" >>$src
echo -e "#define __ROOKPP_BITCONVERTER_H__" >>$src
echo -e "namespace rookpp" >>$src
echo -e "{" >>$src
echo -e "\t/// @brief Utility for converting bit data" >>$src
echo -e "\tclass BitData" >>$src
echo -e "\t{" >>$src
echo -e "\t\t/// @brief Dummy constructor to prevent instances of BitData" >>$src
echo -e "\t\tprivate: BitData();" >>$src
echo -e "" >>$src

auto() {
    local suffix="$1"
    local literal="$2"
    local desc="$3"
    #Read
    echo -e "\t\t/// @brief Reads a $desc from the specified data" >>$src
    echo -e "\t\t/// @param data Data to read from" >>$src
    echo -e "\t\t/// @param bigEndian Whether or not value is stored in big-endian" >>$src
    echo -e "\t\t/// @return $desc that was read" >>$src
    echo -e "\t\tpublic: static $literal read${suffix}(void *data, bool bigEndian);" >>$src
    echo -e "\t\t" >>$src
    echo -e "\t\t/// @brief Reads a little-endian $desc from the specified data" >>$src
    echo -e "\t\t/// @param data Data to read from" >>$src
    echo -e "\t\t/// @return $desc that was read" >>$src
    echo -e "\t\tpublic: static $literal read${suffix}L(void *data);" >>$src
    echo -e "\t\t" >>$src
    echo -e "\t\t/// @brief Reads a big-endian $desc from the specified data" >>$src
    echo -e "\t\t/// @param data Data to read from" >>$src
    echo -e "\t\t/// @return $desc that was read" >>$src
    echo -e "\t\tpublic: static $literal read${suffix}B(void *data);" >>$src
    echo -e "\t\t" >>$src
    #Write
    echo -e "\t\t/// @brief Writes a $desc to the specified data" >>$src
    echo -e "\t\t/// @param data Data to write to" >>$src
    echo -e "\t\t/// @param bigEndian Whether or not to store value in big-endian" >>$src
    echo -e "\t\t/// @param value $desc to write" >>$src
    echo -e "\t\tpublic: static void write${suffix}(void *data, bool bigEndian, $literal value);" >>$src
    echo -e "\t\t" >>$src
    echo -e "\t\t/// @brief Writes a little-endian $desc to the specified data" >>$src
    echo -e "\t\t/// @param data Data to write to" >>$src
    echo -e "\t\t/// @param value $desc to write" >>$src
    echo -e "\t\tpublic: static void write${suffix}L(void *data, $literal value);" >>$src
    echo -e "\t\t" >>$src
    echo -e "\t\t/// @brief Writes a big-endian $desc to the specified data" >>$src
    echo -e "\t\t/// @param data Data to write to" >>$src
    echo -e "\t\t/// @param value $desc to write" >>$src
    echo -e "\t\tpublic: static void write${suffix}B(void *data, $literal value);" >>$src
}
auto "UInt16" "uint16_t" "16-bit unsigned integer"
echo -e "\t\t" >>$src
auto "Int16" "int16_t" "16-bit signed integer"
echo -e "\t\t" >>$src
auto "UInt32" "uint32_t" "32-bit unsigned integer"
echo -e "\t\t" >>$src
auto "Int32" "int32_t" "32-bit signed integer"
echo -e "\t\t" >>$src
auto "UInt64" "uint64_t" "64-bit unsigned integer"
echo -e "\t\t" >>$src
auto "Int64" "int64_t" "64-bit signed integer"

echo -e "\t};" >>$src
echo -e "}" >>$src
echo -e "#endif" >>$src