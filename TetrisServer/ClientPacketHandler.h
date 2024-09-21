#pragma once
#include "Session.h"



enum : uint16_t
{
	PKT_INVALID = 1000,
	PKT_CREATE_ROOM = 1001,
	PKT_ENTER_ROOM = 1002,
	PKT_CHANGE_ROOM = 1003,
	PKT_DELETE_ROOM = 1004
};
using PacketHandlerFunc = std::function <void()>;
class ClientPacketHandler
{
	static void Init()
	{

	}
};

