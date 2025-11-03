#include <cstddef>
#include <cstdint>

#ifndef rookxx_bitman_BitPnt_h
#define rookxx_bitman_BitPnt_h

namespace rookxx::bitman
{
#ifndef rookxx_bitman_BitPtr_h
    class BitPtr;
#endif

    /// @brief Represents a bit point
    class BitPnt
    {
        #pragma region init

        /// @brief Constructor for BitPnt
        /// @note Also accessed by BitPtr
        private: BitPnt();

        /// @brief Constructor for BitPnt
        /// @param loc Byte location
        /// @param offset Bit offset (0 = most significant bit)
        /// @note Also accessed by BitPtr
        private: BitPnt(void* loc, uint8_t offset);

        /// @brief Copy constructor for BitPnt
        /// @param src Source
        /// @note Also accessed by BitPtr
        private: BitPnt(const BitPnt& src);

        /// @brief Destructor for BitPnt
        /// @note Also accessed by BitPtr
        private: ~BitPnt();

        /// @brief Copy assignment for BitPnt
        /// @param src Source
        /// @note Also accessed by BitPtr
        private: BitPnt& operator=(const BitPnt& src);

        // We won't need these
        public: BitPnt(BitPnt&& src) = delete;
        public: BitPnt& operator=(BitPnt&& src) = delete;

        #pragma endregion

        #pragma region friends

        friend BitPtr;

        #pragma endregion

        #pragma region fields

        private: uint8_t* f_Loc; // Also accessed (but not modified) by BitPtr
        private: uint8_t f_Mask; // Also accessed (but not modified) by BitPtr
        private: bool f_Value;

        #pragma endregion

        #pragma region operators

        /// @brief Conversion operator to bool
        public: operator bool() const;

        /// @brief Assignment operator from bool
        /// @param value Value
        public: BitPnt& operator=(bool value);

        #pragma endregion

        #pragma region helper

        // Also accessed by BitPtr
        private: void m_Inc();

        // Also accessed by BitPtr
        private: void m_Dec();

        #pragma endregion
    };
}

#endif