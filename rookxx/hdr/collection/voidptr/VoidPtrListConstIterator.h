#include "collection/voidptr/VoidPtrConstIterator.h"
#include "collection/voidptr/VoidPtrList.h"

#ifndef rookxx_collection_voidptr_VoidPtrListConstIterator_h
#define rookxx_collection_voidptr_VoidPtrListConstIterator_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents an iterator thru a list of pointers
    class VoidPtrListConstIterator : public VoidPtrConstIterator
    {
        #pragma region init

        /// @brief Constructor for VoidPtrListConstIterator
        /// @param list List
        /// @note Assume list is not nullptr
        /// @note Also accessed by VoidPtrList
        private: VoidPtrListConstIterator(const VoidPtrList* list);

        /// @brief Copy constructor for VoidPtrListConstIterator
        /// @param src Source
        public: VoidPtrListConstIterator(const VoidPtrListConstIterator& src);

        /// @brief Move constructor for VoidPtrListConstIterator
        /// @param src Source
        public: VoidPtrListConstIterator(VoidPtrListConstIterator&& src);

        /// @brief Destructor for VoidPtrListConstIterator
        public: ~VoidPtrListConstIterator();

        // We won't need these
        public: VoidPtrListConstIterator() = delete;

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrListConstIterator
        /// @param src Source
        /// @return Current instance of VoidPtrListConstIterator
        public: VoidPtrListConstIterator& operator=(const VoidPtrListConstIterator& src);

        /// @brief Move assignment for VoidPtrListConstIterator
        /// @param src Source
        /// @return Current instance of VoidPtrListConstIterator
        public: VoidPtrListConstIterator& operator=(VoidPtrListConstIterator&& src);

        #pragma endregion

        #pragma region friends

        friend VoidPtrList;

        #pragma endregion
        
        #pragma region fields

        private: const VoidPtrList* f_List;
        private: size_t f_Index;
        private: const void* f_Current;

        #pragma endregion

        #pragma region functions

        /// @brief Checks the position of the iterator within the collection. 
        /// If the iterator has reached the end of the collection, false is returned.
        /// If not, then true is returned.
        /// @return False if the iterator has reached the end of the collection; otherwise true
        public: virtual bool notAtEnd() const override;

        /// @brief Moves the iterator to the next pointer
        public: virtual void next() override;

        /// @brief Gets the pointer at the at the current position of the iterator
        /// @return Pointer at the at the current position of the iterator
        public: virtual const void* current() override;

        #pragma endregion
    };
}

#endif