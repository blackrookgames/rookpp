#include <cstddef>
#include <filesystem>
#include <iostream>

#ifndef rookxx_ioutil_IO_h
#define rookxx_ioutil_IO_h

#ifndef rookxx_ramen_Serializable_h
namespace rookxx::ramen
{
    class Serializable;
}
#endif

namespace rookxx::ioutil
{

    /// @brief Utility for I/O operations
    class IO
    {
        #pragma region helper

        private: static size_t m_GetSize(std::ifstream& is);

        private: static size_t m_Read(std::ifstream& is, uint8_t* dest, size_t size);

        private: static size_t m_Write(std::ofstream& os, const uint8_t* src, size_t size);

        #pragma endregion

        #pragma region char*

        /// @brief Loads from a file
        /// @param path Path to the file
        /// @param content Loaded content
        /// @param size Size of content
        /// @param mode I/O mode
        /// @param appendNull Whether or not to add a null terminating character at the end
        /// @return Whether or not successful
        /// @note If unsuccessful, content will be set to nullptr
        /// @note If unsuccessful, size will be set to 0
        public: static bool load(const std::filesystem::path& path, char*& content, size_t& size, std::ios_base::openmode mode = std::ios::in, bool appendNull = false);

        /// @brief Saves to a file
        /// @param path Path to the file
        /// @param content Content to save
        /// @param size Size of content
        /// @param mode I/O mode
        /// @return Whether or not successful
        public: static bool save(const std::filesystem::path& path, const char* content, size_t size, std::ios_base::openmode mode = std::ios::out);

        #pragma endregion

        #pragma region uint8_t*

        /// @brief Loads from a file
        /// @param path Path to the file
        /// @param content Loaded content
        /// @param size Size of content
        /// @param mode I/O mode
        /// @param appendNull Whether or not to add a null terminating character at the end
        /// @return Whether or not successful
        /// @note If unsuccessful, content will be set to nullptr
        /// @note If unsuccessful, size will be set to 0
        public: static bool load(const std::filesystem::path& path, uint8_t*& content, size_t& size, std::ios_base::openmode mode = std::ios::in, bool appendNull = false);

        /// @brief Saves to a file
        /// @param path Path to the file
        /// @param content Content to save
        /// @param size Size of content
        /// @param mode I/O mode
        /// @return Whether or not successful
        public: static bool save(const std::filesystem::path& path, const uint8_t* content, size_t size, std::ios_base::openmode mode = std::ios::out);

        #pragma endregion
        
        #pragma region Serializable

        /// @brief Loads from a file
        /// @param path Path to the file
        /// @param serializable Object with serializable data
        /// @param mode I/O mode
        /// @return Whether or not successful
        public: static bool load(const std::filesystem::path& path, rookxx::ramen::Serializable& serializable, std::ios_base::openmode mode = std::ios::in);

        /// @brief Saves to a file
        /// @param path Path to the file
        /// @param serializable Object with serializable data
        /// @param mode I/O mode
        /// @return Whether or not successful
        public: static bool save(const std::filesystem::path& path, const rookxx::ramen::Serializable& serializable, std::ios_base::openmode mode = std::ios::out);

        #pragma endregion

        /// @brief Creates a directory at the specified path if it doesn't exist
        /// @param path Path
        /// @return Whether or not successful
        public: static bool createDirectory(const std::filesystem::path& path);

        /// @brief Gets the line number and character number a location within a string
        /// @param src String
        /// @param where Location within string
        /// @param lineN Line number (1 is first line)
        /// @param charN Character number (1 is first character)
        public: static void getLineChar(char* src, char* where, int& lineN, int& charN);

        /// @brief Creates a character buffer of the specified byte size
        /// @param bsize Size (in bytes); see note
        /// @param buffer Pointer to created buffer
        /// @param csize Size (in characters) of created buffer
        /// @note The size of the created buffer may be a little larger than the specified byte size 
        /// if the specified byte size is an odd number and a single character is two bytes in size.
        public: static void createBuffer(size_t bsize, char*& buffer, size_t& csize);

        /// @brief Gets the byte size of a character buffer
        /// @param csize Size (in characters) of buffer
        /// @return Size (in bytes) of buffer
        public: static size_t getBufferSize(size_t csize);
    };
}

#endif