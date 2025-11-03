#include <cstddef>
#include <cstdint>

#ifndef rookxx_bitman_BPtr_h
#define rookxx_bitman_BPtr_h

namespace rookxx::bitman
{
    /// @brief Base class for represents a bit pointer
    class BPtr
    {
        friend bool operator==(const BPtr& a, const BPtr& b);
        friend bool operator!=(const BPtr& a, const BPtr& b);
        friend bool operator<(const BPtr& a, const BPtr& b);
        friend bool operator>(const BPtr& a, const BPtr& b);
        friend bool operator<=(const BPtr& a, const BPtr& b);
        friend bool operator>=(const BPtr& a, const BPtr& b);

        /// @brief Byte location
        protected: virtual const uint8_t* p_Loc() const = 0;

        /// @brief Bit mask
        /// @note Bit significance decreases as bit offset increases
        protected: virtual uint8_t p_Mask() const = 0;

        // Also accessed by operators
        private: int m_Cmp(const BPtr& other) const
        {
            // Compare byte address
            if (p_Loc() < other.p_Loc()) return -1;
            if (p_Loc() > other.p_Loc()) return 1;
            // Compare bit offset (more significant mask means lower offset)
            if (p_Mask() > other.p_Mask()) return -1;
            if (p_Mask() < other.p_Mask()) return 1;
            // Equal
            return 0;
        }
    };

    /// @brief Checks if the two bit pointers point to the same bit
    /// @param a Bit pointer A
    /// @param b Bit pointer B
    /// @return Whether or not the two bit pointers point to the same bit
    inline bool operator==(const BPtr& a, const BPtr& b) { return a.m_Cmp(b) == 0; }

    /// @brief Checks if two bit pointers point to different bits
    /// @param a Bit pointer A
    /// @param b Bit pointer B
    /// @return Whether or not the two bit pointers point to different bits
    inline bool operator!=(const BPtr& a, const BPtr& b) { return a.m_Cmp(b) != 0; }
    
    /// @brief Checks if bit pointer A precedes bit pointer B
    /// @param a Bit pointer A
    /// @param b Bit pointer B
    /// @return Whether or not bit pointer A precedes bit pointer B
    inline bool operator<(const BPtr& a, const BPtr& b) { return a.m_Cmp(b) < 0; }

    /// @brief Checks if bit pointer A follows bit pointer B
    /// @param a Bit pointer A
    /// @param b Bit pointer B
    /// @return Whether or not bit pointer A follows bit pointer B
    inline bool operator>(const BPtr& a, const BPtr& b) { return a.m_Cmp(b) > 0; }
    
    /// @brief Checks if bit pointer A precedes or points to the same bit as bit pointer B
    /// @param a Bit pointer A
    /// @param b Bit pointer B
    /// @return Whether or not bit pointer A precedes or points to the same bit as bit pointer B
    inline bool operator<=(const BPtr& a, const BPtr& b) { return a.m_Cmp(b) <= 0; }

    /// @brief Checks if bit pointer A follows or points to the same bit as bit pointer B
    /// @param a Bit pointer A
    /// @param b Bit pointer B
    /// @return Whether or not bit pointer A follows or points to the same bit as bit pointer B
    inline bool operator>=(const BPtr& a, const BPtr& b) { return a.m_Cmp(b) >= 0; }
}

#endif