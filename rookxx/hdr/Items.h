#ifndef rookxx_Items_h
#define rookxx_Items_h

#define mc_CopyArray(iptr, optr, i) \
    if (src.f_Array) \
    { \
        f_Array = new T*[src.f_Capacity]; \
        T** iptr = src.f_Array; \
        T** optr = f_Array; \
        for (uint16_t i = 0; i < src.f_Size; i++) \
            *(optr++) = new T(**(iptr++)); \
    } \
    else f_Array = nullptr; \
    f_Capacity = src.f_Capacity; \
    f_Size = src.f_Size;

#define mc_MoveArray \
    /*Set*/ \
    f_Array = src.f_Array; \
    f_Capacity = src.f_Capacity; \
    f_Size = src.f_Size; \
    /*Reset*/ \
    f_Array = nullptr; \
    f_Capacity = 0; \
    f_Size = 0;

#define mc_DeleteArray(ptr, i) \
    T** ptr = f_Array; \
    for (uint16_t i = 0; i < f_Size; i++) \
        delete *(ptr++); \
    delete[] f_Array;

#define mc_CDeleteArray(newArray, iptr, optr, i) \
    T** iptr = f_Array; \
    T** optr = newArray; \
    for (uint16_t i = 0; i < f_Size; i++) \
        *(optr++) = *(iptr++); \
    delete[] f_Array;

#define mc_NewCap(newCap) \
    if (f_Size == maxCapacity) return; \
    int newCap = ((int)f_Capacity << 1) | 1; \
    if (newCap > maxCapacity) \
        newCap = maxCapacity; \

#define mc_FixCap_Add(newCap, newArray, iptr, optr, i) \
    if (f_Size == f_Capacity) \
    { \
        /*Determine new capacity*/ \
        mc_NewCap(newCap) \
        /*Reallocate*/ \
        T** newArray = new T*[newCap]; \
        if (f_Array) \
        { \
            T** iptr = f_Array; \
            T** optr = newArray; \
            for (uint16_t i = 0; i < f_Size; i++) \
                *(optr++) = *(iptr++); \
            delete[] f_Array; \
        } \
        f_Array = newArray; \
        f_Capacity = newCap; \
    }

#define mc_FixCap_Ins(newCap, newArray, iptr, optr, i) \
    if (f_Size == f_Capacity) \
    { \
        /*Determine new capacity*/ \
        mc_NewCap(newCap) \
        /*Reallocate*/ \
        T** newArray = new T*[newCap]; \
        if (f_Array) \
        { \
            T** iptr = f_Array; \
            T** optr = newArray; \
            uint16_t i = 0; \
            while (i < index) \
            { \
                *(optr++) = *(iptr++); \
                i++; \
            } \
            optr++; \
            while (i < f_Size) \
            { \
                *(optr++) = *(iptr++); \
                i++; \
            } \
            delete[] f_Array; \
        } \
        f_Array = newArray; \
        f_Capacity = newCap; \
    } \
    else if (index < f_Size) \
    { \
        T** optr = f_Array + f_Size; \
        T** iptr = optr - 1; \
        for (uint16_t i = index; i < f_Size; i++) \
            *(optr--) = *(iptr--); \
    }

namespace helper
{
    /// @brief Represents a list of items
    /// @tparam T Item type
    template<typename T>
    class Items
    {
        #pragma region init

        /// @brief Constructor for Items
        public: Items()
        {
            f_Array = nullptr;
            f_Capacity = 0;
            f_Size = 0;
        }

        /// @brief Copy constructor for Items
        /// @param src Source
        public: Items(const Items& src)
        {
            mc_CopyArray(iptr, optr, i);
        }

        /// @brief Move constructor for Items
        /// @param src Source
        public: Items(Items&& src)
        {
            mc_MoveArray
        }

        /// @brief Destructor for Items
        public: ~Items()
        {
            if (f_Array) { mc_DeleteArray(ptr, i) }
            f_Array = nullptr;
            f_Capacity = 0;
            f_Size = 0;
        }

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for Items
        /// @param src Source
        /// @return Current instance of Items
        public: Items<T>& operator=(const Items<T>& src)
        {
            if (this != &src)
            {
                if (f_Array) { mc_DeleteArray(ptr, i) }
                mc_CopyArray(iptr, optr, i)
            }
            return *this;
        }

        /// @brief Move assignment for Items
        /// @param src Source
        /// @return Current instance of Items
        public: Items<T>& operator=(Items<T>&& src)
        {
            if (this != &src)
            {
                if (f_Array) { mc_DeleteArray(ptr, i) }
                mc_MoveArray
            }
            return *this;
        }

        #pragma endregion

        #pragma region const

        /// @brief Maximum capacity of a list
        public: static const uint16_t maxCapacity = 0xFFFF;

        #pragma endregion

        #pragma region fields

        private: T** f_Array;
        private: uint16_t f_Capacity;
        private: uint16_t f_Size;

        #pragma endregion

        #pragma properties

        #pragma region properties

        /// @brief Current capacity of the list
        public: uint16_t capacity() const { return f_Capacity; }

        /// @brief Number of items within the list 
        public: uint16_t size() const { return f_Size; }

        #pragma endregion

        #pragma region operators

        /// @brief Gets a reference to the item at the specified index
        /// @param index Index of the item
        /// @return A reference to the item at the specified index
        public: T& operator[](uint16_t index)
        {
            return *f_Array[index];
        }

        /// @brief Gets a reference to the item at the specified index
        /// @param index Index of the item
        /// @return A reference to the item at the specified index
        public: const T& operator[](uint16_t index) const
        {
            return *f_Array[index];
        }

        #pragma endregion

        #pragma region functions

        /// @brief Ensures the capacity is greater than or equal to the specified minimum, reallocating if neccessary
        /// @param minCapacity Minimum capacity 
        public: void reserve(uint16_t minCapacity)
        {
            if (f_Capacity >= minCapacity) return;
            T** newArray = new T*[minCapacity];
            if (f_Array) { mc_CDeleteArray(newArray, iptr, optr, i) }
            f_Array = newArray;
            f_Capacity = minCapacity;
        }

        /// @brief Shrinks the capacity so it fits the items within the list, reallocating if neccessary
        public: void shrink()
        {
            if (f_Capacity == f_Size) return;
            T** newArray = new T*[f_Size];
            if (f_Array) { mc_CDeleteArray(newArray, iptr, optr, i) }
            f_Array = newArray;
            f_Capacity = f_Size;
        }

        /// @brief Adds a copy of the source item to the list
        /// @param src Source item
        public: void add(const T& src)
        {
            mc_FixCap_Add(newCap, newArray, iptr, optr, i)
            f_Array[f_Size++] = new T(src);
        }

        /// @brief Adds the source item to the list
        /// @param src Source item
        public: void add(T&& src)
        {
            mc_FixCap_Add(newCap, newArray, iptr, optr, i)
            f_Array[f_Size++] = new T(std::move(src));
        }

        /// @brief Inserts a copy of the source item into the list
        /// @param index Index to insert item
        /// @param src Source item
        public: void insert(uint16_t index, const T& src)
        {
            if (index > f_Size) return;
            mc_FixCap_Ins(newCap, newArray, iptr, optr, i)
            f_Array[index] = new T(src);
            f_Size++;
        }

        /// @brief Inserts a the source item into the list
        /// @param index Index to insert item
        /// @param src Source item
        public: void insert(uint16_t index, T&& src)
        {
            if (index > f_Size) return;
            mc_FixCap_Ins(newCap, newArray, iptr, optr, i)
            f_Array[index] = new T(std::move(src));
            f_Size++;
        }

        /// @brief Removes the item at the specified index from the list
        /// @param index Index of item to remove
        /// @return Removed item
        public: T remove(uint16_t index)
        {
            if (index >= f_Size) return T();
            //Retrieve item
            T* ptr = f_Array[index];
            T item = std::move(*ptr);
            delete ptr;
            //Fix list
            f_Size--;
            {
                T** optr = f_Array + index;
                T** iptr = optr + 1;
                for (uint16_t i = index; i < f_Size; i++)
                    *(optr++) = *(iptr++);
            }
            //Return
            return item;
        }

        public: void clear()
        {
            if (!f_Array) return;
            T** ptr = f_Array;
            for (uint16_t i = 0; i < f_Size; i++)
                delete *(ptr++);
            f_Size = 0;
        }

        #pragma endregion
    };
}

#undef mc_FixCap_Ins
#undef mc_FixCap_Add
#undef mc_NewCap
#undef mc_CDeleteArray
#undef mc_DeleteArray
#undef mc_MoveArray
#undef mc_CopyArray

#endif