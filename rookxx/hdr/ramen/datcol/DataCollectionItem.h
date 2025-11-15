#include <cstddef>
#include <cstdint>

#include "ramen/String8.h"

#ifndef rookxx_ramen_datcol_DataCollectionItem_h
#define rookxx_ramen_datcol_DataCollectionItem_h

namespace rookxx::ramen::datcol
{
#ifndef rookxx_ramen_datcol_DataCollectionDirectory_h
    class DataCollectionDirectory;
#endif

    /// @brief Represents an item within a data collection
    class DataCollectionItem
    {
        #pragma region init

    public:
        
        /// @brief Constructor for DataCollectionItem
        /// @param deleteOnDisown Whether or not to delete item when disowned by parent directory
        DataCollectionItem(bool deleteOnDisown);
        
        /// @brief Destructor for DataCollectionItem
        virtual ~DataCollectionItem();

        // We won't need these
        DataCollectionItem(const DataCollectionItem& src) = delete;
        DataCollectionItem(DataCollectionItem&& src) = delete;
        DataCollectionItem& operator=(const DataCollectionItem& src) = delete;
        DataCollectionItem& operator=(DataCollectionItem&& src) = delete;

        #pragma endregion

        #pragma region fields

    private:

        bool f_Deleted;

        DataCollectionDirectory* f_Parent;

        bool f_DeleteOnDisown;

        rookxx::ramen::String8 f_Name;

        #pragma endregion

        #pragma region properties

    public:

        /// @brief Whether or not the item is a file
        virtual bool isFile() const = 0;
        
        /// @brief Whether or not the item is a directory
        virtual bool isDirectory() const = 0;
        
        /// @brief Whether or not the item is a root directory
        virtual bool isRoot() const = 0;
        
        /// @brief Parent directory
        DataCollectionDirectory* parent();
        /// @brief Parent directory
        const DataCollectionDirectory* parent() const;

        /// @brief Whether or not to delete item when disowned by parent directory
        bool deleteOnDisown() const;
        /// @brief Whether or not to delete item when disowned by parent directory
        void deleteOnDisown(bool value);

        /// @brief Name of the item
        const rookxx::ramen::String8& name() const;

        #pragma endregion

        #pragma region functions

    public:

        /// @brief Attempts to rename the item
        /// @param name New name for item
        /// @return Whether or not successful
        bool rename(const rookxx::ramen::String8& name);

        /// @brief Attempts to rename the item
        /// @param name New name for item
        /// @return Whether or not successful
        bool rename(rookxx::ramen::String8&& name);

        #pragma endregion
    };
}

#endif