#include <cstddef>
#include <cstdint>

#include "StringTemplate.h"

#ifndef rookxx_strings_String8_h
#define rookxx_strings_String8_h

namespace rookxx::strings
{
    /// @brief
    /// Represents a string of 8-bit characters
    class String8 : public StringTemplate<uint8_t, size_t>
    {
        #pragma region nested

    public:
        typedef StringTemplate<uint8_t, size_t>::CStrNullOption CStrNullOption;

        #pragma endregion

        #pragma region init

    public:
        
        /// @brief 
        /// Constructor for String8
        String8();

        /// @brief 
        /// Cosntructor for String8
        /// @param length 
        /// Length of string
        String8(size_t length);

        /// @brief 
        /// Constructor for String8
        /// @param cstr 
        /// Source C-string
        /// @note 
        /// Depending on the implemention of the char type, some characters 
        /// may be modified in the constructed string.
        String8(const char* cstr);

        /// @brief 
        /// Destructor for String8
        virtual ~String8();

        #pragma endregion
    };
}

#endif