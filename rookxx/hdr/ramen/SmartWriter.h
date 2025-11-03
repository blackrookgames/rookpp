#include <cstddef>
#include <cstdint>

#ifndef rookxx_ramen_SmartWriter_h
#define rookxx_ramen_SmartWriter_h

namespace rookxx::ramen
{
    class SmartWriter
    {
        #pragma region init

        /// @brief Constructor for SmartWriter
        public: SmartWriter();

        /// @brief Destructor for SmartData
        public: ~SmartWriter();

        // We won't need these
        public: SmartWriter(const SmartWriter& src) = delete;
        public: SmartWriter& operator=(const SmartWriter& src) = delete;
        public: SmartWriter(SmartWriter&& src) = delete;
        public: SmartWriter& operator=(SmartWriter&& src) = delete;

        private: void m_Reset();

        #pragma endregion

        #pragma region fields

        private: bool f_Valid;

        private: uint8_t* f_Beg;
        private: uint8_t* f_Cap;
        private: uint8_t* f_End;
        private: uint8_t* f_Pos;

        #pragma endregion

        #pragma region properties

        /// @brief Whether or not reader is in a valid state
        public: bool valid() const;

        /// @brief Pointer to beginning of data
        /// @note This value may change if the capacity is changed
        public: uint8_t* beg();
        /// @brief Pointer to beginning of data
        /// @note This value may change if the capacity is changed
        public: const uint8_t* beg() const;

        /// @brief Pointer to end of data
        /// @note This value may change if the capacity is changed
        public: uint8_t* end();
        /// @brief Pointer to end of data
        /// @note This value may change if the capacity is changed
        public: const uint8_t* end() const;

        /// @brief Position of reader
        public: uint8_t* pos();
        /// @brief Position of reader
        public: const uint8_t* pos() const;

        #pragma endregion

        #pragma region helper

        private: void m_Realloc(size_t newCap);

        private: void m_UpdateSize(size_t inc);

        #pragma endregion

        #pragma region functions

        /// @brief Flushes existing data to an array
        /// @param data Array containing flushed data
        /// @param size Size of flushed data
        /// @note This will remove all data within the writer
        public: void flush(uint8_t*& data, size_t& size);

        /// @brief Clears all data within the buffer
        public: void clear();

        /// @brief Gets the current data capacity
        /// @return Current data capacity
        public: size_t getCapacity() const;

        /// @brief Gets the current size of data
        /// @return Current size of data
        public: size_t getSize() const;

        /// @brief Gets the reader's position
        /// @return Writer's distance from beginning of data
        public: size_t tell() const;

        /// @brief Sets the reader's position
        /// @param pos Distance from beginning of data
        public: void seek(size_t pos);
        
        /// @brief Adjusts the capacity so it supports the specified size, reallocating if necessary
        /// @param size Minimum size
        public: void reserve(size_t size);
        
        /// @brief Shrinks the capacity so it neatly fits the contained data, reallocating if necessary
        public: void shrink();

        #pragma endregion

        #pragma region Misc
        
        public: void write(const uint8_t* buffer, size_t size);

        public: void writeU8(uint8_t value);
        
        public: void writeI8(int8_t value);

        #pragma endregion

        #pragma region UInt16

        public: void writeU16(uint16_t value, bool big);
        public: void writeU16l(uint16_t value);
        public: void writeU16b(uint16_t value);

        #pragma endregion

        #pragma region Int16

        public: void writeI16(int16_t value, bool big);
        public: void writeI16l(int16_t value);
        public: void writeI16b(int16_t value);

        #pragma endregion

        #pragma region UInt32

        public: void writeU32(uint32_t value, bool big);
        public: void writeU32l(uint32_t value);
        public: void writeU32b(uint32_t value);

        #pragma endregion

        #pragma region Int32

        public: void writeI32(int32_t value, bool big);
        public: void writeI32l(int32_t value);
        public: void writeI32b(int32_t value);

        #pragma endregion

        #pragma region UInt64

        public: void writeU64(uint64_t value, bool big);
        public: void writeU64l(uint64_t value);
        public: void writeU64b(uint64_t value);

        #pragma endregion

        #pragma region Int64

        public: void writeI64(int64_t value, bool big);
        public: void writeI64l(int64_t value);
        public: void writeI64b(int64_t value);

        #pragma endregion
    };
}

#endif