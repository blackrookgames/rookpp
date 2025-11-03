#include <cstdint>
#include <fstream>
#include <iostream>

#include "bitman/ConstBitPtr.h"

int main(int argc, char** argv)
{
    size_t size = 16;
    uint8_t data[size];
    for (size_t i = 0; i < size; i++)
        data[i] = i;

    const uint8_t* test = data;

    rookxx::bitman::ConstBitPtr beg = test;
    rookxx::bitman::ConstBitPtr end = test + 16;
    for (auto ptr = beg; ptr < end; ++ptr)
        std::cout << *ptr;
    std::cout << std::endl;
}