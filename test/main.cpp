#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "ramen/ArrUtil.h"
#include "ramen/huffman/HuffmanTree.h"

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

void printByteData(const uint8_t* data, size_t size)
{
    while (size-- > 0)
        std::cout << *(data++);
    std::cout << std::endl;
}

void countOccurances(const uint8_t* data, size_t size, size_t*& occurances)
{
    occurances = rookxx::ramen::ArrUtil::createNull<size_t>(256);
    while (size-- > 0)
        occurances[*(data++)] += 1;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << *argv << " <string>" << std::endl;
        return 0;
    }

    uint8_t* idata = nullptr;
    size_t isize = 0;
    size_t* occurances = nullptr;
    {
        // Get input data
        extractByteData(argv[1], idata, isize);
        // Print input data
        printByteData(idata, isize);
        // Count occurances
        countOccurances(idata, isize, occurances);
        // Create tree
        huffman::HuffmanTree tree;
        {
            // Create queue
            std::vector<huffman::HuffmanNode*> queue;
            queue.reserve(256);
            {
                size_t* iptr = occurances;
                for (size_t i = 0; i < 256; i++)
                {
                    if (*iptr > 0)
                    {
                        huffman::HuffmanLeaf* newNode = new huffman::HuffmanLeaf(
                            (uint8_t)i, *iptr, true);
                        auto iter = queue.begin();
                        while (iter != queue.end())
                        {
                            if ((*iter)->freq() >= newNode->freq())
                                break;
                            ++iter;
                        }
                        queue.insert(iter, newNode);
                    }
                    ++iptr;
                }
            }
            // List queue
            for (auto iter = queue.begin(); iter != queue.end(); iter++)
            {
                huffman::HuffmanLeaf* leaf = static_cast<huffman::HuffmanLeaf*>(*iter);
                std::cout << "'" << leaf->value() << "': " << leaf->freq() << std::endl;
            }
            // Build tree
            if (queue.size() > 1)
            {
                while (queue.size() > 2)
                {
                    // Remove first two
                    huffman::HuffmanNode* child0 = queue[0];
                    huffman::HuffmanNode* child1 = queue[1];
                    queue.erase(queue.begin());
                    queue.erase(queue.begin());
                    // Create new node
                    huffman::HuffmanParent* newNode = new huffman::HuffmanParent(true);
                    newNode->setChild0(child0);
                    newNode->setChild1(child1);
                    // Insert new node into queue
                    auto iter = queue.begin();
                    while (iter != queue.end())
                    {
                        if ((*iter)->freq() >= newNode->freq())
                            break;
                        ++iter;
                    }
                    queue.insert(iter, newNode);
                }
                tree.root().setChild0(queue[0]);
                tree.root().setChild1(queue[1]);
                queue.clear();
            }
            else if (queue.size() == 1)
            {
                tree.root().setChild0(queue[0]);
                queue.clear();
            }
        }
        // Print tree
        TreePrinter::run(tree, true);
    }
    if (occurances) delete[] occurances;
    if (idata) delete[] idata;
    return 0;
}