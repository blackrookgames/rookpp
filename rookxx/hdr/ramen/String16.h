#include <cstddef>
#include <cstdint>
#include "ramen/StringTemplate.h"

#ifndef rookxx_ramen_String16_h
#define rookxx_ramen_String16_h

namespace rookxx::ramen
{
    /// @brief Represents a string with 16-bit characters
    class String16 : public rookxx::ramen::StringTemplate<uint16_t>
    {
        #pragma region init

    public:

        /// @brief Constructor for String16
        String16();

        /// @brief Constructor for String16
        /// @param length Length of string
        String16(size_t length);

        /// @brief Constructor for String16
        /// @param cstr C-style string
        String16(const char* cstr);

        /// @brief Destructor for String16
        virtual ~String16();
        
        /// @brief Copy constructor for String16
        /// @param src Source
        String16(const String16& src);
        
        /// @brief Move constructor for String16
        /// @param src Source
        String16(String16&& src);
        
        /// @brief Copy assignment for String16
        /// @param src Source
        String16& operator=(const String16& src);
        
        /// @brief Move assignment for String16
        /// @param src Source
        String16& operator=(String16&& src);

        #pragma endregion

        #pragma region operators

    public:
        
        /// @brief Creates a C-style string using data from the current string
        operator char*() const;

        #pragma endregion

        #pragma region functions
    
    public:

        /// @brief Combines the current string with the other string and returns the result
        /// @param other Other string
        /// @return Resulting string
        String16 combine(const String16& other) const;

        /// @brief Appends the specified character to the string and returns the result
        /// @param c Character
        /// @return Resulting string
        String16 append(uint16_t c) const;

        /// @brief Prepends the specified character to the string and returns the result
        /// @param c Character
        /// @return Resulting string
        String16 prepend(uint16_t c) const;

        #pragma endregion
    };

    #pragma region operators

    /// @brief Combines string A and string B and returns the result
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return Resulting string
    inline String16 operator+(const String16& strA, const String16& strB)
    { return strA.combine(strB); }

    /// @brief Appends a character to a string and returns the result
    /// @tparam TChar Character type
    /// @param str String
    /// @param c Character
    /// @return Resulting string
    inline String16 operator+(const String16& str, const uint16_t& c)
    { return str.append(c); }

    /// @brief Prepends a character to a string and returns the result
    /// @tparam TChar Character type
    /// @param c Character
    /// @param str String
    /// @return Resulting string
    inline String16 operator+(const uint16_t& c, const String16& str)
    { return str.prepend(c); }

    #pragma endregion
}

#endif