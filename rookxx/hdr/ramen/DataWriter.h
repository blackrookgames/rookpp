#include <cstddef>
#include <cstdint>

#ifndef rookxx_ramen_DataWriter_h
#define rookxx_ramen_DataWriter_h

namespace rookxx::ramen
{
    class DataWriter
    {
        #pragma region UInt16

        public: static void writeU16(uint8_t*& ptr, uint16_t value, bool big);
        public: static void writeU16l(uint8_t*& ptr, uint16_t value);
        public: static void writeU16b(uint8_t*& ptr, uint16_t value);

        #pragma endregion

        #pragma region Int16

        public: static void writeI16(uint8_t*& ptr, int16_t value, bool big);
        public: static void writeI16l(uint8_t*& ptr, int16_t value);
        public: static void writeI16b(uint8_t*& ptr, int16_t value);

        #pragma endregion

        #pragma region UInt32

        public: static void writeU32(uint8_t*& ptr, uint32_t value, bool big);
        public: static void writeU32l(uint8_t*& ptr, uint32_t value);
        public: static void writeU32b(uint8_t*& ptr, uint32_t value);

        #pragma endregion

        #pragma region Int32

        public: static void writeI32(uint8_t*& ptr, int32_t value, bool big);
        public: static void writeI32l(uint8_t*& ptr, int32_t value);
        public: static void writeI32b(uint8_t*& ptr, int32_t value);

        #pragma endregion

        #pragma region UInt64

        public: static void writeU64(uint8_t*& ptr, uint64_t value, bool big);
        public: static void writeU64l(uint8_t*& ptr, uint64_t value);
        public: static void writeU64b(uint8_t*& ptr, uint64_t value);

        #pragma endregion

        #pragma region Int64

        public: static void writeI64(uint8_t*& ptr, int64_t value, bool big);
        public: static void writeI64l(uint8_t*& ptr, int64_t value);
        public: static void writeI64b(uint8_t*& ptr, int64_t value);

        #pragma endregion
    };
}

#endif