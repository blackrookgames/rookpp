#include <cstdint>
#include <cstdio>
#include <fstream>
#include <rookpp.BitData.h>

#pragma once
#ifndef __ROOKPP_IO_BINREADER_H__
#define __ROOKPP_IO_BINREADER_H__
namespace rookpp::io
{
	/// @brief Represents a reader for binary file streams
	class BinReader
	{
        /// @brief Creates an instance of BinReader
        /// @param stream Stream to use for reading
        public: BinReader(std::ifstream *stream);

        /// @brief Destroys the instance of BinReader
        public: ~BinReader();

        #pragma region const

        /// @brief Size of the buffer
        public: static const uint8_t bufferSize = 8;

        #pragma endregion

        #pragma region fields

        private: void *f_Buffer;
        private: std::ifstream *f_Stream;

        #pragma endregion

        #pragma region get/set

        /// @brief Gets the buffer used for reading
        /// @return The buffer used for reading
        public: void *get_Buffer();

        /// @brief Gets the stream used for reading
        /// @return The stream used for reading
        public: std::ifstream *get_Stream();

        #pragma endregion

        #pragma region methods

		/// @brief Reads an 8-bit unsigned integer from the stream
		/// @return 8-bit unsigned integer that was read
		public: uint8_t readUInt8();
		
		/// @brief Reads an 8-bit signed integer from the stream
		/// @return 8-bit signed integer that was read
		public: int8_t readInt8();

		/// @brief Reads a 16-bit unsigned integer from the stream
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 16-bit unsigned integer that was read
		public: uint16_t readUInt16(bool bigEndian);
		
		/// @brief Reads a little-endian 16-bit unsigned integer from the stream
		/// @return 16-bit unsigned integer that was read
		public: uint16_t readUInt16L();
		
		/// @brief Reads a big-endian 16-bit unsigned integer from the stream
		/// @return 16-bit unsigned integer that was read
		public: uint16_t readUInt16B();
		
		/// @brief Reads a 16-bit signed integer from the stream
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 16-bit signed integer that was read
		public: int16_t readInt16(bool bigEndian);
		
		/// @brief Reads a little-endian 16-bit signed integer from the stream
		/// @return 16-bit signed integer that was read
		public: int16_t readInt16L();
		
		/// @brief Reads a big-endian 16-bit signed integer from the stream
		/// @return 16-bit signed integer that was read
		public: int16_t readInt16B();
		
		/// @brief Reads a 32-bit unsigned integer from the stream
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 32-bit unsigned integer that was read
		public: uint32_t readUInt32(bool bigEndian);
		
		/// @brief Reads a little-endian 32-bit unsigned integer from the stream
		/// @return 32-bit unsigned integer that was read
		public: uint32_t readUInt32L();
		
		/// @brief Reads a big-endian 32-bit unsigned integer from the stream
		/// @return 32-bit unsigned integer that was read
		public: uint32_t readUInt32B();
		
		/// @brief Reads a 32-bit signed integer from the stream
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 32-bit signed integer that was read
		public: int32_t readInt32(bool bigEndian);
		
		/// @brief Reads a little-endian 32-bit signed integer from the stream
		/// @return 32-bit signed integer that was read
		public: int32_t readInt32L();
		
		/// @brief Reads a big-endian 32-bit signed integer from the stream
		/// @return 32-bit signed integer that was read
		public: int32_t readInt32B();
		
		/// @brief Reads a 64-bit unsigned integer from the stream
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 64-bit unsigned integer that was read
		public: uint64_t readUInt64(bool bigEndian);
		
		/// @brief Reads a little-endian 64-bit unsigned integer from the stream
		/// @return 64-bit unsigned integer that was read
		public: uint64_t readUInt64L();
		
		/// @brief Reads a big-endian 64-bit unsigned integer from the stream
		/// @return 64-bit unsigned integer that was read
		public: uint64_t readUInt64B();
		
		/// @brief Reads a 64-bit signed integer from the stream
		/// @param bigEndian Whether or not value is stored in big-endian
		/// @return 64-bit signed integer that was read
		public: int64_t readInt64(bool bigEndian);
		
		/// @brief Reads a little-endian 64-bit signed integer from the stream
		/// @return 64-bit signed integer that was read
		public: int64_t readInt64L();
		
		/// @brief Reads a big-endian 64-bit signed integer from the stream
		/// @return 64-bit signed integer that was read
		public: int64_t readInt64B();

        #pragma endregion
	};
}
#endif
