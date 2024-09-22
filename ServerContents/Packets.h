#pragma once
struct SamplePacket
{

};

struct CreateRoomPackets : public SamplePacket
{
	uint32_t roomId;
	uint16_t titleLen;
	string title;
	uint16_t pwLen;
	string pw;
};

struct EnterRoomPackets : public SamplePacket
{
	uint32_t roomId;
	uint16_t pwLen;
	string pw;
};


