#include <cstddef>
#include <cstdint>

#ifndef rookxx_ramen_Serializable_h
#define rookxx_ramen_Serializable_h

namespace rookxx::ramen
{
    /// @brief Represents an object containing serializable data
    class Serializable
    {
        #pragma region serialization

        /// @brief Attempts to serialize object data
        /// @param data Serialized byte data
        /// @param size Size of serialized byte data
        /// @return Whether or not successful
        /// @note If serialization fails, data will be set to nullptr
        /// @note If serialization fails, size will be set to zero
        public: virtual bool serialize(uint8_t*& data, size_t& size) const = 0;
        
        /// @brief Attempts to update object data by deserializing byte data
        /// @param data Serialized byte data
        /// @param size Size of serialized byte data
        /// @return Whether or not successful
        public: virtual bool deserialize(const uint8_t* data, size_t size) = 0;

        #pragma endregion
    };
}

#endif