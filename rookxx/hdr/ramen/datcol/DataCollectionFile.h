#include "ramen/datcol/DataCollectionItem.h"

#ifndef rookxx_ramen_datcol_DataCollectionFile_h
#define rookxx_ramen_datcol_DataCollectionFile_h

namespace rookxx::ramen::datcol
{
    /// @brief Represents a file within a data collection
    class DataCollectionFile : public DataCollectionItem
    {
        #pragma region init

    public:
        
        /// @brief Constructor for DataCollectionFile
        /// @param deleteOnDisown Whether or not to delete item when disowned by parent directory
        DataCollectionFile(bool deleteOnDisown = false);
        
        /// @brief Destructor for DataCollectionFile
        virtual ~DataCollectionFile();

        // We won't need these
        DataCollectionFile(const DataCollectionFile& src) = delete;
        DataCollectionFile(DataCollectionFile&& src) = delete;
        DataCollectionFile& operator=(const DataCollectionFile& src) = delete;
        DataCollectionFile& operator=(DataCollectionFile&& src) = delete;

        #pragma endregion

        #pragma region properties

    public:

        /// @brief Whether or not the item is a file
        /// @note For DataCollectionFile, this will always return true
        bool isFile() const override;
        
        /// @brief Whether or not the item is a directory
        /// @note For DataCollectionFile, this will always return false
        bool isDirectory() const override;
        
        /// @brief Whether or not the item is a root directory
        /// @note For DataCollectionFile, this will always return false
        bool isRoot() const override;

        #pragma endregion
    };
}

#endif