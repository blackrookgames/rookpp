#include <utility>

#ifndef rookxx_collection_AttachableListIterator_h
#define rookxx_collection_AttachableListIterator_h

#define mc_Copy(src) \
    f_Items = src.f_Items; \
    f_Size = src.f_Size; \
    f_Current = src.f_Current; \
    f_Position = src.f_Position;

namespace rookxx::collection
{
#ifndef rookxx_collection_AttachableList_h
    template<typename TItem, typename TIndex>
    class AttachableList;
#endif

    /// @brief Represents an iterator thru a list of attachable items
    /// @tparam TItem Type for attachable items
    /// @tparam TIndex Type for indexing
    /// @note Modifying a list while iterating thru it may corrupt the iterator
    template<typename TItem, typename TIndex>
    class AttachableListIterator
    {
        #pragma region init

        /// @brief Constructor for AttachableListIterator
        /// @param items Array used by list
        /// @param size Size of list
        /// @note Also accessed by AttachableList
        private: AttachableListIterator(TItem** items, TIndex size) :
            f_Items(items),
            f_Size(size),
            f_Current(items),
            f_Position(0)
        { }

        /// @brief Copy constructor for AttachableListIterator
        /// @param src Source
        public: AttachableListIterator(const AttachableListIterator& src)
        {
            mc_Copy(src)
        }

        /// @brief Copy assignment for AttachableListIterator
        /// @param src Source
        public: AttachableListIterator& operator=(const AttachableListIterator& src)
        {
            if (this != &src) { mc_Copy(src) }
            return *this;
        }

        /// @brief Move constructor for AttachableListIterator
        /// @param src Source
        public: AttachableListIterator(AttachableListIterator&& src)
        {
            mc_Copy(src)
        }

        /// @brief Move assignment for AttachableListIterator
        /// @param src Source
        public: AttachableListIterator& operator=(AttachableListIterator&& src)
        {
            if (this != &src) { mc_Copy(src) }
            return *this;
        }

        /// @brief Destructor for AttachableListIterator
        public: virtual ~AttachableListIterator() { }

        // We won't need these
        public: AttachableListIterator() = delete;

        #pragma endregion

        #pragma region operators

        /// @brief Conversion operator to bool
        /// @note This returns false if the iterator has reached the end of the list, returning true if otherwise
        public: operator bool() const
        {
            return f_Position < f_Size;
        }

        /// @brief Prefix increment operator
        /// @note This moves the iterator to the next position in the list
        public: AttachableListIterator& operator++()
        {
            f_Current++;
            f_Position++;
            return *this;
        }

        /// @brief Postfix increment operator
        /// @note This moves the iterator to the next position in the list
        public: AttachableListIterator operator++(int)
        {
            AttachableListIterator temp(*this);
            f_Current++;
            f_Position++;
            return temp;
        }

        /// @brief Dereference operator
        /// @return This returns the item at the current position of the iterator
        public: TItem& operator*()
        {
            return **f_Current;
        }

        /// @brief Dereference operator
        /// @return This returns the item at the current position of the iterator
        public: const TItem& operator*() const
        {
            return **f_Current;
        }

        #pragma endregion

        #pragma region friends

        friend AttachableList<TItem, TIndex>;

        #pragma endregion

        #pragma region fields

        private: TItem** f_Items;
        private: TIndex f_Size;
        
        private: TItem** f_Current;
        private: TIndex f_Position;

        #pragma endregion
    };
}

#endif