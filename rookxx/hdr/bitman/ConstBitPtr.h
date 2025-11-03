#include "bitman/BPtr.h"
#include "bitman/ConstBitPnt.h"

#ifndef rookxx_bitman_ConstBitPtr_h
#define rookxx_bitman_ConstBitPtr_h

namespace rookxx::bitman
{
    /// @brief Represents a bit pointer
    class ConstBitPtr : public BPtr
    {
        #pragma region init

        /// @brief Constructor for ConstBitPtr
        public: ConstBitPtr();
        
        /// @brief Constructor for ConstBitPtr
        /// @param loc Byte location
        /// @param offset Bit offset (0 = most significant bit)
        public: ConstBitPtr(const void* loc, uint8_t offset = 0);
        
        /// @brief Copy constructor for ConstBitPtr
        /// @param src Source
        public: ConstBitPtr(const ConstBitPtr& src);
        
        /// @brief Move constructor for ConstBitPtr
        /// @param src Source
        public: ConstBitPtr(ConstBitPtr&& src);
        
        /// @brief Destructor for ConstBitPtr
        public: ~ConstBitPtr();
        
        /// @brief Copy assignment for ConstBitPtr
        /// @param src Source
        public: ConstBitPtr& operator=(const ConstBitPtr& src);
        
        /// @brief Move assignment for ConstBitPtr
        /// @param src Source
        public: ConstBitPtr& operator=(ConstBitPtr&& src);

        #pragma endregion

        #pragma region fields

        private: ConstBitPnt* f_Pnt;

        #pragma endregion

        #pragma region helper
        
        protected: const uint8_t* p_Loc() const override;

        protected: uint8_t p_Mask() const override;

        #pragma endregion

        #pragma region operator

        /// @brief Dereference operator
        public: ConstBitPnt& operator*();

        /// @brief Dereference operator
        public: const ConstBitPnt& operator*() const;

        /// @brief Prefix increment operator
        public: ConstBitPtr& operator++();
        
        /// @brief Postfix increment operator
        public: ConstBitPtr operator++(int);
        
        /// @brief Prefix decrement operator
        public: ConstBitPtr& operator--();
        
        /// @brief Postfix decrement operator
        public: ConstBitPtr operator--(int);

        #pragma endregion
    };
}

#endif