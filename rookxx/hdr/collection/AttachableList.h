#include "collection/AttachableListIterator.h"
#include "collection/AttachableListConstIterator.h"

#ifndef rookxx_collection_AttachableList_h
#define rookxx_collection_AttachableList_h

namespace rookxx::collection
{
    /// @brief Represents a list of attachable items
    /// @tparam TItem Type for attachable items
    /// @tparam TIndex Type for indexing
    /// @note Items are not automatically cleared during destruction.
    /// @note They can be cleared by calling clear() during a derived class' destructor.
    template<typename TItem, typename TIndex>
    class AttachableList
    {
        #pragma region init

        /// @brief Constructor for AttachableList
        protected: AttachableList() :
            f_Capacity(0),
            f_Items(nullptr),
            f_Size(0)
        { }

        /// @brief Destructor for AttachableList
        protected: virtual ~AttachableList()
        {
            if (f_Items) delete[] f_Items;
            f_Capacity = 0;
            f_Items = nullptr;
            f_Size = 0;
        }

        // We won't need these
        public: AttachableList(const AttachableList& src) = delete;
        public: AttachableList& operator=(const AttachableList& src) = delete;
        public: AttachableList(AttachableList&& src) = delete;
        public: AttachableList& operator=(AttachableList&& src) = delete;

        #pragma endregion

        #pragma region operators

        /// @brief Gets the item at the specified index
        /// @param index Index of the item
        /// @return Item at the specified index
        public: TItem& operator[](TIndex index)
        {
            return *f_Items[index];
        }
        
        /// @brief Gets the item at the specified index
        /// @param index Index of the item
        /// @return Item at the specified index
        public: const TItem& operator[](TIndex index) const
        {
            return *f_Items[index];
        }

        #pragma endregion

        #pragma region fields

        private: TIndex f_Capacity;
        private: TItem** f_Items;
        private: TIndex f_Size;

        #pragma endregion

        #pragma region properties

        /// @brief Current capacity of the list
        public: TIndex capacity() const { return f_Capacity; }

        /// @brief Current size of the list
        public: TIndex size() const { return f_Size; }

        #pragma endregion

        #pragma region helper

        /// @brief Attempts to attach the specified item
        /// @param item Item to attach
        /// @return Whether or not successful
        protected: virtual bool m_AttachItem(TItem& item) = 0;

        /// @brief Detaches the specified item
        /// @param item Item to detach
        protected: virtual void m_DetachItem(TItem& item) = 0;

        // Assume capacity >= 0
        private: void m_SetCapacity(TIndex capacity)
        {
            // Note old
            TIndex prevCapacity = f_Capacity;
            TItem** prevItems = f_Items;
            // Create new
            f_Capacity = capacity;
            f_Items = (capacity == 0) ? nullptr : (new TItem*[capacity]);
            // Copy
            if (prevItems && f_Items)
            {
                TItem** iptr = prevItems;
                TItem** optr = f_Items;
                for (TIndex i = 0; i < f_Size; i++)
                    *(optr++) = *(iptr++);
                delete[] prevItems;
            }
        }

        private: bool m_MaxxedOut() const
        {
            return (f_Size + 1) < f_Size;
        }

        // Assume m_MaxxedOut() returns false
        // Assume index >= 0 && index <= f_Size
        // Assume item
        // Assume item has been attached
        private: void m_Insert(TIndex index, TItem* item)
        {
            // Does capacity need to be adjusted?
            if (f_Size == f_Capacity)
            {
                // Does an array exist
                if (f_Items)
                {
                    TIndex prevCapacity = f_Capacity;
                    TItem** prevItems = f_Items;
                    // Determine new capacity
                    f_Capacity = prevCapacity << 1;
                    if (f_Capacity < prevCapacity) // Check for overflow
                    {
                        f_Capacity = ~0; // Works for unsigned but not for signed
                        // Is index type signed?
                        if (f_Capacity < 0)
                        {
                            f_Capacity = 1;
                            while (f_Capacity > 0)
                                f_Capacity <<= 1;
                            f_Capacity = ~f_Capacity;
                        }
                    }
                    // Create new array
                    f_Items = new TItem*[f_Capacity];
                    // Before
                    TItem** iptr = prevItems;
                    TItem** optr = f_Items;
                    for (TIndex i = 0; i < index; i++)
                        *(optr++) = *(iptr++);
                    // Insert
                    *(optr++) = item;
                    // After
                    for (TIndex i = index; i < f_Size; i++)
                        *(optr++) = *(iptr++);
                    // Adjust size
                    f_Size++;
                    // Delete old array
                    delete[] prevItems;
                }
                // It doesn't. Create one
                else
                {
                    f_Capacity = 1;
                    f_Items = new TItem*[f_Capacity];
                    // Insert item
                    *f_Items = item;
                    // Adjust size
                    f_Size++;
                }
            }
            // Capacity does not need to be adjusted
            else
            {
                // Adjust items
                TItem** optr = f_Items + f_Size;
                TItem** iptr = optr - 1;
                for (TIndex i = index; i < f_Size; i++)
                    *(optr--) = *(iptr--);
                // Insert item
                *optr = item;
                // Adjust size
                f_Size++;
            }
        }

        // Assume index >= 0 && index < f_Size
        private: TItem* m_Remove(TIndex index)
        {
            // Adjust size
            f_Size--;
            // Adjust items
            TItem** optr = f_Items + index;
            TItem** iptr = optr + 1;
            TItem* item = *optr;
            for (TIndex i = index; i < f_Size; i++)
                *(optr++) = *(iptr++);
            // Return
            return item;
        }

        #pragma endregion

        #pragma region functions

        /// @brief Creates an iterator thru the list
        /// @return Created iterator thru the list
        /// @note Modifying the list while iterating thru it may corrupt the iterator
        public: AttachableListIterator<TItem, TIndex> getIterator()
        {
            return AttachableListIterator<TItem, TIndex>(f_Items, f_Size);
        }

        /// @brief Creates an iterator thru the list
        /// @return Created iterator thru the list
        /// @note Modifying the list while iterating thru it may corrupt the iterator
        public: AttachableListConstIterator<TItem, TIndex> getIterator() const
        {
            return AttachableListConstIterator<TItem, TIndex>(f_Items, f_Size);
        }

        /// @brief Expands the capacity to the specified capacity, reallocating if neccessary
        /// @param capacity Minimum capacity
        /// @note If the current capacity is greater than or equal to the specified capacity, nothing happens
        public: void expand(TIndex capacity)
        {
            if (f_Capacity >= capacity)
                return;
            m_SetCapacity(capacity);
        }

        /// @brief Shrinks the capacity so it fits the list's size, reallocating if neccessary
        public: void shrink()
        {
            if (f_Capacity == f_Size)
                return;
            m_SetCapacity(f_Size);
        }

        /// @brief Attempts to add the specified item to the list
        /// @param item Item to add
        /// @return Whether or not successful
        public: bool add(TItem& item)
        {
            if (m_MaxxedOut()) return false;
            if (!m_AttachItem(item)) return false;
            m_Insert(f_Size, &item);
            return true;
        }

        /// @brief Attempts to insert the specified item to the list
        /// @param index Index to insert item
        /// @param item Item to insert
        /// @return Whether or not successful
        public: bool insert(TIndex index, TItem& item)
        {
            if (m_MaxxedOut()) return false;
            if (index < 0 || index > f_Size) return false;
            if (!m_AttachItem(item)) return false;
            m_Insert(index, &item);
            return true;
        }

        /// @brief Attempts to remove the specified item from the list
        /// @param item Item to remove
        /// @return Whether or not successful
        /// @note This determines matches based on the memory position of the item
        public: bool remove(TItem& item)
        {
            TItem** ptr = f_Items;
            for (TIndex i = 0; i < f_Size; i++)
            {
                if (*(ptr++) != &item)
                    continue;
                m_Remove(i);
                m_DetachItem(item);
                return true;
            }
            return false;
        }

        /// @brief Attempts to remove item at the specified index from the list
        /// @param index Index of item to remove
        /// @return Whether or not successful
        public: bool remove(TIndex index)
        {
            if (index < 0 || index >= f_Size)
                return false;
            TItem* item = m_Remove(index);
            m_DetachItem(*item);
            return true;
        }

        /// @brief Removes all items from the list
        public: void clear()
        {
            TIndex prevSize = f_Size;
            f_Size = 0;
            TItem** ptr = f_Items;
            for (TIndex i = 0; i < prevSize; i++)
                m_DetachItem(**(ptr++));
        }

        #pragma endregion
    };
}

#endif