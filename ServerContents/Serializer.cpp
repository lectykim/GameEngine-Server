#include "pch.h"
#include "Serializer.h"

bool Serializer::Serialization(const vector<PacketVariant>& collection,BYTE* pos,uint16_t len)
{
	int currentByte = 0;
	for (auto it = collection.begin();it != collection.end();it++)
	{
		
		visit(overloaded{
			[&pos,&currentByte](uint8_t arg) 
			{
				::memcpy(pos+currentByte,reinterpret_cast<const void*>(0x0001),1);
				currentByte++;
				::memcpy(pos + currentByte, reinterpret_cast<const void*>(arg), sizeof(arg));
				currentByte += sizeof(arg);
			},
			[&pos,&currentByte](uint16_t arg) 
			{
				::memcpy(pos + currentByte,reinterpret_cast<const void*>(0x0002),1);
				currentByte++;
				::memcpy(pos + currentByte, reinterpret_cast<const void*>(arg), sizeof(arg));
				currentByte += sizeof(arg);
			},
			[&pos,&currentByte](string arg) 
			{
				::memcpy(pos + currentByte,reinterpret_cast<const void*>(0x0003),1);
				currentByte++;
				uint16_t strLen = static_cast<uint16_t>(sizeof(arg.c_str()));
				::memcpy(pos + currentByte, reinterpret_cast<const void*>(strLen), sizeof(uint16_t));
				currentByte += sizeof(uint16_t);
				::memcpy(pos+currentByte, arg.c_str(), strlen(arg.c_str()));
				currentByte += strlen(arg.c_str());
			},
			[&pos,&currentByte](uint64_t arg) 
			{
				::memcpy(pos + currentByte,reinterpret_cast<const void*>(0x0004),1);
				currentByte++;
				::memcpy(pos + currentByte, reinterpret_cast<void*>(arg), sizeof(arg));
				currentByte += sizeof(arg);
			},
			[&pos,&currentByte](uint16_t* arg) 
			{
				::memcpy(pos + currentByte,reinterpret_cast<const void*>(0x0005),1);
				currentByte++;
				int arraySize = 0;
				uint16_t tempArrayValue = arg[arraySize];
				while (tempArrayValue != UINT16_MAX)
				{
					::memcpy(pos + currentByte, reinterpret_cast<const void*>(tempArrayValue), sizeof(uint16_t));
					currentByte += sizeof(uint16_t);
					arraySize++;
					tempArrayValue = arg[arraySize];
				}
				::memcpy(pos + currentByte, reinterpret_cast<const void*>(UINT16_MAX), sizeof(uint16_t));
				currentByte += sizeof(uint16_t);
			},
			[&pos,&currentByte](uint64_t* arg) 
			{
				::memcpy(pos + currentByte,reinterpret_cast<const void*>(0x0006),1);
				currentByte++;
				int arraySize = 0;
				uint64_t tempArrayValue = arg[arraySize];
				while (tempArrayValue != UINT64_MAX)
				{
					::memcpy(pos + currentByte, reinterpret_cast<const void*>(tempArrayValue), sizeof(uint64_t));
					currentByte += sizeof(uint64_t);
					arraySize++;
					tempArrayValue = arg[arraySize];
				}
				::memcpy(pos + currentByte, reinterpret_cast<const void*>(UINT64_MAX), sizeof(uint64_t));
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
				currentByte += static_cast<uint16_t>(sizeof(arg.c_str()));
				currentByte += sizeof(arg.c_str());
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
				while (arg[arraySize++] != UINT64_MAX)
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
