#include "rookpp.io.BinReader.h"

using namespace rookpp::io;

BinReader::BinReader(std::ifstream *stream)
{
    f_Buffer = malloc(8);
    f_Stream = stream;
}

BinReader::~BinReader()
{
    free(f_Buffer);
    
    f_Buffer = NULL;
    f_Stream = NULL;
}

#pragma region get/set

void *BinReader::get_Buffer() { return f_Buffer; }

std::ifstream *BinReader::get_Stream() { return f_Stream; }

#pragma endregion