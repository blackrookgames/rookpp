#include "collection/voidptr/VoidPtrConstIterator.h"
#include "collection/voidptr/VoidPtrSegCol.h"

#ifndef rookxx_collection_voidptr_VoidPtrSegColConstIterator_h
#define rookxx_collection_voidptr_VoidPtrSegColConstIterator_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents an iterator thru a segmented collection
    class VoidPtrSegColConstIterator : public VoidPtrConstIterator
    {
        #pragma region init

        /// @brief Constructor for VoidPtrSegColConstIterator
        /// @note Also accessed by VoidPtrSegCol
        private: VoidPtrSegColConstIterator();

        /// @brief Copy constructor for VoidPtrSegColConstIterator
        /// @param src Source
        public: VoidPtrSegColConstIterator(const VoidPtrSegColConstIterator& src);

        /// @brief Move constructor for VoidPtrSegColConstIterator
        /// @param src Source
        public: VoidPtrSegColConstIterator(VoidPtrSegColConstIterator&& src);

        /// @brief Destructor for VoidPtrSegColConstIterator
        public: ~VoidPtrSegColConstIterator();

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrSegColConstIterator
        /// @param src Source
        /// @return Current instance of VoidPtrSegColConstIterator
        public: VoidPtrSegColConstIterator& operator=(const VoidPtrSegColConstIterator& src);

        /// @brief Move assignment for VoidPtrSegColConstIterator
        /// @param src Source
        /// @return Current instance of VoidPtrSegColConstIterator
        public: VoidPtrSegColConstIterator& operator=(VoidPtrSegColConstIterator&& src);
        
        #pragma endregion
        
        #pragma region friends

        friend VoidPtrSegCol;
        
        #pragma endregion
        
        #pragma region fields

        // Also accessed by VoidPtrSegCol
        private: const VoidPtrSegCol* f_SegCol;
        // Also accessed by VoidPtrSegCol
        private: const VoidPtrSegColSegment* f_Prev;
        // Also accessed by VoidPtrSegCol
        private: const VoidPtrSegColSegment* f_Curr;

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