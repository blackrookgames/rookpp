#include <cstddef>
#include <cstdint>

#include "collection/voidptr/VoidPtrSegColSegment.h"

#ifndef rookxx_collection_voidptr_VoidPtrSegCol_h
#define rookxx_collection_voidptr_VoidPtrSegCol_h

namespace rookxx::collection::voidptr
{
    #ifndef rookxx_collection_voidptr_VoidPtrSegColConstIterator_h
    class VoidPtrSegColConstIterator;
    #endif
    
    #ifndef rookxx_collection_voidptr_VoidPtrSegColIterator_h
    class VoidPtrSegColIterator;
    #endif

    /// @brief Represents a segmented collection
    class VoidPtrSegCol
    {
        #pragma region init

        /// @brief Constructor for VoidPtrSegCol
        public: VoidPtrSegCol();

        /// @brief Copy constructor for VoidPtrSegCol
        /// @param src Source
        public: VoidPtrSegCol(const VoidPtrSegCol& src);

        /// @brief Move constructor for VoidPtrSegCol
        /// @param src Source
        public: VoidPtrSegCol(VoidPtrSegCol&& src);

        /// @brief Destructor for VoidPtrSegCol
        public: ~VoidPtrSegCol();

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrSegCol
        /// @param src Source
        /// @return Current instance of VoidPtrSegCol
        public: VoidPtrSegCol& operator=(const VoidPtrSegCol& src);

        /// @brief Move assignment for VoidPtrSegCol
        /// @param src Source
        /// @return Current instance of VoidPtrSegCol
        public: VoidPtrSegCol& operator=(VoidPtrSegCol&& src);
        
        #pragma endregion
        
        #pragma region fields

        protected: VoidPtrSegColSegment* f_First;
        protected: VoidPtrSegColSegment* f_Last;
        protected: size_t f_Size;

        #pragma endregion

        #pragma region properties

        /// @brief Number of pointers within the collection
        public: size_t size() const;

        #pragma endregion

        #pragma region helper

        // Assume f_First and f_Last are either nullptr or deleted
        private: void m_CopyFrom(const VoidPtrSegCol& src);
        
        // Assume f_First and f_Last are either nullptr or deleted
        private: void m_MoveFrom(VoidPtrSegCol&& src);

        private: void m_Reset();
        
        #pragma endregion

        #pragma region functions

        /// @brief Inserts a pointer at the specified position
        /// @param position Position within the collection
        /// @param ptr Pointer to insert
        public: void insert(VoidPtrSegColIterator& position, void* ptr);

        /// @brief Removes the pointer at the specified position
        /// @param position Position of pointer to remove
        public: void remove(VoidPtrSegColIterator& position);

        /// @brief Removes all pointers
        public: void clear();

        /// @brief Creates an iterator thru the stack
        /// @return Created iterator thru the stack
        public: VoidPtrSegColIterator getIterator();

        /// @brief Creates an iterator thru the stack
        /// @return Created iterator thru the stack
        public: VoidPtrSegColConstIterator getIterator() const;

        #pragma endregion
    };
}

#endif