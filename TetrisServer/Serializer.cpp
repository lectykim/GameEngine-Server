#include "pch.h"
#include "Serializer.h"

bool Serializer::Serialization(const vector<PacketVariant>& collection, BYTE* pos, uint16_t len)
{
	int currentByte = 0;
	for (auto it = collection.begin(); it != collection.end(); it++)
	{

		visit(overloaded{
			[&pos,&currentByte](uint8_t arg)
			{
				pos[currentByte] = 1;
				currentByte++;
				pos[currentByte] = arg;
				currentByte++;
			},
			[&pos,&currentByte](uint16_t arg)
			{
				pos[currentByte] = 2;
				currentByte++;
				InsertMemory(pos, static_cast<void*>(&arg), sizeof(arg), currentByte);
				currentByte += sizeof(arg);
				//::memcpy(&pos[currentByte], reinterpret_cast<const void*>(arg), sizeof(arg));


			},
			[&pos,&currentByte](string arg)
			{
				pos[currentByte] = 3;
				currentByte++;
				uint16_t strLen = static_cast<uint16_t>(strlen(arg.c_str()));
				InsertMemory(pos, static_cast<void*>(&strLen), sizeof(uint16_t), currentByte);
				currentByte += sizeof(uint16_t);
				strcpy_s(reinterpret_cast<char*>(pos + currentByte),strlen(arg.c_str()) + 1, arg.c_str());
				currentByte += strlen(arg.c_str());
				pos[currentByte] = '\0';
				currentByte++;
			},
			[&pos,&currentByte](uint64_t arg)
			{
				pos[currentByte] = 4;
				currentByte++;
				InsertMemory(pos, static_cast<void*>(&arg), sizeof(arg), currentByte);
				currentByte += sizeof(arg);
			},
			[&pos,&currentByte](uint16_t* arg)
			{
				pos[currentByte] = 5;
				currentByte++;
				int arraySize = 0;
				uint16_t tempArrayValue = arg[arraySize];
				while (tempArrayValue != UINT16_MAX)
				{
					InsertMemory(pos, static_cast<void*>(&tempArrayValue), sizeof(tempArrayValue), currentByte);
					currentByte += sizeof(uint16_t);
					arraySize++;
					tempArrayValue = arg[arraySize];
				}
				tempArrayValue = UINT16_MAX;
				InsertMemory(pos, static_cast<void*>(&tempArrayValue), sizeof(tempArrayValue), currentByte);
				currentByte += sizeof(uint16_t);
			},
			[&pos,&currentByte](uint64_t* arg)
			{
				pos[currentByte] = 6;
				currentByte++;
				int arraySize = 0;
				uint64_t tempArrayValue = arg[arraySize];
				while (tempArrayValue != UINT64_MAX)
				{
					InsertMemory(pos, static_cast<void*>(&tempArrayValue), sizeof(tempArrayValue), currentByte);
					currentByte += sizeof(uint64_t);
					arraySize++;
					tempArrayValue = arg[arraySize];
				}
				tempArrayValue = UINT64_MAX;
				InsertMemory(pos, static_cast<void*>(&tempArrayValue), sizeof(tempArrayValue), currentByte);
				currentByte += sizeof(uint64_t);
			}
			}, *it);
	}

	if (currentByte != len)
	{
		cout << "Serialization Failed" << endl;
		return false;
	}
	return true;


}

long Serializer::GetDataSize(const vector<PacketVariant>& collection)
{
	long currentByte = 0;
	for (auto it = collection.begin(); it != collection.end(); it++)
	{
		visit(overloaded{
			[&currentByte](uint8_t arg)
			{
				//1 + 1 = 2바이트 추가
				currentByte++;
				currentByte += sizeof(arg);
			},
			[&currentByte](uint16_t arg)
			{
				// 1 + 2 = 3바이트 추가
				currentByte++;
				currentByte += sizeof(arg);
			},
			[&currentByte](string arg)
			{
				// 1 + strlen(2) + str char data (1*N) 바이트 추가
				currentByte++;
				currentByte += sizeof(uint16_t);
				currentByte += strlen(arg.c_str());
				currentByte++;
			},
			[&currentByte](uint64_t arg)
			{
				// 1+ 8바이트 추가
				currentByte++;
				currentByte += sizeof(arg);
			},
			[&currentByte](uint16_t* arg)
			{
				// 1+(2*N) 바이트 추가
				currentByte++;
				int arraySize = 0;
				while (arg[arraySize++] != UINT16_MAX)
				{

				}
				currentByte += sizeof(uint16_t) * (arraySize);
			},
			[&currentByte](uint64_t* arg)
			{
				//1 + (8*N) 바이트 추가
				currentByte++;
				int arraySize = 0;
				while (arg[arraySize++] != UINT64_MAX)
				{

				}
				currentByte += sizeof(double) * (arraySize);
			}
			}, *it);
	}

	return currentByte;
}

void Serializer::InsertMemory(BYTE* pos, void* data, size_t len, int currentByte)
{
	if (len == 2)
	{
		uint16_t* acceptableData = (uint16_t*)data;
		pos[currentByte] = static_cast<BYTE>((*acceptableData >> 0) & 0xFF);
		pos[currentByte + 1] = static_cast<BYTE>((*acceptableData >> 8) & 0xFF);

	}
	else if (len == 4)
	{

	}
	else if (len == 8)
	{
		uint64_t* acceptableData = (uint64_t*)data;
		pos[currentByte] = static_cast<BYTE>((*acceptableData >> 0) & 0xFF);
		pos[currentByte + 1] = static_cast<BYTE>((*acceptableData >> 8) & 0xFF);
		pos[currentByte + 2] = static_cast<BYTE>((*acceptableData >> 16) & 0xFF);
		pos[currentByte + 3] = static_cast<BYTE>((*acceptableData >> 24) & 0xFF);
		pos[currentByte + 4] = static_cast<BYTE>((*acceptableData >> 32) & 0xFF);
		pos[currentByte + 5] = static_cast<BYTE>((*acceptableData >> 40) & 0xFF);
		pos[currentByte + 6] = static_cast<BYTE>((*acceptableData >> 48) & 0xFF);
		pos[currentByte + 7] = static_cast<BYTE>((*acceptableData >> 56) & 0xFF);

	}
}
