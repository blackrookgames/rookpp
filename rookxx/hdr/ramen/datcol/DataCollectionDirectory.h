#include "ramen/datcol/DataCollectionItem.h"

#ifndef rookxx_ramen_datcol_DataCollectionDirectory_h
#define rookxx_ramen_datcol_DataCollectionDirectory_h

namespace rookxx::ramen::datcol
{
#ifndef rookxx_ramen_datcol_DataCollection_h
    class DataCollection;
#endif

    /// @brief Represents a directory within a data collection
    class DataCollectionDirectory : public DataCollectionItem
    {
        #pragma region init

    private:
        /// @brief Constructor for DataCollectionDirectory
        /// @param isRoot Whether or not directory is a root directory
        /// @param deleteOnDisown Whether or not to delete item when disowned by parent directory
        /// @note Also accessed by DataCollection
        DataCollectionDirectory(bool isRoot, bool deleteOnDisown);

    public:
        
        /// @brief Constructor for DataCollectionDirectory
        /// @param deleteOnDisown Whether or not to delete item when disowned by parent directory
        DataCollectionDirectory(bool deleteOnDisown = false);
        
        /// @brief Destructor for DataCollectionDirectory
        virtual ~DataCollectionDirectory();

        // We won't need these
        DataCollectionDirectory(const DataCollectionDirectory& src) = delete;
        DataCollectionDirectory(DataCollectionDirectory&& src) = delete;
        DataCollectionDirectory& operator=(const DataCollectionDirectory& src) = delete;
        DataCollectionDirectory& operator=(DataCollectionDirectory&& src) = delete;

        #pragma endregion

        #pragma region friends

        friend DataCollection;

        #pragma endregion

        #pragma region fields

    private:

        bool f_IsRoot;

        #pragma endregion

        #pragma region properties

    public:

        /// @brief Whether or not the item is a file
        /// @note For DataCollectionDirectory, this will always return false
        bool isFile() const override;
        
        /// @brief Whether or not the item is a directory
        /// @note For DataCollectionDirectory, this will always return true
        bool isDirectory() const override;
        
        /// @brief Whether or not the item is a root directory
        bool isRoot() const override;

        #pragma endregion
    };
}

#endif