src=$1
rm -fr $src

echo -e "#include \"rookpp.io.BinReader.h\"" >>$src
echo -e "" >>$src
echo -e "using namespace rookpp::io;" >>$src

auto8() {
    local suffix=$1
    local literal=$2
    local explicit=$3
    echo -e "$literal BinReader::read${suffix}()" >>$src
    echo -e "{" >>$src
    echo -e "\tf_Stream->read((char*)f_Buffer, 1);" >>$src
    if [ $explicit = 1 ]; then
        echo -e "\treturn ($literal)(*((uint8_t*)f_Buffer));" >>$src
    else
        echo -e "\treturn *((uint8_t*)f_Buffer);" >>$src
    fi
    echo -e "}" >>$src
}

auto() {
    local suffix=$1
    local literal=$2
    local byteCount=$3
    echo -e "$literal BinReader::read${suffix}(bool bigEndian)" >>$src
    echo -e "{" >>$src
    echo -e "\tf_Stream->read((char*)f_Buffer, ${byteCount});" >>$src
    echo -e "\treturn BitData::read${suffix}(f_Buffer, bigEndian);" >>$src
    echo -e "}" >>$src
    echo -e "" >>$src
    echo -e "$literal BinReader::read${suffix}L()" >>$src
    echo -e "{" >>$src
    echo -e "\tf_Stream->read((char*)f_Buffer, ${byteCount});" >>$src
    echo -e "\treturn BitData::read${suffix}L(f_Buffer);" >>$src
    echo -e "}" >>$src
    echo -e "" >>$src
    echo -e "$literal BinReader::read${suffix}B()" >>$src
    echo -e "{" >>$src
    echo -e "\tf_Stream->read((char*)f_Buffer, ${byteCount});" >>$src
    echo -e "\treturn BitData::read${suffix}B(f_Buffer);" >>$src
    echo -e "}" >>$src
}

echo -e "" >>$src
auto8 "UInt8" "uint8_t" 0
echo -e "" >>$src
auto8 "Int8" "int8_t" 1
echo -e "" >>$src
auto "UInt16" "uint16_t" 2
echo -e "" >>$src
auto "Int16" "int16_t" 2
echo -e "" >>$src
auto "UInt32" "uint32_t" 4
echo -e "" >>$src
auto "Int32" "int32_t" 4
echo -e "" >>$src
auto "UInt64" "uint64_t" 8
echo -e "" >>$src
auto "Int64" "int64_t" 8