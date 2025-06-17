#include "rookpp.io.BinWriter.h"

using namespace rookpp::io;

BinWriter::BinWriter(std::ofstream *stream)
{
    f_Buffer = malloc(8);
    f_Stream = stream;
}

BinWriter::~BinWriter()
{
    free(f_Buffer);
    
    f_Buffer = NULL;
    f_Stream = NULL;
}

#pragma region get/set

void *BinWriter::get_Buffer() { return f_Buffer; }

std::ofstream *BinWriter::get_Stream() { return f_Stream; }

#pragma endregion