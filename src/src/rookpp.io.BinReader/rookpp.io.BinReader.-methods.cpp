#include "rookpp.io.BinReader.h"

using namespace rookpp::io;

uint8_t BinReader::readUInt8()
{
	f_Stream->read((char*)f_Buffer, 1);
	return *((uint8_t*)f_Buffer);
}

int8_t BinReader::readInt8()
{
	f_Stream->read((char*)f_Buffer, 1);
	return (int8_t)(*((uint8_t*)f_Buffer));
}

uint16_t BinReader::readUInt16(bool bigEndian)
{
	f_Stream->read((char*)f_Buffer, 2);
	return BitData::readUInt16(f_Buffer, bigEndian);
}

uint16_t BinReader::readUInt16L()
{
	f_Stream->read((char*)f_Buffer, 2);
	return BitData::readUInt16L(f_Buffer);
}

uint16_t BinReader::readUInt16B()
{
	f_Stream->read((char*)f_Buffer, 2);
	return BitData::readUInt16B(f_Buffer);
}

int16_t BinReader::readInt16(bool bigEndian)
{
	f_Stream->read((char*)f_Buffer, 2);
	return BitData::readInt16(f_Buffer, bigEndian);
}

int16_t BinReader::readInt16L()
{
	f_Stream->read((char*)f_Buffer, 2);
	return BitData::readInt16L(f_Buffer);
}

int16_t BinReader::readInt16B()
{
	f_Stream->read((char*)f_Buffer, 2);
	return BitData::readInt16B(f_Buffer);
}

uint32_t BinReader::readUInt32(bool bigEndian)
{
	f_Stream->read((char*)f_Buffer, 4);
	return BitData::readUInt32(f_Buffer, bigEndian);
}

uint32_t BinReader::readUInt32L()
{
	f_Stream->read((char*)f_Buffer, 4);
	return BitData::readUInt32L(f_Buffer);
}

uint32_t BinReader::readUInt32B()
{
	f_Stream->read((char*)f_Buffer, 4);
	return BitData::readUInt32B(f_Buffer);
}

int32_t BinReader::readInt32(bool bigEndian)
{
	f_Stream->read((char*)f_Buffer, 4);
	return BitData::readInt32(f_Buffer, bigEndian);
}

int32_t BinReader::readInt32L()
{
	f_Stream->read((char*)f_Buffer, 4);
	return BitData::readInt32L(f_Buffer);
}

int32_t BinReader::readInt32B()
{
	f_Stream->read((char*)f_Buffer, 4);
	return BitData::readInt32B(f_Buffer);
}

uint64_t BinReader::readUInt64(bool bigEndian)
{
	f_Stream->read((char*)f_Buffer, 8);
	return BitData::readUInt64(f_Buffer, bigEndian);
}

uint64_t BinReader::readUInt64L()
{
	f_Stream->read((char*)f_Buffer, 8);
	return BitData::readUInt64L(f_Buffer);
}

uint64_t BinReader::readUInt64B()
{
	f_Stream->read((char*)f_Buffer, 8);
	return BitData::readUInt64B(f_Buffer);
}

int64_t BinReader::readInt64(bool bigEndian)
{
	f_Stream->read((char*)f_Buffer, 8);
	return BitData::readInt64(f_Buffer, bigEndian);
}

int64_t BinReader::readInt64L()
{
	f_Stream->read((char*)f_Buffer, 8);
	return BitData::readInt64L(f_Buffer);
}

int64_t BinReader::readInt64B()
{
	f_Stream->read((char*)f_Buffer, 8);
	return BitData::readInt64B(f_Buffer);
}
