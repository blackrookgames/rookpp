#include "ramen/datcol/DataCollectionDirectory.h"
#include "ramen/SmartSerializable.h"

#ifndef rookxx_ramen_datcol_DataCollection_h
#define rookxx_ramen_datcol_DataCollection_h

namespace rookxx::ramen::datcol
{
    /// @brief Represents a collection of data
    class DataCollection : public SmartSerializable
    {
        #pragma region init

    public:
        
        /// @brief Constructor for DataCollection
        DataCollection();
        
        /// @brief Destructor for DataCollection
        virtual ~DataCollection();

        // We won't need these
        DataCollection(const DataCollection& src) = delete;
        DataCollection(DataCollection&& src) = delete;
        DataCollection& operator=(const DataCollection& src) = delete;
        DataCollection& operator=(DataCollection&& src) = delete;

        #pragma endregion

        #pragma region serialization

    public:

        /// @brief Attempts to serialize the data collection
        /// @param data Serialized byte data
        /// @param size Size of serialized byte data
        /// @return Whether or not successful
        /// @note If serialization fails, data will be set to nullptr
        /// @note If serialization fails, size will be set to zero
        virtual bool serialize(uint8_t*& data, size_t& size) const override;
        
        /// @brief Attempts to deserialize a data collection
        /// @param data Serialized byte data
        /// @param size Size of serialized byte data
        /// @return Whether or not successful
        virtual bool deserialize(const uint8_t* data, size_t size) override;

        /// @brief Attempts to serialize the data collection
        /// @param sw Smart writer
        /// @return Whether or not successful
        /// @note If serialization fails, writer position will not be changed
        virtual bool serialize(SmartWriter& sw) const override;
        
        /// @brief Attempts to deserialize a data collection
        /// @param sr Smart reader
        /// @return Whether or not successful
        /// @note If serialization fails, reader position will not be changed
        virtual bool deserialize(SmartReader& sr) override;
        
        #pragma endregion

        #pragma region fields

    private:

        DataCollectionDirectory f_Root;

        #pragma endregion

        #pragma region properties

    public:

        /// @brief Root directory
        DataCollectionDirectory& root();
        /// @brief Root directory
        const DataCollectionDirectory& root() const;

        #pragma endregion
    };
}

#endif