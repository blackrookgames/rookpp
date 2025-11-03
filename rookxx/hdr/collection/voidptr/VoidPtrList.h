#include <cstddef>
#include <cstdint>

#ifndef rookxx_collection_voidptr_VoidPtrList_h
#define rookxx_collection_voidptr_VoidPtrList_h

namespace rookxx::collection::voidptr
{
    #ifndef rookxx_collection_voidptr_VoidPtrListIterator_h
    class VoidPtrListIterator;
    #endif

    #ifndef rookxx_collection_voidptr_VoidPtrListConstIterator_h
    class VoidPtrListConstIterator;
    #endif

    /// @brief Represents a list of pointers
    class VoidPtrList
    {
        #pragma region init

        /// @brief Constructor for VoidPtrList
        public: VoidPtrList();

        /// @brief Copy constructor for VoidPtrList
        /// @param src Source
        public: VoidPtrList(const VoidPtrList& src);

        /// @brief Move constructor for VoidPtrList
        /// @param src Source
        public: VoidPtrList(VoidPtrList&& src);

        /// @brief Destructor for VoidPtrList
        public: ~VoidPtrList();

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrList
        /// @param src Source
        /// @return Current instance of VoidPtrList
        public: VoidPtrList& operator=(const VoidPtrList& src);

        /// @brief Move assignment for VoidPtrList
        /// @param src Source
        /// @return Current instance of VoidPtrList
        public: VoidPtrList& operator=(VoidPtrList&& src);

        #pragma endregion

        #pragma region operators

        /// @brief Gets the pointer at the specified index
        /// @param index Index of the pointer
        /// @return Pointer at the specified index
        public: void*& operator[](size_t index);

        /// @brief Gets the pointer at the specified index
        /// @param index Index of the pointer
        /// @return Pointer at the specified index
        public: const void* operator[](size_t index) const;

        #pragma endregion
        
        #pragma region fields

        private: void** f_Array;
        private: size_t f_Capacity;
        private: size_t f_Size;

        #pragma endregion

        #pragma region properties

        /// @brief Current capacity of the list
        public: size_t capacity() const;

        /// @brief Number of pointers within the list 
        public: size_t size() const;

        #pragma endregion

        #pragma region helpers

        /// @brief Copies the elements of the source array into the destination array
        /// @param src Source array
        /// @param dest Destination array
        /// @param count Number of elements to copy
        /// @param index Index of gap; this can be used to leave a gap in the destination array
        /// @note Assume src is not nullptr
        /// @note Assume dest is not nullptr
        /// @note Assume the number of elements in src is greater than or equal to count
        /// @note Assume the number of elements in dest is greater than or equal to count
        /// @note Assume if index is less than count, the number of elements in dest is greater than count
        private: static void m_Copy(void** src, void** dest, size_t count, size_t index);

        /// @brief Removes a gap within the array, shifting following elements
        /// @param array Array
        /// @param oldCount Element count before the gap is removed
        /// @param index Index of gap
        /// @note Assume array is not nullptr
        /// @note Assume index is less than oldCount
        private: static void m_RemoveGap(void** array, size_t oldCount, size_t index);

        /// @brief Inserts a gap within the array, shifting following elements
        /// @param array Array
        /// @param oldCount Element count before the gap is inserted
        /// @param index Index to insert gap
        /// @note Assume array is not nullptr
        /// @note Assume index is less than or equal to oldCount
        private: static void m_InsertGap(void** array, size_t oldCount, size_t index);

        /// @brief Sets a new capacity, reallocating data
        /// @note Assume newCapacity is greater than or equal to size
        private: void m_SetCapacity(size_t newCapacity);

        /// @brief Calculates a new capacity that is larger than the current capacity
        /// @return Calculated capacity
        /// @note This does not change the current capacity. It only calculates a potential new capacity.
        private: size_t m_NewCapacity() const;

        #pragma endregion

        #pragma region functions

        /// @brief Ensures the capacity is greater than or equal to the specified minimum, reallocating if neccessary
        /// @param minCapacity Minimum capacity 
        public: void reserve(size_t minCapacity);

        /// @brief Shrinks the capacity so it fits the number of pointers within the list, reallocating if neccessary
        public: void shrink();

        /// @brief Adds the specified pointer to the list
        /// @param ptr Pointer to add
        public: void add(void* ptr);

        /// @brief Inserts the specified pointer into the list
        /// @param index Index to insert pointer
        /// @param ptr Pointer
        public: void insert(size_t index, void* ptr);

        /// @brief Removes the pointer at the specified index from the list
        /// @param index Index of pointer to remove
        public: void remove(size_t index);

        /// @brief Removes all pointers from the list
        public: void clear();

        /// @brief Creates an iterator thru the list
        /// @return Created iterator thru the list
        public: VoidPtrListIterator getIterator();

        /// @brief Creates an iterator thru the list
        /// @return Created iterator thru the list
        public: VoidPtrListConstIterator getIterator() const;

        #pragma endregion
    };
}

#endif