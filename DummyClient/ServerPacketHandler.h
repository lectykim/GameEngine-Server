#pragma once
using PacketHandlerFunc = function<void(const shared_ptr<PacketSession>&, const shared_ptr<vector<PacketVariant>>&)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum PacketNumber : uint16_t
{
	PKT_CREATE_ROOM = 1000,
	PKT_ENTER_ROOM = 1001
};

void HandleInvalid(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection);
void HandleCreateRoom(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection);
void HandleEnterRoom(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = HandleInvalid;
		GPacketHandler[PKT_CREATE_ROOM] = HandleCreateRoom;
		GPacketHandler[PKT_ENTER_ROOM] = HandleEnterRoom;
	}

	static void HandlePacket(const shared_ptr<PacketSession>& session, const shared_ptr< vector<PacketVariant>>& collection)
	{
		if (collection->empty())
			GPacketHandler[0](session, collection);
		else
		{
			uint16_t* id = get_if<uint16_t>(&collection->front());
			GPacketHandler[*id](session, collection);
		}

	}
};

