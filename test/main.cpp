#include <cstddef>
#include <cstdint>
#include <iostream>
#include <utility>

#include "ramen/String8.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << *argv << " <string0> [<string1> [<string2> ...]]" << std::endl;
        return 0;
    }
    rookxx::ramen::String8 str;
    for (int i = 1; i < argc; ++i)
        str = ';' + str + argv[i];
    std::cout << str << std::endl;
    return 0;
}