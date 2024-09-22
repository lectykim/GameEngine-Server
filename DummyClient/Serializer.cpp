#include "pch.h"
#include "Serializer.h"

PacketStructure* Serializer::Serialization(const PacketHeader& header, const shared_ptr<vector<PacketVariant>>& collection)
{
	BYTE* buffer = new BYTE;
	PacketHeader* headerWritePos = reinterpret_cast<PacketHeader*>(buffer);
	headerWritePos->id = header.id;
	headerWritePos->size = 0;

	BYTE* bodyWritePos = reinterpret_cast<BYTE*>(&headerWritePos[1]);



	int currentByte = 0;
	for (auto it = collection->begin(); it != collection->end(); it++)
	{

		visit(overloaded{
			[&bodyWritePos,&currentByte](uint8_t arg)
			{
				bodyWritePos[currentByte] = 0;
				currentByte++;
				bodyWritePos[currentByte] = arg;
				currentByte += sizeof(arg);
			},
			[&bodyWritePos,&currentByte](uint16_t arg)
			{
				bodyWritePos[currentByte] = 1;
				currentByte++;
				bodyWritePos[currentByte] = arg;
				currentByte += sizeof(arg);
			},
			[&bodyWritePos,&currentByte](string arg)
			{
				bodyWritePos[currentByte] = 2;
				currentByte++;
				bodyWritePos[currentByte] = static_cast<uint16_t>(sizeof(arg.c_str()));
				currentByte += static_cast<uint16_t>(sizeof(arg.c_str()));
				::memcpy(bodyWritePos, arg.c_str(), sizeof(arg.c_str()));
				currentByte += sizeof(arg.c_str());
			},
			[&bodyWritePos,&currentByte](double arg)
			{
				bodyWritePos[currentByte] = 3;
				currentByte++;
				bodyWritePos[currentByte] = arg;
				currentByte += sizeof(arg);
			},
			[&bodyWritePos,&currentByte](uint16_t* arg)
			{
				bodyWritePos[currentByte] = 4;
				currentByte++;
				int arraySize = 0;
				uint16_t tempArrayValue = arg[arraySize];
				while (tempArrayValue != UINT16_MAX)
				{
					tempArrayValue = arg[++arraySize];
				}
				::memcpy(bodyWritePos, arg, sizeof(uint16_t) * (--arraySize));
				currentByte += sizeof(uint16_t) * (arraySize);
			},
			[&bodyWritePos,&currentByte](double* arg)
			{
				bodyWritePos[currentByte] = 5;
				currentByte++;
				int arraySize = 0;
				double tempArrayValue = arg[arraySize];
				while (tempArrayValue != UINT64_MAX)
				{
					tempArrayValue = arg[++arraySize];
				}
				::memcpy(bodyWritePos, arg, sizeof(double) * (--arraySize));
				currentByte += sizeof(double) * (arraySize);
			}
			}, *it);
	}
	currentByte += sizeof(PacketHeader);

	return new PacketStructure{ buffer, currentByte };

}
