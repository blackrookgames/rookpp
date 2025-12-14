#include <iostream>

#include "strings/String8.h"

int main(int argc, char** argv)
{
    rookxx::strings::String8 str("Hello world!!!");
    str.get(6) = 'e';
    for (size_t i = 0; i < str.length(); ++i)
        std::cout << str.get(i);
    std::cout << std::endl;

    return 0;
}