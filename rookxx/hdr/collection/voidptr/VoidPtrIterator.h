#include <cstddef>
#include <cstdint>

#ifndef rookxx_collection_voidptr_VoidPtrIterator_h
#define rookxx_collection_voidptr_VoidPtrIterator_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents an iterator thru a collection of void pointers
    class VoidPtrIterator
    {
        #pragma region init

        /// @brief Constructor for VoidPtrIterator
        public: VoidPtrIterator();

        /// @brief Destructor for VoidPtrIterator
        public: virtual ~VoidPtrIterator();

        // We won't need these
        public: VoidPtrIterator(const VoidPtrIterator& src) = delete;
        public: VoidPtrIterator(VoidPtrIterator&& src) = delete;

        #pragma endregion

        #pragma region assignment

        // We won't need these
        public: VoidPtrIterator& operator=(const VoidPtrIterator& src) = delete;
        public: VoidPtrIterator& operator=(VoidPtrIterator&& src) = delete;

        #pragma endregion

        #pragma region operators

        /// @brief Conversion to bool operator
        /// @note This operator returns false if the iterator has reached the end of the 
        /// collection, returning true if otherwise.
        public: operator bool();

        /// @brief Conversion to bool operator
        /// @note This operator returns false if the iterator has reached the end of the 
        /// collection, returning true if otherwise.
        public: operator bool() const;

        /// @brief Dereference operator
        /// @note This returns the pointer at the current position of the iterator
        public: void* operator*();

        #pragma endregion

        #pragma region functions

        /// @brief Checks the position of the iterator within the collection. 
        /// If the iterator has reached the end of the collection, false is returned.
        /// If not, then true is returned.
        /// @return False if the iterator has reached the end of the collection; otherwise true
        public: virtual bool notAtEnd() const = 0;

        /// @brief Moves the iterator to the next pointer
        public: virtual void next() = 0;

        /// @brief Gets the pointer at the at the current position of the iterator
        /// @return Pointer at the at the current position of the iterator
        public: virtual void* current() = 0;

        #pragma endregion
    };
}

#endif