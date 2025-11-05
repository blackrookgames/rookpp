#include <cstddef>
#include <cstdint>
#include <cstring>

#ifndef rookxx_ramen_Ramen_h
#define rookxx_ramen_Ramen_h

namespace rookxx::ramen
{
    /// @brief Utility with array-related operations
    class ArrUtil
    {
        /// @brief Creates a new array
        /// @tparam T Element type
        /// @param length Number of elements within the array
        /// @return Created array (or nullptr if length = 0)
        public: template<typename T> static T* create(size_t length)
        {
            if (length == 0) return nullptr;
            return new T[length];
        }

        /// @brief Creates a new array and sets the elements to a null value
        /// @tparam T Element type
        /// @param length Number of elements within the array
        /// @return Created array (or nullptr if length = 0)
        public: template<typename T> static T* createNull(size_t length)
        {
            if (length == 0) return nullptr;
            T* array = new T[length];
            memset(array, 0, length * sizeof(T));
            return array;
        }

        /// @brief Sets the elements within the specified array to a null value
        /// @tparam T Element type
        /// @param array Array
        /// @param length Number of elements within the array
        public: template<typename T> static void nullify(T* array, size_t length)
        {
            memset(array, 0, length * sizeof(T));
        }
    };
}

#endif