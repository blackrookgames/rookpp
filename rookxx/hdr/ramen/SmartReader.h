#include <cstddef>
#include <cstdint>

#ifndef rookxx_ramen_SmartReader_h
#define rookxx_ramen_SmartReader_h

namespace rookxx::ramen
{
    class SmartReader
    {
        #pragma region init

        /// @brief Constructor for SmartReader
        /// @param beg Pointer to beginning of data
        /// @param end Pointer to end of data
        public: SmartReader(const uint8_t* beg, const uint8_t* end);

        /// @brief Constructor for SmartReader
        /// @param beg Pointer to beginning of data
        /// @param size Size of data
        public: SmartReader(const uint8_t* beg, size_t size);

        /// @brief Destructor for SmartData
        public: ~SmartReader();

        // We won't need these
        public: SmartReader() = delete;
        public: SmartReader(const SmartReader& src) = delete;
        public: SmartReader& operator=(const SmartReader& src) = delete;
        public: SmartReader(SmartReader&& src) = delete;
        public: SmartReader& operator=(SmartReader&& src) = delete;

        #pragma endregion

        #pragma region fields

        private: bool f_Valid;

        private: const uint8_t* f_Beg;
        private: const uint8_t* f_End;
        private: const uint8_t* f_Pos;

        #pragma endregion

        #pragma region properties

        /// @brief Whether or not reader is in a valid state
        public: bool valid() const;

        /// @brief Beginning of data
        public: const uint8_t* beg() const;

        /// @brief End of data
        public: const uint8_t* end() const;

        /// @brief Position of reader
        public: const uint8_t* pos() const;

        #pragma endregion

        #pragma region functions

        /// @brief Gets the size of the data
        /// @return Size of data
        public: size_t getSize() const;

        /// @brief Gets the reader's position
        /// @return Reader's distance from beginning of data
        public: size_t tell() const;

        /// @brief Sets the reader's position
        /// @param pos Distance from beginning of data
        public: void seek(size_t pos);

        #pragma endregion

        #pragma region Misc
        
        public: void read(uint8_t* buffer, size_t size);

        public: uint8_t readU8();
        
        public: int8_t readI8();

        #pragma endregion

        #pragma region UInt16

        public: uint16_t readU16(bool big);
        public: uint16_t readU16l();
        public: uint16_t readU16b();

        #pragma endregion

        #pragma region Int16

        public: int16_t readI16(bool big);
        public: int16_t readI16l();
        public: int16_t readI16b();

        #pragma endregion

        #pragma region UInt32

        public: uint32_t readU32(bool big);
        public: uint32_t readU32l();
        public: uint32_t readU32b();

        #pragma endregion

        #pragma region Int32

        public: int32_t readI32(bool big);
        public: int32_t readI32l();
        public: int32_t readI32b();

        #pragma endregion

        #pragma region UInt64

        public: uint64_t readU64(bool big);
        public: uint64_t readU64l();
        public: uint64_t readU64b();

        #pragma endregion

        #pragma region Int64

        public: int64_t readI64(bool big);
        public: int64_t readI64l();
        public: int64_t readI64b();

        #pragma endregion
    };
}

#endif