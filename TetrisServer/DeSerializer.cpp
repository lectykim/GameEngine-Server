#include "pch.h"
#include "DeSerializer.h"

shared_ptr<vector<PacketVariant>> DeSerilizer::Deserialization(BYTE* pos, int len)
{
	auto result = make_shared<vector<PacketVariant>>();
	int currentByte = 0;
	
	while (currentByte <= len)
	{
		uint8_t serializationId = pos[currentByte];
		currentByte++;
		switch (serializationId)
		{
			case 1:
			{
				uint8_t data = pos[currentByte];
				currentByte++;
				result->emplace_back(data);
				break;
			}
			case 2:
			{
				uint16_t data = 0;
				ConvertMemory(pos, static_cast<void*>(&data), sizeof(data), currentByte);
				currentByte += sizeof(data);
				result->emplace_back(data);
				break;

			}
			case 3:
			{
				uint16_t strLen = 0;
				ConvertMemory(pos, static_cast<void*>(&strLen), sizeof(strLen), currentByte);
				currentByte += sizeof(strLen);
				string str(reinterpret_cast<const char*>(pos + currentByte));
				currentByte += str.length();
				result->emplace_back(str);
				break;
			}
			case 4:
			{
				uint64_t data = 0;
				ConvertMemory(pos, static_cast<void*>(&data), sizeof(data), currentByte);
				currentByte += sizeof(data);
				result->emplace_back(data);
				break;
			}
			case 5:
			{
				uint16_t value = 0;
				vector<uint16_t> vec;
				while (value != UINT16_MAX)
				{
					ConvertMemory(pos, static_cast<void*>(&value), sizeof(value), currentByte);
					currentByte += sizeof(value);
					vec.emplace_back(value);
				}
				uint16_t* valueArray = new uint16_t[vec.size()];
				copy(vec.begin(), vec.end(), valueArray);
				result->emplace_back(valueArray);
				break;
			}
			case 6:
			{
				uint64_t value = 0;
				vector<uint64_t> vec;
				while (value != UINT64_MAX)
				{
					ConvertMemory(pos, static_cast<void*>(&value), sizeof(value), currentByte);
					currentByte += sizeof(value);
					vec.emplace_back(value);
				}
				uint64_t* valueArray = new uint64_t[vec.size()];
				copy(vec.begin(), vec.end(), valueArray);
				result->emplace_back(valueArray);
				break;
			}
		}
	}
	return result;
}

void DeSerilizer::ConvertMemory(BYTE* pos, void* data, size_t len, int currentByte)
{
	if (len == 2)
	{
		uint16_t tempData = 0;
		tempData += static_cast<uint16_t>(pos[currentByte]);
		tempData += static_cast<uint16_t>(pos[currentByte + 1] << 8);
		*(uint16_t*)data = tempData;
	}
	else if (len == 4)
	{

	}
	else if (len == 8)
	{
		uint64_t tempData = 0;
		tempData |= (static_cast<uint64_t>(pos[currentByte]));
		tempData |= (static_cast<uint64_t>(pos[currentByte+1])<<8);
		tempData |= (static_cast<uint64_t>(pos[currentByte+2]) << 16);
		tempData |= (static_cast<uint64_t>(pos[currentByte+3]) << 24);
		tempData |= (static_cast<uint64_t>(pos[currentByte+4]) <<32);
		tempData |= (static_cast<uint64_t>(pos[currentByte+5]) <<40);
		tempData |= (static_cast<uint64_t>(pos[currentByte+6]) <<48);
		tempData |= (static_cast<uint64_t>(pos[currentByte+7]) <<56);
		*(uint64_t*)data = tempData;
	}
}
