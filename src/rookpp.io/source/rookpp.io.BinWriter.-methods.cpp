#include "rookpp.io.BinWriter.h"

using namespace rookpp::io;

void BinWriter::writeUInt8(uint8_t value)
{
	*((uint8_t*)f_Buffer) = value;
	f_Stream->write((char*)f_Buffer, 1);
}

void BinWriter::writeInt8(int8_t value)
{
	*((uint8_t*)f_Buffer) = (uint8_t)value;
	f_Stream->write((char*)f_Buffer, 1);
}

void BinWriter::writeUInt16(bool bigEndian, uint16_t value)
{
	BitData::writeUInt16(f_Buffer, bigEndian, value);
	f_Stream->write((char*)f_Buffer, 2);
}

void BinWriter::writeUInt16L(uint16_t value)
{
	BitData::writeUInt16L(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 2);
}

void BinWriter::writeUInt16B(uint16_t value)
{
	BitData::writeUInt16B(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 2);
}

void BinWriter::writeInt16(bool bigEndian, int16_t value)
{
	BitData::writeInt16(f_Buffer, bigEndian, value);
	f_Stream->write((char*)f_Buffer, 2);
}

void BinWriter::writeInt16L(int16_t value)
{
	BitData::writeInt16L(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 2);
}

void BinWriter::writeInt16B(int16_t value)
{
	BitData::writeInt16B(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 2);
}

void BinWriter::writeUInt32(bool bigEndian, uint32_t value)
{
	BitData::writeUInt32(f_Buffer, bigEndian, value);
	f_Stream->write((char*)f_Buffer, 4);
}

void BinWriter::writeUInt32L(uint32_t value)
{
	BitData::writeUInt32L(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 4);
}

void BinWriter::writeUInt32B(uint32_t value)
{
	BitData::writeUInt32B(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 4);
}

void BinWriter::writeInt32(bool bigEndian, int32_t value)
{
	BitData::writeInt32(f_Buffer, bigEndian, value);
	f_Stream->write((char*)f_Buffer, 4);
}

void BinWriter::writeInt32L(int32_t value)
{
	BitData::writeInt32L(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 4);
}

void BinWriter::writeInt32B(int32_t value)
{
	BitData::writeInt32B(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 4);
}

void BinWriter::writeUInt64(bool bigEndian, uint64_t value)
{
	BitData::writeUInt64(f_Buffer, bigEndian, value);
	f_Stream->write((char*)f_Buffer, 8);
}

void BinWriter::writeUInt64L(uint64_t value)
{
	BitData::writeUInt64L(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 8);
}

void BinWriter::writeUInt64B(uint64_t value)
{
	BitData::writeUInt64B(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 8);
}

void BinWriter::writeInt64(bool bigEndian, int64_t value)
{
	BitData::writeInt64(f_Buffer, bigEndian, value);
	f_Stream->write((char*)f_Buffer, 8);
}

void BinWriter::writeInt64L(int64_t value)
{
	BitData::writeInt64L(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 8);
}

void BinWriter::writeInt64B(int64_t value)
{
	BitData::writeInt64B(f_Buffer, value);
	f_Stream->write((char*)f_Buffer, 8);
}
