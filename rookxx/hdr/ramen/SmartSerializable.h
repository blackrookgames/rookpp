#include "ramen/Serializable.h"
#include "ramen/SmartReader.h"
#include "ramen/SmartWriter.h"

#ifndef rookxx_ramen_SmartSerializable_h
#define rookxx_ramen_SmartSerializable_h

namespace rookxx::ramen
{
    /// @brief Represents an object containing serializable data that's compatible with SmartReader and SmartWriter
    class SmartSerializable : public Serializable
    {
        #pragma region serialization

        /// @brief Attempts to serialize object data
        /// @param sw Smart writer
        /// @return Whether or not successful
        /// @note If serialization fails, writer position will not be changed
        public: virtual bool serialize(SmartWriter& sw) const = 0;
        
        /// @brief Attempts to update object data by deserializing byte data
        /// @param sr Smart reader
        /// @return Whether or not successful
        /// @note If serialization fails, reader position will not be changed
        public: virtual bool deserialize(SmartReader& sr) = 0;

        #pragma endregion
    };
}

#endif