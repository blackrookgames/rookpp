#include "collection/voidptr/VoidPtrIterator.h"
#include "collection/voidptr/VoidPtrSegCol.h"

#ifndef rookxx_collection_voidptr_VoidPtrSegColIterator_h
#define rookxx_collection_voidptr_VoidPtrSegColIterator_h

namespace rookxx::collection::voidptr
{
    /// @brief Represents an iterator thru a segmented collection
    class VoidPtrSegColIterator : public VoidPtrIterator
    {
        #pragma region init

        /// @brief Constructor for VoidPtrSegColIterator
        /// @note Also accessed by VoidPtrSegCol
        private: VoidPtrSegColIterator();

        /// @brief Copy constructor for VoidPtrSegColIterator
        /// @param src Source
        public: VoidPtrSegColIterator(const VoidPtrSegColIterator& src);

        /// @brief Move constructor for VoidPtrSegColIterator
        /// @param src Source
        public: VoidPtrSegColIterator(VoidPtrSegColIterator&& src);

        /// @brief Destructor for VoidPtrSegColIterator
        public: ~VoidPtrSegColIterator();

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrSegColIterator
        /// @param src Source
        /// @return Current instance of VoidPtrSegColIterator
        public: VoidPtrSegColIterator& operator=(const VoidPtrSegColIterator& src);

        /// @brief Move assignment for VoidPtrSegColIterator
        /// @param src Source
        /// @return Current instance of VoidPtrSegColIterator
        public: VoidPtrSegColIterator& operator=(VoidPtrSegColIterator&& src);
        
        #pragma endregion
        
        #pragma region friends

        friend VoidPtrSegCol;
        
        #pragma endregion
        
        #pragma region fields

        // Also accessed by VoidPtrSegCol
        private: VoidPtrSegCol* f_SegCol;
        // Also accessed by VoidPtrSegCol
        private: VoidPtrSegColSegment* f_Prev;
        // Also accessed by VoidPtrSegCol
        private: VoidPtrSegColSegment* f_Curr;

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