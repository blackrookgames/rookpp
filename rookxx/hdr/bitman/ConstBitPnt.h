#include <cstddef>
#include <cstdint>

#ifndef rookxx_bitman_ConstBitPnt_h
#define rookxx_bitman_ConstBitPnt_h

namespace rookxx::bitman
{
#ifndef rookxx_bitman_ConstBitPtr_h
    class ConstBitPtr;
#endif

    /// @brief Represents a bit point
    class ConstBitPnt
    {
        #pragma region init

        /// @brief Constructor for ConstBitPnt
        /// @note Also accessed by ConstBitPtr
        private: ConstBitPnt();

        /// @brief Constructor for ConstBitPnt
        /// @param loc Byte location
        /// @param offset Bit offset (0 = most significant bit)
        /// @note Also accessed by ConstBitPtr
        private: ConstBitPnt(const void* loc, uint8_t offset);

        /// @brief Copy constructor for ConstBitPnt
        /// @param src Source
        /// @note Also accessed by ConstBitPtr
        private: ConstBitPnt(const ConstBitPnt& src);

        /// @brief Destructor for ConstBitPnt
        /// @note Also accessed by ConstBitPtr
        private: ~ConstBitPnt();

        /// @brief Copy assignment for ConstBitPnt
        /// @param src Source
        /// @note Also accessed by ConstBitPtr
        private: ConstBitPnt& operator=(const ConstBitPnt& src);

        // We won't need these
        public: ConstBitPnt(ConstBitPnt&& src) = delete;
        public: ConstBitPnt& operator=(ConstBitPnt&& src) = delete;

        #pragma endregion

        #pragma region friends

        friend ConstBitPtr;

        #pragma endregion

        #pragma region fields

        private: const uint8_t* f_Loc; // Also accessed (but not modified) by ConstBitPtr
        private: uint8_t f_Mask; // Also accessed (but not modified) by ConstBitPtr
        private: bool f_Value;

        #pragma endregion

        #pragma region operators

        /// @brief Conversion operator to bool
        public: operator bool() const;

        #pragma endregion

        #pragma region helper

        // Also accessed by ConstBitPtr
        private: void m_Inc();

        // Also accessed by ConstBitPtr
        private: void m_Dec();

        #pragma endregion
    };
}

#endif