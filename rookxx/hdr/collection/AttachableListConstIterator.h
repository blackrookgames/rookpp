#include <utility>

#ifndef rookxx_collection_AttachableListConstIterator_h
#define rookxx_collection_AttachableListConstIterator_h

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
    class AttachableListConstIterator
    {
        #pragma region init

        /// @brief Constructor for AttachableListConstIterator
        /// @param items Array used by list
        /// @param size Size of list
        /// @note Also accessed by AttachableList
        private: AttachableListConstIterator(TItem** items, TIndex size) :
            f_Items(items),
            f_Size(size),
            f_Current(items),
            f_Position(0)
        { }

        /// @brief Copy constructor for AttachableListConstIterator
        /// @param src Source
        public: AttachableListConstIterator(const AttachableListConstIterator& src)
        {
            mc_Copy(src)
        }

        /// @brief Copy assignment for AttachableListConstIterator
        /// @param src Source
        public: AttachableListConstIterator& operator=(const AttachableListConstIterator& src)
        {
            if (this != &src) { mc_Copy(src) }
            return *this;
        }

        /// @brief Move constructor for AttachableListConstIterator
        /// @param src Source
        public: AttachableListConstIterator(AttachableListConstIterator&& src)
        {
            mc_Copy(src)
        }

        /// @brief Move assignment for AttachableListConstIterator
        /// @param src Source
        public: AttachableListConstIterator& operator=(AttachableListConstIterator&& src)
        {
            if (this != &src) { mc_Copy(src) }
            return *this;
        }

        /// @brief Destructor for AttachableListConstIterator
        public: virtual ~AttachableListConstIterator() { }

        // We won't need these
        public: AttachableListConstIterator() = delete;

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
        public: AttachableListConstIterator& operator++()
        {
            f_Current++;
            f_Position++;
            return *this;
        }

        /// @brief Postfix increment operator
        /// @note This moves the iterator to the next position in the list
        public: AttachableListConstIterator operator++(int)
        {
            AttachableListConstIterator temp(*this);
            f_Current++;
            f_Position++;
            return temp;
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