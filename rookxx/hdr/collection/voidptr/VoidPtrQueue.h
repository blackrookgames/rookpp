#include "collection/voidptr/VoidPtrSegCol.h"

#ifndef rookxx_collection_voidptr_VoidPtrQueue_h
#define rookxx_collection_voidptr_VoidPtrQueue_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents a queue of pointers
    class VoidPtrQueue : public VoidPtrSegCol
    {
        #pragma region init

        /// @brief Constructor for VoidPtrQueue
        public: VoidPtrQueue();

        /// @brief Copy constructor for VoidPtrQueue
        /// @param src Source
        public: VoidPtrQueue(const VoidPtrQueue& src);

        /// @brief Move constructor for VoidPtrQueue
        /// @param src Source
        public: VoidPtrQueue(VoidPtrQueue&& src);

        /// @brief Destructor for VoidPtrQueue
        public: ~VoidPtrQueue();

        #pragma endregion

        #pragma region properties

        /// @brief Pointer at the front of the queue 
        public: void* front();
        /// @brief Pointer at the front of the queue
        public: const void* front() const;

        #pragma endregion

        #pragma region functions

        /// @brief Adds a pointer to the back of the queue
        /// @param ptr Pointer to add
        public: void push(void* ptr);

        /// @brief Removes the pointer at the front of the queue
        /// @return Removed pointer
        public: void* pop();

        #pragma endregion
    };
}

#endif