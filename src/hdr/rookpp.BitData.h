#include <cstdint>

#pragma once
#ifndef __ROOKPP_BITCONVERTER_H__
#define __ROOKPP_BITCONVERTER_H__
namespace rookpp
{
	/// @brief Utility for converting bit data
	class BitData
	{
		/// @brief Dummy constructor to prevent instances of BitData
		private: BitData();

		/// @brief Reads a 16-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 16-bit unsigned integer that was read
		public: static uint16_t readUInt16(void *data, bool bigEndian);
		
		/// @brief Reads a little-endian 16-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @return 16-bit unsigned integer that was read
		public: static uint16_t readUInt16L(void *data);
		
		/// @brief Reads a big-endian 16-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @return 16-bit unsigned integer that was read
		public: static uint16_t readUInt16B(void *data);
		
		/// @brief Writes a 16-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 16-bit unsigned integer to write
		public: static void writeUInt16(void *data, bool bigEndian, uint16_t value);
		
		/// @brief Writes a little-endian 16-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param value 16-bit unsigned integer to write
		public: static void writeUInt16L(void *data, uint16_t value);
		
		/// @brief Writes a big-endian 16-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param value 16-bit unsigned integer to write
		public: static void writeUInt16B(void *data, uint16_t value);
		
		/// @brief Reads a 16-bit signed integer from the specified data
		/// @param data Data to read from
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 16-bit signed integer that was read
		public: static int16_t readInt16(void *data, bool bigEndian);
		
		/// @brief Reads a little-endian 16-bit signed integer from the specified data
		/// @param data Data to read from
		/// @return 16-bit signed integer that was read
		public: static int16_t readInt16L(void *data);
		
		/// @brief Reads a big-endian 16-bit signed integer from the specified data
		/// @param data Data to read from
		/// @return 16-bit signed integer that was read
		public: static int16_t readInt16B(void *data);
		
		/// @brief Writes a 16-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 16-bit signed integer to write
		public: static void writeInt16(void *data, bool bigEndian, int16_t value);
		
		/// @brief Writes a little-endian 16-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param value 16-bit signed integer to write
		public: static void writeInt16L(void *data, int16_t value);
		
		/// @brief Writes a big-endian 16-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param value 16-bit signed integer to write
		public: static void writeInt16B(void *data, int16_t value);
		
		/// @brief Reads a 32-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 32-bit unsigned integer that was read
		public: static uint32_t readUInt32(void *data, bool bigEndian);
		
		/// @brief Reads a little-endian 32-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @return 32-bit unsigned integer that was read
		public: static uint32_t readUInt32L(void *data);
		
		/// @brief Reads a big-endian 32-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @return 32-bit unsigned integer that was read
		public: static uint32_t readUInt32B(void *data);
		
		/// @brief Writes a 32-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 32-bit unsigned integer to write
		public: static void writeUInt32(void *data, bool bigEndian, uint32_t value);
		
		/// @brief Writes a little-endian 32-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param value 32-bit unsigned integer to write
		public: static void writeUInt32L(void *data, uint32_t value);
		
		/// @brief Writes a big-endian 32-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param value 32-bit unsigned integer to write
		public: static void writeUInt32B(void *data, uint32_t value);
		
		/// @brief Reads a 32-bit signed integer from the specified data
		/// @param data Data to read from
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 32-bit signed integer that was read
		public: static int32_t readInt32(void *data, bool bigEndian);
		
		/// @brief Reads a little-endian 32-bit signed integer from the specified data
		/// @param data Data to read from
		/// @return 32-bit signed integer that was read
		public: static int32_t readInt32L(void *data);
		
		/// @brief Reads a big-endian 32-bit signed integer from the specified data
		/// @param data Data to read from
		/// @return 32-bit signed integer that was read
		public: static int32_t readInt32B(void *data);
		
		/// @brief Writes a 32-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 32-bit signed integer to write
		public: static void writeInt32(void *data, bool bigEndian, int32_t value);
		
		/// @brief Writes a little-endian 32-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param value 32-bit signed integer to write
		public: static void writeInt32L(void *data, int32_t value);
		
		/// @brief Writes a big-endian 32-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param value 32-bit signed integer to write
		public: static void writeInt32B(void *data, int32_t value);
		
		/// @brief Reads a 64-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 64-bit unsigned integer that was read
		public: static uint64_t readUInt64(void *data, bool bigEndian);
		
		/// @brief Reads a little-endian 64-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @return 64-bit unsigned integer that was read
		public: static uint64_t readUInt64L(void *data);
		
		/// @brief Reads a big-endian 64-bit unsigned integer from the specified data
		/// @param data Data to read from
		/// @return 64-bit unsigned integer that was read
		public: static uint64_t readUInt64B(void *data);
		
		/// @brief Writes a 64-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 64-bit unsigned integer to write
		public: static void writeUInt64(void *data, bool bigEndian, uint64_t value);
		
		/// @brief Writes a little-endian 64-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param value 64-bit unsigned integer to write
		public: static void writeUInt64L(void *data, uint64_t value);
		
		/// @brief Writes a big-endian 64-bit unsigned integer to the specified data
		/// @param data Data to write to
		/// @param value 64-bit unsigned integer to write
		public: static void writeUInt64B(void *data, uint64_t value);
		
		/// @brief Reads a 64-bit signed integer from the specified data
		/// @param data Data to read from
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 64-bit signed integer that was read
		public: static int64_t readInt64(void *data, bool bigEndian);
		
		/// @brief Reads a little-endian 64-bit signed integer from the specified data
		/// @param data Data to read from
		/// @return 64-bit signed integer that was read
		public: static int64_t readInt64L(void *data);
		
		/// @brief Reads a big-endian 64-bit signed integer from the specified data
		/// @param data Data to read from
		/// @return 64-bit signed integer that was read
		public: static int64_t readInt64B(void *data);
		
		/// @brief Writes a 64-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 64-bit signed integer to write
		public: static void writeInt64(void *data, bool bigEndian, int64_t value);
		
		/// @brief Writes a little-endian 64-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param value 64-bit signed integer to write
		public: static void writeInt64L(void *data, int64_t value);
		
		/// @brief Writes a big-endian 64-bit signed integer to the specified data
		/// @param data Data to write to
		/// @param value 64-bit signed integer to write
		public: static void writeInt64B(void *data, int64_t value);
	};
}
#endif
