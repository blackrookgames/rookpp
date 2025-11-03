#include "IO.h"

#include <fstream>

#include "ramen/Serializable.h"

#pragma region macros

#define mc_IS_OpenFail(path) \
    std::cerr << "Failed to open " << path << " for reading." << std::endl;

#define mc_IS_ReadError(path) \
    std::cerr << "An unexpected error occurred while reading from " << path << "." << std::endl;

#define mc_OS_OpenFail(path) \
    std::cerr << "Failed to open " << path << " for writing." << std::endl;

#define mc_OS_WriteError(path) \
    std::cerr << "An unexpected error occurred while writing from " << path << "." << std::endl;

#pragma endregion

using namespace rookxx::ioutil;

#pragma region helper

size_t IO::m_GetSize(std::ifstream& is)
{
    if (is.fail()) return 0;
    // Mark current pos
    auto mark = is.tellg();
    if (is.fail()) return 0;
    // Goto end
    is.seekg(0, std::ios::end);
    if (is.fail()) return 0;
    // Get end position (assume success)
    size_t end = is.tellg();
    // Return to marked position (assume success)
    is.seekg(mark);
    // Success!!!
    return end;
}

size_t IO::m_Read(std::ifstream& is, uint8_t* dest, size_t size)
{
    size_t bytesRead = 0;
    if (!is.fail())
    {
        char buffer[1];
        while (bytesRead < size)
        {
            is.read(buffer, 1);
            if (is.fail()) goto finish;
            *(dest++) = (uint8_t)(*buffer & 0xFF);
            ++bytesRead;
        }
    }
finish:
    return bytesRead;
}

size_t IO::m_Write(std::ofstream& os, const uint8_t* src, size_t size)
{
    size_t bytesWritten = 0;
    if (!os.fail())
    {
        char buffer[1];
        while (bytesWritten < size)
        {
            *buffer = (char)*(src++);
            os.write(buffer, 1);
            if (os.fail()) goto finish;
            ++bytesWritten;
        }
    }
finish:
    return bytesWritten;
}

#pragma endregion

#pragma region char*

bool IO::load(const std::filesystem::path& path, char*& content, size_t& size, std::ios_base::openmode mode, bool appendNull)
{
    bool success = false;
    content = nullptr;
    size = 0;
    // Open file
    std::ifstream is(path, mode);
    if (!is.is_open()) { mc_IS_OpenFail(path); goto fail; }
    // Get size
    size = m_GetSize(is);
    if (is.fail()) { mc_IS_ReadError(path); goto fail; }
    // Read content
    content = new char[size];
    is.read(content, size);
    if (is.fail()) { mc_IS_ReadError(path); goto fail; }
    // Finish
    success = true;
    goto finish;
fail:
    if (content) delete[] content;
    content = nullptr;
    size = 0;
finish:
    if (is.is_open()) is.close();
    return success;
}

bool IO::save(const std::filesystem::path& path, const char* content, size_t size, std::ios_base::openmode mode)
{
    bool success = false;
    // Open file
    std::ofstream os(path, mode);
    if (!os.is_open()) { mc_OS_OpenFail(path); goto finish; }
    // Write content
    os.write(content, size);
    if (os.fail()) { mc_OS_WriteError(path); goto finish; }
    // Finish
    success = true;
finish:
    if (os.is_open()) os.close();
    return success;
}

#pragma endregion

#pragma region uint8_t*

bool IO::load(const std::filesystem::path& path, uint8_t*& content, size_t& size, std::ios_base::openmode mode, bool appendNull)
{
    bool success = false;
    content = nullptr;
    size = 0;
    // Open file
    std::ifstream is(path, mode);
    if (!is.is_open()) { mc_IS_OpenFail(path); goto fail; }
    // Get size
    size = m_GetSize(is);
    if (is.fail()) { mc_IS_ReadError(path); goto fail; }
    // Read content
    content = new uint8_t[size];
    m_Read(is, content, size);
    if (is.fail()) { mc_IS_ReadError(path); goto fail; }
    // Finish
    success = true;
    goto finish;
fail:
    if (content) delete[] content;
    content = nullptr;
    size = 0;
finish:
    if (is.is_open()) is.close();
    return success;
}

bool IO::save(const std::filesystem::path& path, const uint8_t* content, size_t size, std::ios_base::openmode mode)
{
    bool success = false;
    // Open file
    std::ofstream os(path, mode);
    if (!os.is_open()) { mc_OS_OpenFail(path); goto finish; }
    // Write content
    m_Write(os, content, size);
    if (os.fail()) { mc_OS_WriteError(path); goto finish; }
    // Finish
    success = true;
finish:
    if (os.is_open()) os.close();
    return success;
}

#pragma endregion

#pragma region Serializable

bool IO::load(const std::filesystem::path& path, rookxx::ramen::Serializable& serializable, std::ios_base::openmode mode)
{
    // Load serialized data
    uint8_t* data;
    size_t size;
    if (!load(path, data, size, mode, false))
        return false;
    // Deserialize
    bool success = serializable.deserialize(data, size);
    if (data) delete[] data;
    return success;
}

bool IO::save(const std::filesystem::path& path, const rookxx::ramen::Serializable& serializable, std::ios_base::openmode mode)
{
    // Serialize
    uint8_t* data;
    size_t size;
    if (!serializable.serialize(data, size))
        return false;
    // Save serialized data
    bool success = serializable.serialize(data, size);
    if (data) delete[] data;
    return success;
}

#pragma endregion

void IO::getLineChar(char* src, char* where, int& lineN, int& charN)
{
    if (src <= where)
    {
        lineN = 1;
        charN = 1;
        char newLine = 0;
        while (src < where)
        {
            if (newLine != 0)
            {
                if (*src == newLine)
                {
                    lineN++;
                    charN = 1;
                }
                else charN++;
            }
            else
            {
                if (*src == '\n' || *src == '\r')
                {
                    newLine = *src;
                    lineN++;
                    charN = 1;
                }
                else charN++;
            }
            src++;
        }
    }
    else
    {
        lineN = 0;
        charN = 0;
    }
}

bool IO::createDirectory(const std::filesystem::path& path)
{
    try
    {
        create_directories(path);
        return true;
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cerr << "An error occurred while creating the directory " << path << "." << std::endl;
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void IO::createBuffer(size_t bsize, char*& buffer, size_t& csize)
{
    csize = (bsize + sizeof(char) - 1) / sizeof(char);
    buffer = (csize == 0) ? nullptr : (new char[csize]);
}

size_t IO::getBufferSize(size_t csize)
{
    return csize * sizeof(char);
}