#include "collection/voidptr/VoidPtrSegCol.h"

#ifndef rookxx_collection_voidptr_VoidPtrStack_h
#define rookxx_collection_voidptr_VoidPtrStack_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents a stack of pointers
    class VoidPtrStack : public VoidPtrSegCol
    {
        #pragma region init

        /// @brief Constructor for VoidPtrStack
        public: VoidPtrStack();

        /// @brief Copy constructor for VoidPtrStack
        /// @param src Source
        public: VoidPtrStack(const VoidPtrStack& src);

        /// @brief Move constructor for VoidPtrStack
        /// @param src Source
        public: VoidPtrStack(VoidPtrStack&& src);

        /// @brief Destructor for VoidPtrStack
        public: ~VoidPtrStack();

        #pragma endregion

        #pragma region properties

        /// @brief Pointer on the top of the stack 
        public: void* top();
        /// @brief Pointer on the top of the stack 
        public: const void* top() const;

        #pragma endregion

        #pragma region functions

        /// @brief Adds a pointer to the top of the stack
        /// @param ptr Pointer to add
        public: void push(void* ptr);

        /// @brief Removes the pointer at the top of the stack
        /// @return Removed pointer
        public: void* pop();

        #pragma endregion
    };
}

#endif