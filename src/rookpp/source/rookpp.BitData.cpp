#include "rookpp.BitData.h"

rookpp::BitData::BitData() { }

uint16_t rookpp::BitData::readUInt16(void *data, bool bigEndian)
{
	if(bigEndian) return readUInt16B(data);
	else return readUInt16L(data);
}

uint16_t rookpp::BitData::readUInt16L(void *data)
{
	uint16_t value = 0;	uint8_t *ptr = (uint8_t*)data + 1;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--);
	return value;
}

uint16_t rookpp::BitData::readUInt16B(void *data)
{
	uint16_t value = 0;	uint8_t *ptr = (uint8_t*)data;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++);
	return value;
}

void rookpp::BitData::writeUInt16(void *data, bool bigEndian, uint16_t value)
{
	if(bigEndian) writeUInt16B(data, value);
	else writeUInt16L(data, value);
}

void rookpp::BitData::writeUInt16L(void *data, uint16_t value)
{
	uint8_t *ptr = (uint8_t*)data;
	for (uint8_t i = 0; i < 2; i++)
	{
		*(ptr++) = (uint8_t)(value & 0xFF);
		value >>= 8;
	}
}

void rookpp::BitData::writeUInt16B(void *data, uint16_t value)
{
	uint8_t *ptr = (uint8_t*)data + 1;
	for (uint8_t i = 0; i < 2; i++)
	{
		*(ptr--) = (uint8_t)(value & 0xFF);
		value >>= 8;
	}
}

int16_t rookpp::BitData::readInt16(void *data, bool bigEndian)
{
	if(bigEndian) return readInt16B(data);
	else return readInt16L(data);
}

int16_t rookpp::BitData::readInt16L(void *data)
{
	uint16_t value = 0;	uint8_t *ptr = (uint8_t*)data + 1;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--);
	return (int16_t)value;
}

int16_t rookpp::BitData::readInt16B(void *data)
{
	uint16_t value = 0;	uint8_t *ptr = (uint8_t*)data;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++);
	return (int16_t)value;
}

void rookpp::BitData::writeInt16(void *data, bool bigEndian, int16_t value)
{
	if(bigEndian) writeInt16B(data, value);
	else writeInt16L(data, value);
}

void rookpp::BitData::writeInt16L(void *data, int16_t value)
{
	uint16_t uvalue = (uint16_t)value;
	uint8_t *ptr = (uint8_t*)data;
	for (uint8_t i = 0; i < 2; i++)
	{
		*(ptr++) = (uint8_t)(uvalue & 0xFF);
		uvalue >>= 8;
	}
}

void rookpp::BitData::writeInt16B(void *data, int16_t value)
{
	uint16_t uvalue = (uint16_t)value;
	uint8_t *ptr = (uint8_t*)data + 1;
	for (uint8_t i = 0; i < 2; i++)
	{
		*(ptr--) = (uint8_t)(uvalue & 0xFF);
		uvalue >>= 8;
	}
}

uint32_t rookpp::BitData::readUInt32(void *data, bool bigEndian)
{
	if(bigEndian) return readUInt32B(data);
	else return readUInt32L(data);
}

uint32_t rookpp::BitData::readUInt32L(void *data)
{
	uint32_t value = 0;	uint8_t *ptr = (uint8_t*)data + 3;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--);
	return value;
}

uint32_t rookpp::BitData::readUInt32B(void *data)
{
	uint32_t value = 0;	uint8_t *ptr = (uint8_t*)data;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++);
	return value;
}

void rookpp::BitData::writeUInt32(void *data, bool bigEndian, uint32_t value)
{
	if(bigEndian) writeUInt32B(data, value);
	else writeUInt32L(data, value);
}

void rookpp::BitData::writeUInt32L(void *data, uint32_t value)
{
	uint8_t *ptr = (uint8_t*)data;
	for (uint8_t i = 0; i < 4; i++)
	{
		*(ptr++) = (uint8_t)(value & 0xFF);
		value >>= 8;
	}
}

void rookpp::BitData::writeUInt32B(void *data, uint32_t value)
{
	uint8_t *ptr = (uint8_t*)data + 3;
	for (uint8_t i = 0; i < 4; i++)
	{
		*(ptr--) = (uint8_t)(value & 0xFF);
		value >>= 8;
	}
}

int32_t rookpp::BitData::readInt32(void *data, bool bigEndian)
{
	if(bigEndian) return readInt32B(data);
	else return readInt32L(data);
}

int32_t rookpp::BitData::readInt32L(void *data)
{
	uint32_t value = 0;	uint8_t *ptr = (uint8_t*)data + 3;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--);
	return (int32_t)value;
}

int32_t rookpp::BitData::readInt32B(void *data)
{
	uint32_t value = 0;	uint8_t *ptr = (uint8_t*)data;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++);
	return (int32_t)value;
}

void rookpp::BitData::writeInt32(void *data, bool bigEndian, int32_t value)
{
	if(bigEndian) writeInt32B(data, value);
	else writeInt32L(data, value);
}

void rookpp::BitData::writeInt32L(void *data, int32_t value)
{
	uint32_t uvalue = (uint32_t)value;
	uint8_t *ptr = (uint8_t*)data;
	for (uint8_t i = 0; i < 4; i++)
	{
		*(ptr++) = (uint8_t)(uvalue & 0xFF);
		uvalue >>= 8;
	}
}

void rookpp::BitData::writeInt32B(void *data, int32_t value)
{
	uint32_t uvalue = (uint32_t)value;
	uint8_t *ptr = (uint8_t*)data + 3;
	for (uint8_t i = 0; i < 4; i++)
	{
		*(ptr--) = (uint8_t)(uvalue & 0xFF);
		uvalue >>= 8;
	}
}

uint64_t rookpp::BitData::readUInt64(void *data, bool bigEndian)
{
	if(bigEndian) return readUInt64B(data);
	else return readUInt64L(data);
}

uint64_t rookpp::BitData::readUInt64L(void *data)
{
	uint64_t value = 0;	uint8_t *ptr = (uint8_t*)data + 7;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--);
	return value;
}

uint64_t rookpp::BitData::readUInt64B(void *data)
{
	uint64_t value = 0;	uint8_t *ptr = (uint8_t*)data;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++);
	return value;
}

void rookpp::BitData::writeUInt64(void *data, bool bigEndian, uint64_t value)
{
	if(bigEndian) writeUInt64B(data, value);
	else writeUInt64L(data, value);
}

void rookpp::BitData::writeUInt64L(void *data, uint64_t value)
{
	uint8_t *ptr = (uint8_t*)data;
	for (uint8_t i = 0; i < 8; i++)
	{
		*(ptr++) = (uint8_t)(value & 0xFF);
		value >>= 8;
	}
}

void rookpp::BitData::writeUInt64B(void *data, uint64_t value)
{
	uint8_t *ptr = (uint8_t*)data + 7;
	for (uint8_t i = 0; i < 8; i++)
	{
		*(ptr--) = (uint8_t)(value & 0xFF);
		value >>= 8;
	}
}

int64_t rookpp::BitData::readInt64(void *data, bool bigEndian)
{
	if(bigEndian) return readInt64B(data);
	else return readInt64L(data);
}

int64_t rookpp::BitData::readInt64L(void *data)
{
	uint64_t value = 0;	uint8_t *ptr = (uint8_t*)data + 7;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--); value <<= 8;
		value |= *(ptr--);
	return (int64_t)value;
}

int64_t rookpp::BitData::readInt64B(void *data)
{
	uint64_t value = 0;	uint8_t *ptr = (uint8_t*)data;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++); value <<= 8;
		value |= *(ptr++);
	return (int64_t)value;
}

void rookpp::BitData::writeInt64(void *data, bool bigEndian, int64_t value)
{
	if(bigEndian) writeInt64B(data, value);
	else writeInt64L(data, value);
}

void rookpp::BitData::writeInt64L(void *data, int64_t value)
{
	uint64_t uvalue = (uint64_t)value;
	uint8_t *ptr = (uint8_t*)data;
	for (uint8_t i = 0; i < 8; i++)
	{
		*(ptr++) = (uint8_t)(uvalue & 0xFF);
		uvalue >>= 8;
	}
}

void rookpp::BitData::writeInt64B(void *data, int64_t value)
{
	uint64_t uvalue = (uint64_t)value;
	uint8_t *ptr = (uint8_t*)data + 7;
	for (uint8_t i = 0; i < 8; i++)
	{
		*(ptr--) = (uint8_t)(uvalue & 0xFF);
		uvalue >>= 8;
	}
}
