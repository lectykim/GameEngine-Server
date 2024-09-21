#pragma once

using PacketHandlerFunc = function<void(const shared_ptr<PacketSession>&,BYTE*, int)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum PacketNumber : uint16_t
{
	PKT_CREATE_ROOM = 1000,
	PKT_ENTER_ROOM = 1001
};

void HandleInvalid(const shared_ptr<PacketSession>& session, BYTE* buffer, int len);
void HandleCreateRoom(const shared_ptr<PacketSession>& session, BYTE* buffer, int len);
void HandleEnterRoom(const shared_ptr<PacketSession>& session, BYTE* buffer, int len);
class ClientPacketHandler 
{
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = HandleInvalid;
		GPacketHandler[PKT_CREATE_ROOM] = HandleCreateRoom;
		GPacketHandler[PKT_ENTER_ROOM] = HandleEnterRoom;
	}
};