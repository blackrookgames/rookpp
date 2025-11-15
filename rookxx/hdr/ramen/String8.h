#include <cstddef>
#include <cstdint>
#include "ramen/StringTemplate.h"

#ifndef rookxx_ramen_String8_h
#define rookxx_ramen_String8_h

namespace rookxx::ramen
{
    /// @brief Represents a string with 8-bit characters
    class String8 : public rookxx::ramen::StringTemplate<uint8_t>
    {
        #pragma region init

    public:

        /// @brief Constructor for String8
        String8();

        /// @brief Constructor for String8
        /// @param length Length of string
        String8(size_t length);

        /// @brief Constructor for String8
        /// @param cstr C-style string
        String8(const char* cstr);

        /// @brief Destructor for String8
        virtual ~String8();
        
        /// @brief Copy constructor for String8
        /// @param src Source
        String8(const String8& src);
        
        /// @brief Move constructor for String8
        /// @param src Source
        String8(String8&& src);
        
        /// @brief Copy assignment for String8
        /// @param src Source
        String8& operator=(const String8& src);
        
        /// @brief Move assignment for String8
        /// @param src Source
        String8& operator=(String8&& src);

        #pragma endregion

        #pragma region operators

    public:
        
        /// @brief Creates a C-style string using data from the current string
        operator char*() const;

        #pragma endregion
    };
}

#endif