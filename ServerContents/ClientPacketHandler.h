#pragma once


#include "Packets.h"
#include <variant>
#include "Serializer.h"
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
class ClientPacketHandler 
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

	static shared_ptr<SendBuffer> MakeSendBuffer(const vector<PacketVariant>& collection,uint16_t pktId )
	{
		
		const uint16_t dataSize = static_cast<uint16_t>(Serializer::GetDataSize(collection));
		const uint16_t pktSize = dataSize + sizeof(PacketHeader);

		shared_ptr<SendBuffer> sendBuffer = GSendBufferManager->Open(pktSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = pktSize;
		header->id = pktId;
		if (Serializer::Serialization(collection, reinterpret_cast<BYTE*>(&header[1]), dataSize) == false)
		{
			return nullptr;
		}
		else
		{
			sendBuffer->Close(pktSize);
			return sendBuffer;
		}
	}

};