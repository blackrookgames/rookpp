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
        
        /// @brief Represents an option for converting to a C-style string
        enum struct CStrOption
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
        }

        #pragma endregion

        #pragma region init

    public:
        
        /// @brief 
        /// Constructor for StringTemplate
        StringTemplate()
        {
            f_Length = 0;
            f_Chars = nullptr;
        }

        /// @brief 
        /// Cosntructor for StringTemplate
        /// @param length 
        /// Length of string
        StringTemplate(TLen length)
        {
            if (length > 0)
            {
                f_Length = length;
                f_Chars = new TChar[f_Length];
            }
            else
            {
                f_Length = 0;
                f_Chars = nullptr;
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
                f_Chars = new TChar[f_Length];
                iptr = cstr;
                optr = f_Chars;
                for (TLen i = 0; i < f_Length; ++i)
                    *(optr++) = *(iptr++);
            }
            else
            {
                f_Chars = nullptr;
            }
        }

        /// @brief 
        /// Destructor for StringTemplate
        virtual ~StringTemplate()
        {
            if (f_Chars)
                delete[] f_Chars;
        }

        #pragma endregion

        #pragma region fields

    private:
        
        TLen f_Length;
        TChar** f_Chars;

        #pragma endregion

        #pragma region properties

    public:
        
        /// @brief 
        /// Length of string
        TLen length() const { return f_Length; }

        #pragma endregion

        #pragma region methods

    public:

        /// @brief 
        /// Gets the character at the specified index
        /// @param index 
        /// Index of character
        /// @return 
        /// The character at the specified index
        /// @note 
        /// Ensure the index is within range, else undefined behaviour may result
        TChar get(TLen index) const
        {
            return f_Chars[index];
        }

        /// @brief 
        /// Sets the character at the specified index
        /// @param index 
        /// Index to set
        /// @param c
        /// Character value
        /// @note 
        /// Ensure the index is within range, else undefined behaviour may result
        void set(TLen index, TChar c)
        {
            f_Chars[index] = c;
        }

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
        char* toCStr(TLen& len, CStrOption option = CStrOption::TruncateNull) const
        {
            TChar* iptr;
            char* optr;
            TChar* cstr;
            // Allocate memory
            len = f_Length;
            cstr = new char[len + 1];
            // Reset pointers
            iptr = f_Chars;
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
                // TODO: Handle
            }
            // Add null terminating character
            *optr = 0;
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
        char* toCStr(CStrOption option = CStrOption::TruncateNull) const
        {
            TLen len;
            return toCStr(len, keepNullChars);
        }

        #pragma endregion
    };
}