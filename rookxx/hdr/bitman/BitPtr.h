#include "bitman/BitPnt.h"
#include "bitman/BPtr.h"

#ifndef rookxx_bitman_BitPtr_h
#define rookxx_bitman_BitPtr_h

namespace rookxx::bitman
{
    /// @brief Represents a bit pointer
    class BitPtr : public BPtr
    {
        #pragma region init

        /// @brief Constructor for BitPtr
        public: BitPtr();
        
        /// @brief Constructor for BitPtr
        /// @param loc Byte location
        /// @param offset Bit offset (0 = most significant bit)
        public: BitPtr(void* loc, uint8_t offset = 0);
        
        /// @brief Copy constructor for BitPtr
        /// @param src Source
        public: BitPtr(const BitPtr& src);
        
        /// @brief Move constructor for BitPtr
        /// @param src Source
        public: BitPtr(BitPtr&& src);
        
        /// @brief Destructor for BitPtr
        public: ~BitPtr();
        
        /// @brief Copy assignment for BitPtr
        /// @param src Source
        public: BitPtr& operator=(const BitPtr& src);
        
        /// @brief Move assignment for BitPtr
        /// @param src Source
        public: BitPtr& operator=(BitPtr&& src);

        #pragma endregion

        #pragma region fields

        private: BitPnt* f_Pnt;

        #pragma endregion

        #pragma region helper
        
        protected: const uint8_t* p_Loc() const override;

        protected: uint8_t p_Mask() const override;

        #pragma endregion

        #pragma region operator

        /// @brief Dereference operator
        public: BitPnt& operator*();

        /// @brief Dereference operator
        public: const BitPnt& operator*() const;

        /// @brief Prefix increment operator
        public: BitPtr& operator++();
        
        /// @brief Postfix increment operator
        public: BitPtr operator++(int);
        
        /// @brief Prefix decrement operator
        public: BitPtr& operator--();
        
        /// @brief Postfix decrement operator
        public: BitPtr operator--(int);

        #pragma endregion
    };
}

#endif