#include <cstddef>
#include <cstdint>
#include "ramen/ArrUtil.h"

#ifndef rookxx_ramen_StringTemplate_h
#define rookxx_ramen_StringTemplate_h

namespace rookxx::ramen
{
    /// @brief Represents a template for a string
    /// @tparam TChar Character type
    template<typename TChar>
    class StringTemplate
    {
        #pragma region init

    public:

        /// @brief Constructor for StringTemplate
        StringTemplate()
        {
            f_Chars = nullptr;
            f_Length = 0;
        }

        /// @brief Constructor for StringTemplate
        /// @param length Length of string
        StringTemplate(size_t length)
        {
            f_Chars = rookxx::ramen::ArrUtil::create<TChar>(length);
            f_Length = length;
        }

        /// @brief Constructor for StringTemplate
        /// @param cstr C-style string
        StringTemplate(const char* cstr)
        {
            const char* iptr;
            TChar* optr;
            // Determine length
            f_Length = 0;
            iptr = cstr;
            while (*(iptr++) != 0)
                ++f_Length;
            // Create characters
            f_Chars = rookxx::ramen::ArrUtil::create<TChar>(f_Length);
            iptr = cstr;
            optr = f_Chars;
            for (size_t i = 0; i < f_Length; ++i)
                *(optr++) = (TChar)*(iptr++);
        }

        /// @brief Destructor for StringTemplate
        virtual ~StringTemplate()
        {
            if (f_Chars) delete[] f_Chars;
        }
        
        /// @brief Copy constructor for StringTemplate
        /// @param src Source
        StringTemplate(const StringTemplate& src)
        {
            f_Chars = rookxx::ramen::ArrUtil::createCopy(src.f_Chars, src.f_Length);
            f_Length = src.f_Length;
        }
        
        /// @brief Move constructor for StringTemplate
        /// @param src Source
        StringTemplate(StringTemplate&& src)
        {
            f_Chars = src.f_Chars;
            f_Length = src.f_Length;
            src.f_Chars = nullptr;
            src.f_Length = 0;
        }
        
        /// @brief Copy assignment for StringTemplate
        /// @param src Source
        StringTemplate& operator=(const StringTemplate& src)
        {
            if (this != &src)
            {
                if (f_Chars) delete[] f_Chars;
                f_Chars = rookxx::ramen::ArrUtil::createCopy(src.f_Chars, src.f_Length);
                f_Length = src.f_Length;
            }
            return *this;
        }
        
        /// @brief Move assignment for StringTemplate
        /// @param src Source
        StringTemplate& operator=(StringTemplate&& src)
        {
            if (this != &src)
            {
                if (f_Chars) delete[] f_Chars;
                f_Chars = src.f_Chars;
                f_Length = src.f_Length;
                src.f_Chars = nullptr;
                src.f_Length = 0;
            }
            return *this;
        }

        #pragma endregion

        #pragma region fields
    
    private:

        TChar* f_Chars;
        size_t f_Length;

        #pragma endregion

        #pragma region properties
        
    public:

        /// @brief Length of string
        size_t length() const { return f_Length; }

        #pragma endregion

        #pragma region helper

    protected:
        
        /// @brief Pointer to characters
        TChar* p_Chars() { return f_Chars; }
        /// @brief Pointer to characters
        const TChar* p_Chars() const { return f_Chars; }

        #pragma endregion

        #pragma region operators

    public:
        
        /// @brief Gets a reference to the character at the specified index
        /// @param index Index of character
        /// @return A reference to the character at the specified index
        TChar& operator[](size_t index)
        {
            return f_Chars[index];
        }
        
        /// @brief Gets a reference to the character at the specified index
        /// @param index Index of character
        /// @return A reference to the character at the specified index
        const TChar& operator[](size_t index) const
        {
            return f_Chars[index];
        }

        #pragma endregion

        #pragma region functions

    public:

        /// @brief Initializes the string
        /// @param length Length of string
        /// @note To retain any existing data within the string, use resize(size_t) instead.
        void init(size_t length)
        {
            if (f_Chars) delete[] f_Chars;
            f_Chars = rookxx::ramen::ArrUtil::create<TChar>(length);
            f_Length = length;
        }

        /// @brief Resizes the string
        /// @param length New length of string
        /// @note Existing data may be truncated
        void resize(size_t length)
        {
            TChar* oldChars = f_Chars;
            size_t oldLength = f_Length;
            f_Chars = rookxx::ramen::ArrUtil::createCopy<TChar>(oldChars, length, oldLength);
            f_Length = length;
        }

        /// @brief Whether or not the current string is equal in value to the other string
        /// @param other Other string
        /// @param insensitive Check or not to make a case-insensitive comparison
        /// @return Whether or not the current string is equal in value to the other string
        bool equals(const StringTemplate<TChar>& other, bool insensitive = false) const
        {
            // Check length
            if (f_Length != other.f_Length)
                return false;
            // Check characters
            {
                const TChar* cptr = f_Chars;
                const TChar* optr = other.f_Chars;
                for (size_t i = 0; i < f_Length; ++i)
                {
                    TChar c = *(cptr++);
                    TChar o = *(optr++);
                    // Adjust if case-insensitive
                    if (insensitive)
                    {
                        if (c >= 'a' && c <= 'z')
                            c -= 'a' - 'A';
                        if (o >= 'a' && o <= 'z')
                            o -= 'a' - 'A';
                    }
                    // Compare
                    if (c != o) return false;
                }
            }
            // Equality!!!
            return true;
        }

        /// @brief Compares the current string to the other string
        /// @param other Other string
        /// @param insensitive Check or not to make a case-insensitive comparison
        /// @return < 0: Current string precedes other string\
        /// @return = 0: Current string and other string are equal\
        /// @return > 0: Current string follows other string
        /// @note Casing is compared in such a way that string only differ in casing are closer together
        /// @note For example, "apple" will follow "APPLE" but precede "BANANA"
        int compare(const StringTemplate<TChar>& other, bool insensitive = false) const
        {
            // Length comparison
            size_t minLen;
            int lenCmp;
            if (f_Length < other.f_Length)
            {
                minLen = f_Length;
                lenCmp = -1;
                goto charCmp;
            }
            if (f_Length > other.f_Length)
            {
                minLen = other.f_Length;
                lenCmp = 1;
                goto charCmp;
            }
            minLen = f_Length;
            lenCmp = 0;
            // Character comparison
        charCmp:
            int caseCmp = 0;
            {
                const TChar* cptr = f_Chars;
                const TChar* optr = other.f_Chars;
                for (size_t i = 0; i < minLen; ++i)
                {
                    TChar c = *(cptr++);
                    TChar o = *(optr++);
                    // Case-sensitive comparison
                    if (caseCmp == 0)
                    {
                        if (c < o)
                            caseCmp = -1;
                        else if (c > o)
                            caseCmp = 1;
                    }
                    // Case-insensitive comparison
                    if (c >= 'a' && c <= 'z')
                        c -= 'a' - 'A';
                    if (o >= 'a' && o <= 'z')
                        o -= 'a' - 'A';
                    if (c < o) return -1;
                    if (c > o) return 1;
                }
            }
            if (lenCmp != 0) return lenCmp;
            if (insensitive) return 0;
            return caseCmp;
        }

        #pragma endregion
    };

    #pragma region operators

    /// @brief Checks if string A and string B are equal
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return True if string A and string B are equal; otherwise false
    template<typename TChar>
    constexpr bool operator==(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return strA.equals(strB); }

    /// @brief Checks if string A and string B are not equal
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return True if string A and string B are not equal; otherwise false
    template<typename TChar>
    constexpr bool operator!=(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return !strA.equals(strB); }

    /// @brief Checks if string A precedes string B
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return True if string A precedes string B; otherwise false
    template<typename TChar>
    constexpr bool operator<(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return strA.compare(strB) < 0; }

    /// @brief Checks if string A precedes or is equal to string B
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return True if string A precedes or is equal to string B; otherwise false
    template<typename TChar>
    constexpr bool operator<=(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return strA.compare(strB) <= 0; }

    /// @brief Checks if string A follows string B
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return True if string A follows string B; otherwise false
    template<typename TChar>
    constexpr bool operator>(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return strA.compare(strB) > 0; }

    /// @brief Checks if string A follows or is equal to string B
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return True if string A follows or is equal to string B; otherwise false
    template<typename TChar>
    constexpr bool operator>=(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return strA.compare(strB) >= 0; }

    /// @brief Combines string A and string B and returns the result
    /// @tparam TChar Character type
    /// @param strA String A
    /// @param strB String B
    /// @return Resulting string
    template<typename TChar>
    StringTemplate<TChar> operator+(const StringTemplate<TChar>& strA, const StringTemplate<TChar>& strB)
    { return strA.combine(strB); }

    /// @brief Appends a character to a string and returns the result
    /// @tparam TChar Character type
    /// @param str String
    /// @param c Character
    /// @return Resulting string
    template<typename TChar>
    StringTemplate<TChar> operator+(const StringTemplate<TChar>& str, const TChar& c)
    { return str.append(c); }

    /// @brief Prepends a character to a string and returns the result
    /// @tparam TChar Character type
    /// @param c Character
    /// @param str String
    /// @return Resulting string
    template<typename TChar>
    StringTemplate<TChar> operator+(const TChar& c, const StringTemplate<TChar>& str)
    { return str.prepend(c); }

    #pragma endregion
}

#endif