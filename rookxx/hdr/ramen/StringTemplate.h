#include <cstddef>
#include <cstdint>
#include "ramen/ArrUtil.h"

#ifndef rookxx_ramen_StringTemplate_h
#define rookxx_ramen_StringTemplate_h

namespace rookxx::ramen
{
    /// @brief Represents a template for a string
    /// @tparam Character type
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
        /// @return Whether or not the current string is equal in value to the other string
        /// @note Comparison is case sensitive
        bool equals(const StringTemplate<TChar>& other) const
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
                    if (*(cptr++) != *(optr++))
                        return false;
                }
            }
            // Equality!!!
            return true;
        }

        /// @brief Compares the current string to the other string
        /// @param other Other string
        /// @return < 0: Current string precedes other string\
        /// @return = 0: Current string and other string are equal\
        /// @return > 0: Current string follows other string
        /// @note Comparison is case sensitive
        int compare(const StringTemplate<TChar>& other) const
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
            {
                const TChar* cptr = f_Chars;
                const TChar* optr = other.f_Chars;
                for (size_t i = 0; i < minLen; ++i)
                {
                    if (*cptr < *optr) return -1;
                    if (*cptr > *optr) return 1;
                    ++cptr; ++optr;
                }
            }
            // Return length comparison
            return lenCmp;
        }

        #pragma endregion
    };
}

#endif