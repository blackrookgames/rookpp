#include "collection/voidptr/VoidPtrIterator.h"
#include "collection/voidptr/VoidPtrList.h"

#ifndef rookxx_collection_voidptr_VoidPtrListIterator_h
#define rookxx_collection_voidptr_VoidPtrListIterator_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents an iterator thru a list of pointers
    class VoidPtrListIterator : public VoidPtrIterator
    {
        #pragma region init

        /// @brief Constructor for VoidPtrListIterator
        /// @param list List
        /// @note Assume list is not nullptr
        /// @note Also accessed by VoidPtrList
        private: VoidPtrListIterator(VoidPtrList* list);

        /// @brief Copy constructor for VoidPtrListIterator
        /// @param src Source
        public: VoidPtrListIterator(const VoidPtrListIterator& src);

        /// @brief Move constructor for VoidPtrListIterator
        /// @param src Source
        public: VoidPtrListIterator(VoidPtrListIterator&& src);

        /// @brief Destructor for VoidPtrListIterator
        public: ~VoidPtrListIterator();

        // We won't need these
        public: VoidPtrListIterator() = delete;

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrListIterator
        /// @param src Source
        /// @return Current instance of VoidPtrListIterator
        public: VoidPtrListIterator& operator=(const VoidPtrListIterator& src);

        /// @brief Move assignment for VoidPtrListIterator
        /// @param src Source
        /// @return Current instance of VoidPtrListIterator
        public: VoidPtrListIterator& operator=(VoidPtrListIterator&& src);

        #pragma endregion

        #pragma region friends

        friend VoidPtrList;

        #pragma endregion
        
        #pragma region fields

        private: VoidPtrList* f_List;
        private: size_t f_Index;
        private: void* f_Current;

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
        public: virtual void* current() override;

        #pragma endregion
    };
}

#endif