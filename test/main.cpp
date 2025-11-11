#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "ramen/ArrUtil.h"
#include "ramen/huffman/HuffmanTree.h"
#include "ramen/huffman/HuffmanUtility.h"

#include "IO.h"

#include "TreePrinter.h"

namespace huffman = rookxx::ramen::huffman;

void extractByteData(const char* arg, uint8_t*& data, size_t& size)
{
    const char* iptr;
    // Get size
    size = 0;
    iptr = arg;
    while (*(iptr++) != 0x00)
        ++size;
    // Get data
    if (size > 0)
    {
        data = new uint8_t[size];
        uint8_t* optr = data;
        iptr = arg;
        for (size_t i = 0; i < size; i++)
            *(optr++) = (uint8_t)(*(iptr++) & 0xFF);
    }
    else
    {
        data = nullptr;
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << *argv << " <string> <output>" << std::endl;
        return 0;
    }

    std::filesystem::path output(argv[2]);

    uint8_t* idata = nullptr;
    size_t isize = 0;
    uint8_t* odata = nullptr;
    size_t osize = 0;
    {
        // Get input data
        extractByteData(argv[1], idata, isize);
        // Save tree
        {
            if (!huffman::HuffmanUtility::encode(idata, isize, odata, osize))
                goto fail;
            if (!rookxx::ioutil::IO::save(output, odata, osize, std::ios::binary))
                goto fail;
        }
        // Load tree
        huffman::HuffmanTree tree;
        if (!rookxx::ioutil::IO::load(output, tree, std::ios::binary))
            goto fail;
        // Print tree
        TreePrinter::run(tree, true);
    }
fail:
    if (odata) delete[] odata;
    if (idata) delete[] idata;
    return 0;
}