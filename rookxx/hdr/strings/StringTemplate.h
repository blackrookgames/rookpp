#ifndef rookxx_strings_StringTemplate_h
#define rookxx_strings_StringTemplate_h

namespace rookxx::strings
{
    /// @brief
    /// Represents a string of characters
    /// @tparam TChar
    /// Character type
    /// @tparam TLen
    /// Length type
    template<typename TChar, typename TLen>
    class StringTemplate
    {
        #pragma region nested

    public:
        
        /// @brief Represents an option for dealing with null characters when converting to a C-style string
        enum struct CStrNullOption
        {
            /// @brief 
            /// Created C-string will be truncated at the first occurance of a null character
            TruncateNull,
            /// @brief 
            /// Created C-string will not contain any null characters from the source string
            RemoveNull,
            /// @brief 
            /// Created C-string will contain all null characters from the source string; this may cause the created 
            /// string to not be fully readable by operations that interpret the occurance of a null character as the 
            /// end of the string.
            KeepNull,
        };
        
        /// @brief Represents an option for dealing with letters when comparing strings
        enum struct StrCmpLetterOption
        {
            /// @brief Letter comparisons are based solely on their ASCII values. \
            /// @brief Examples: \
            /// @brief A > a \
            /// @brief A > b \
            /// @brief a < B
            Simple,
            /// @brief Letters are first compared by their order in the alphabet, then compared by their casing. \
            /// @brief Examples: \
            /// @brief A > a \
            /// @brief A > b \
            /// @brief a > B
            PairCase,
            /// @brief 
            /// Letter casing is completely ignored. 
            /// @brief Examples: \
            /// @brief A == a \
            /// @brief A > b \
            /// @brief a > B
            IgnoreCase,
        }

        #pragma endregion

        #pragma region init

    public:

        // TODO: StringTemplate(const StringTemplate<TChar, TLen>& src)

        // TODO: StringTemplate(StringTemplate<TChar, TLen>&& src)

        // TODO: void m_CopyFrom(const StringTemplate<TChar, TLen>& src) // Protected

        // TODO: void m_MoveFrom(StringTemplate<TChar, TLen>&& src) // Protected
        
        /// @brief 
        /// Constructor for StringTemplate
        StringTemplate()
        {
            f_Length = 0;
            f_Beg = nullptr;
            f_End = nullptr;
        }

        /// @brief 
        /// Constructor for StringTemplate
        /// @param length 
        /// Length of string
        StringTemplate(TLen length)
        {
            if (length > 0)
            {
                f_Length = length;
                f_Beg = new TChar[f_Length];
                f_End = f_Beg + f_Length;
            }
            else
            {
                f_Length = 0;
                f_Beg = nullptr;
                f_End = nullptr;
            }
        }

        /// @brief 
        /// Constructor for StringTemplate
        /// @param cstr 
        /// Source C-string
        /// @note 
        /// Depending on the implemention of the char type and the constructed string's character type, some characters 
        /// may be modified in the constructed string.
        StringTemplate(const char* cstr)
        {
            const char* iptr;
            TChar* optr;
            // Determine length
            f_Length = 0;
            if (cstr)
            {
                iptr = cstr;
                while (*(iptr++) != 0)
                    ++f_Length;
            }
            // Add characters
            if (f_Length > 0)
            {
                f_Beg = new TChar[f_Length];
                f_End = f_Beg + f_Length;
                iptr = cstr;
                optr = f_Beg;
                for (TLen i = 0; i < f_Length; ++i)
                    *(optr++) = *(iptr++);
            }
            else
            {
                f_Beg = nullptr;
                f_End = nullptr;
            }
        }

        /// @brief 
        /// Destructor for StringTemplate
        virtual ~StringTemplate()
        {
            if (f_Beg)
                delete[] f_Beg;
        }

        #pragma endregion

        #pragma region fields

    private:
        
        TLen f_Length;
        TChar* f_Beg;
        TChar* f_End;

        #pragma endregion

        #pragma region properties

    public:
        
        /// @brief 
        /// Length of string
        TLen length() const { return f_Length; }

        /// @brief 
        /// Pointer to the beginning of string
        TChar* beg() { return f_Beg; }
        /// @brief 
        /// Pointer to the beginning of string
        const TChar* beg() const { return f_Beg; }

        /// @brief 
        /// Pointer to the end of string
        TChar* end() { return f_End; }
        /// @brief 
        /// Pointer to the end of string
        const TChar* end() const { return f_End; }

        #pragma endregion

        #pragma region methods

    public:

        /// @brief 
        /// Gets a reference to the character at the specified index
        /// @param index 
        /// Index of character
        /// @return 
        /// Reference to the character at the specified index
        /// @warning
        /// Ensure the index is within range, else undefined behaviour may result
        TChar& get(TLen index)
        {
            return f_Beg[index];
        }

        /// @brief 
        /// Gets the character at the specified index
        /// @param index 
        /// Index of character
        /// @return 
        /// The character at the specified index
        /// @warning
        /// Ensure the index is within range, else undefined behaviour may result
        TChar get(TLen index) const
        {
            return f_Beg[index];
        }

        /// @brief Sets the length of the string
        /// @param length New length
        /// @param preserve Whether or not the to try to preserve any existing character data
        void setLength(TLen length, bool preserve = false)
        {
            // Previous
            TLen prevLength = f_Length;
            TChar* prevChars = f_Beg;
            // New
            if (length > 0)
            {
                f_Length = length;
                f_Beg = new TChar[f_Length];
                f_End = f_Beg + f_Length;
                if (preserve && prevChars)
                {
                    TLen minLength = (prevLength < f_Length) ? prevLength : f_Length;
                    TChar* iptr = prevChars;
                    TChar* optr = f_Beg;
                    for (TLen i = 0; i < minLength; ++i)
                        *(optr++) = *(iptr++);
                }
            }
            else
            {
                f_Length = 0;
                f_Beg = nullptr;
                f_End = nullptr;
            }
            // Delete previous
            if (prevChars)
                delete[] prevChars;
        }

        // TODO: bool equals(StringTemplate<TChar, TLen> other, StrCmpLetterOption letterOption = StrCmpLetterOption::Simple)

        // TODO: int compare(StringTemplate<TChar, TLen> other, StrCmpLetterOption letterOption = StrCmpLetterOption::Simple)

        // TODO: StringTemplate<TChar, TLen> append(StringTemplate<TChar, TLen> other) const // May not work

        // TODO: StringTemplate<TChar, TLen> prepend(StringTemplate<TChar, TLen> other) const // May not work

        // TODO: StringTemplate<TChar, TLen> append(const char* cstr) const // May not work

        // TODO: StringTemplate<TChar, TLen> prepend(const char* cstr) const // May not work

        // TODO: StringTemplate<TChar, TLen> substring(TLen start) const // May not work
        
        // TODO: StringTemplate<TChar, TLen> substring(TLen start, TLen length) const // May not work
        
        // TODO: StringTemplate<TChar, TLen> left(TLen length) const // May not work
        
        // TODO: StringTemplate<TChar, TLen> right(TLen length) const // May not work

        // TODO: StringTemplate<TChar, TLen> repeat(TLen amount) // May not work

        /// @brief 
        /// Converts the current string to a C-style string
        /// @param len
        /// Length of resulting string (excluding null terminating character at end); this may be different from the 
        /// length of the current string if null characters are removed.
        /// @param option
        /// Option for converting the current string
        /// @return 
        /// Created C-style string
        /// @note 
        /// Depending on the current string's character type and the implemention of the char type, some characters may be 
        /// modified in the resulting string.
        char* toCStr(TLen& len, CStrNullOption option = CStrNullOption::TruncateNull) const
        {
            TChar* iptr;
            char* optr;
            char* cstr;
            // Allocate memory
            len = f_Length;
            cstr = new char[len + 1];
            // Reset pointers
            iptr = f_Beg;
            optr = cstr;
            // Loop
            TLen nullFirst;
            TLen nullCount = 0;
            for (TLen i = 0; i < f_Length; ++i)
            {
                if (*iptr == 0)
                {
                    if (++nullCount == 1)
                        nullFirst = i;
                }
                *(optr++) = (char)*(iptr++);
            }
            // Handle null characters
            if (nullCount > 0)
            {
                switch (option)
                {
                    case CStrNullOption::TruncateNull:
                        {
                            // Reallocate
                            delete[] cstr;
                            len = nullFirst;
                            cstr = new char[len + 1];
                            // Reset pointers
                            iptr = f_Beg;
                            optr = cstr;
                            // Loop
                            for (TLen i = 0; i < len; ++i)
                                *(optr++) = (char)*(iptr++);
                        }
                        break;
                    case CStrNullOption::RemoveNull:
                        {
                            // Reallocate
                            delete[] cstr;
                            len = f_Length - nullCount;
                            cstr = new char[len + 1];
                            // Reset pointers
                            iptr = f_Beg;
                            optr = cstr;
                            // Loop
                            for (TLen i = 0; i < f_Length; ++i)
                            {
                                if (*iptr != 0)
                                    *(optr++) = (char)*iptr;
                                ++iptr;
                            }
                        }
                        break;
                }
            }
            // Add null terminating character
            *optr = 0;
            // Return
            return cstr;
        }

        /// @brief 
        /// Converts the current string to a C-style string
        /// @param option
        /// Option for converting the current string
        /// @return 
        /// Created C-style string
        /// @note 
        /// Depending on the current string's character type and the implemention of the char type, some characters may be 
        /// modified in the resulting string.
        char* toCStr(CStrNullOption option = CStrNullOption::TruncateNull) const
        {
            TLen len;
            return toCStr(len, option);
        }

        #pragma endregion
    };
}

#endif