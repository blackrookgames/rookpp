#include <cstdint>
#include <fstream>
#include <iostream>

#include "ramen/huffman/HuffmanTree.h"

#include "IO.h"

#include "TreePrinter.h"

namespace huffman = rookxx::ramen::huffman;

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
    huffman::HuffmanTree tree;
    huffman::HuffmanParent parent0;
    tree.root().setChild0(&parent0);
    huffman::HuffmanLeaf leaf00(4, 5);
    parent0.setChild0(&leaf00);
    huffman::HuffmanLeaf leaf01(8, 10);
    parent0.setChild1(&leaf01);
    huffman::HuffmanParent parent1;
    tree.root().setChild1(&parent1);
    huffman::HuffmanLeaf leaf10(12, 15);
    parent1.setChild0(&leaf10);
    huffman::HuffmanLeaf leaf11(16, 20);
    parent1.setChild1(&leaf11);
    // Save tree
    {
        uint8_t* data;
        size_t size;
        tree.serialize(data, size, false);
        if (!rookxx::ioutil::IO::save(output, data, size, std::ios::binary))
            goto finish;
    }
    // Load tree
    if (!rookxx::ioutil::IO::load(output, tree, std::ios::binary))
        goto finish;
    // Print tree
    TreePrinter::run(tree);
    // Finish
    exit = 0;
finish:
    return exit;
}