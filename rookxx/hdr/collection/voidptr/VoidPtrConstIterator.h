#include <cstddef>
#include <cstdint>

#ifndef rookxx_collection_voidptr_VoidPtrConstIterator_h
#define rookxx_collection_voidptr_VoidPtrConstIterator_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents an iterator thru a collection of constant void pointers
    class VoidPtrConstIterator
    {
        #pragma region init

        /// @brief Constructor for VoidPtrConstIterator
        public: VoidPtrConstIterator();

        /// @brief Destructor for VoidPtrConstIterator
        public: virtual ~VoidPtrConstIterator();

        // We won't need these
        public: VoidPtrConstIterator(const VoidPtrConstIterator& src) = delete;
        public: VoidPtrConstIterator(VoidPtrConstIterator&& src) = delete;

        #pragma endregion

        #pragma region assignment

        // We won't need these
        public: VoidPtrConstIterator& operator=(const VoidPtrConstIterator& src) = delete;
        public: VoidPtrConstIterator& operator=(VoidPtrConstIterator&& src) = delete;

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
        public: const void* operator*();

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
        public: virtual const void* current() = 0;

        #pragma endregion
    };
}

#endif