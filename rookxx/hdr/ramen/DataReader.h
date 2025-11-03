#include <cstddef>
#include <cstdint>

#ifndef rookxx_ramen_DataReader_h
#define rookxx_ramen_DataReader_h

namespace rookxx::ramen
{
    class DataReader
    {
        #pragma region UInt16

        public: static uint16_t readU16(const uint8_t*& ptr, bool big);
        public: static uint16_t readU16l(const uint8_t*& ptr);
        public: static uint16_t readU16b(const uint8_t*& ptr);

        #pragma endregion

        #pragma region Int16

        public: static int16_t readI16(const uint8_t*& ptr, bool big);
        public: static int16_t readI16l(const uint8_t*& ptr);
        public: static int16_t readI16b(const uint8_t*& ptr);

        #pragma endregion

        #pragma region UInt32

        public: static uint32_t readU32(const uint8_t*& ptr, bool big);
        public: static uint32_t readU32l(const uint8_t*& ptr);
        public: static uint32_t readU32b(const uint8_t*& ptr);

        #pragma endregion

        #pragma region Int32

        public: static int32_t readI32(const uint8_t*& ptr, bool big);
        public: static int32_t readI32l(const uint8_t*& ptr);
        public: static int32_t readI32b(const uint8_t*& ptr);

        #pragma endregion

        #pragma region UInt64

        public: static uint64_t readU64(const uint8_t*& ptr, bool big);
        public: static uint64_t readU64l(const uint8_t*& ptr);
        public: static uint64_t readU64b(const uint8_t*& ptr);

        #pragma endregion

        #pragma region Int64

        public: static int64_t readI64(const uint8_t*& ptr, bool big);
        public: static int64_t readI64l(const uint8_t*& ptr);
        public: static int64_t readI64b(const uint8_t*& ptr);

        #pragma endregion
    };
}

#endif