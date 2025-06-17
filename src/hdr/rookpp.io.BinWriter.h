#include <cstdint>
#include <cstdio>
#include <fstream>
#include <rookpp.BitData.h>

#pragma once
#ifndef __ROOKPP_IO_BINWRITER_H__
#define __ROOKPP_IO_BINWRITER_H__
namespace rookpp::io
{
	/// @brief Represents a writer for binary file streams
	class BinWriter
	{
        /// @brief Creates an instance of BinWriter
        /// @param stream Stream to use for writing
        public: BinWriter(std::ofstream *stream);

        /// @brief Destroys the instance of BinWriter
        public: ~BinWriter();

        #pragma region const

        /// @brief Size of the buffer
        public: static const uint8_t bufferSize = 8;

        #pragma endregion

        #pragma region fields

        private: void *f_Buffer;
        private: std::ofstream *f_Stream;

        #pragma endregion

        #pragma region get/set

        /// @brief Gets the buffer used for writing
        /// @return The buffer used for writing
        public: void *get_Buffer();

        /// @brief Gets the stream used for writing
        /// @return The stream used for writing
        public: std::ofstream *get_Stream();

        #pragma endregion

        #pragma region write methods

        /// @brief Writes an 8-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 8-bit unsigned integer to write
		public: void writeUInt8(uint8_t value);
		
		/// @brief Writes an 8-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 8-bit signed integer to write
		public: void writeInt8(int8_t value);

        /// @brief Writes a 16-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 16-bit unsigned integer to write
		public: void writeUInt16(bool bigEndian, uint16_t value);
		
		/// @brief Writes a little-endian 16-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 16-bit unsigned integer to write
		public: void writeUInt16L(uint16_t value);
		
		/// @brief Writes a big-endian 16-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 16-bit unsigned integer to write
		public: void writeUInt16B(uint16_t value);
		
		/// @brief Writes a 16-bit signed integer to the stream
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 16-bit signed integer to write
		public: void writeInt16(bool bigEndian, int16_t value);
		
		/// @brief Writes a little-endian 16-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 16-bit signed integer to write
		public: void writeInt16L(int16_t value);
		
		/// @brief Writes a big-endian 16-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 16-bit signed integer to write
		public: void writeInt16B(int16_t value);
		
		/// @brief Writes a 32-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 32-bit unsigned integer to write
		public: void writeUInt32(bool bigEndian, uint32_t value);
		
		/// @brief Writes a little-endian 32-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 32-bit unsigned integer to write
		public: void writeUInt32L(uint32_t value);
		
		/// @brief Writes a big-endian 32-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 32-bit unsigned integer to write
		public: void writeUInt32B(uint32_t value);
		
		/// @brief Writes a 32-bit signed integer to the stream
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 32-bit signed integer to write
		public: void writeInt32(bool bigEndian, int32_t value);
		
		/// @brief Writes a little-endian 32-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 32-bit signed integer to write
		public: void writeInt32L(int32_t value);
		
		/// @brief Writes a big-endian 32-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 32-bit signed integer to write
		public: void writeInt32B(int32_t value);
		
		/// @brief Writes a 64-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 64-bit unsigned integer to write
		public: void writeUInt64(bool bigEndian, uint64_t value);
		
		/// @brief Writes a little-endian 64-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 64-bit unsigned integer to write
		public: void writeUInt64L(uint64_t value);
		
		/// @brief Writes a big-endian 64-bit unsigned integer to the stream
		/// @param data Data to write to
		/// @param value 64-bit unsigned integer to write
		public: void writeUInt64B(uint64_t value);
		
		/// @brief Writes a 64-bit signed integer to the stream
		/// @param data Data to write to
		/// @param bigEndian Whether or not to store value in big-endian
		/// @param value 64-bit signed integer to write
		public: void writeInt64(bool bigEndian, int64_t value);
		
		/// @brief Writes a little-endian 64-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 64-bit signed integer to write
		public: void writeInt64L(int64_t value);
		
		/// @brief Writes a big-endian 64-bit signed integer to the stream
		/// @param data Data to write to
		/// @param value 64-bit signed integer to write
		public: void writeInt64B(int64_t value);

        #pragma endregion
	};
}
#endif
