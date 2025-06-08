#include <cstdint>

#pragma once
#ifndef __ROOKPP_PARSING_H__
#define __ROOKPP_PARSING_H__
namespace rookpp
{
	/// @brief Utility for parsing character strings into other value types
	class Parsing
	{
		/// @brief Dummy constructor to prevent instances of Parsing
		private: Parsing();
		
		/// @brief Attempts to parse an 8-bit unsigned integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 8-bit unsigned integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseUInt8(const char *str, uint8_t *result);
		
		/// @brief Attempts to parse an 8-bit signed integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 8-bit signed integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseInt8(const char *str, int8_t *result);
		
		/// @brief Attempts to parse a 16-bit unsigned integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 16-bit unsigned integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseUInt16(const char *str, uint16_t *result);
		
		/// @brief Attempts to parse a 16-bit signed integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 16-bit signed integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseInt16(const char *str, int16_t *result);
		
		/// @brief Attempts to parse a 32-bit unsigned integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 32-bit unsigned integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseUInt32(const char *str, uint32_t *result);
		
		/// @brief Attempts to parse a 32-bit signed integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 32-bit signed integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseInt32(const char *str, int32_t *result);
		
		/// @brief Attempts to parse a 64-bit unsigned integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 64-bit unsigned integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseUInt64(const char *str, uint64_t *result);
		
		/// @brief Attempts to parse a 64-bit signed integer from the specified string
		/// @param str String to parse
		/// @param result Resulting 64-bit signed integer
		/// @return Whether or not successful
		/// @note This function also supports hexadecimal and binary notation
		public: static bool tryParseInt64(const char *str, int64_t *result);
		
		/// @brief Attempts to parse a single-precision floating-point from the specified string
		/// @param str String to parse
		/// @param result Resulting single-precision floating-point
		/// @return Whether or not successful
		/// @note This function does not check for overflow
		public: static bool tryParseSingle(const char *str, float *result);
		
		/// @brief Attempts to parse a double-precision floating-point from the specified string
		/// @param str String to parse
		/// @param result Resulting double-precision floating-point
		/// @return Whether or not successful
		/// @note This function does not check for overflow
		public: static bool tryParseDouble(const char *str, double *result);
	};
}
#endif
