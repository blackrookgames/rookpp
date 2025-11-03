#include <cstdint>
#include <fstream>
#include <iostream>

#include "ramen/huffman/HuffmanTree.h"

#include "IO.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << *argv << " <output>" << std::endl;
        return 0;
    }
    
    std::filesystem::path output(argv[1]);
    
    int exit = 1;
    // Create tree
    rookxx::ramen::huffman::HuffmanTree tree;
    // Save tree
    if (!rookxx::ioutil::IO::save(output, tree, std::ios::binary))
        goto finish;
    // Load tree
    if (!rookxx::ioutil::IO::load(output, tree, std::ios::binary))
        goto finish;
    // Print tree
    // TODO: Add code
    // Finish
    exit = 0;
finish:
    return exit;
}