#include "pch.h"
#include "ServerPacketHandler.h"
PacketHandlerFunc GPacketHandler[UINT16_MAX];

void HandleInvalid(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection)
{
	cout << "Invalid calls" << endl;
}

void HandleCreateRoom(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection)
{
	cout << "Create Room Calls" << endl;
	/*PacketHeader header = PacketHeader{ 0,PKT_CREATE_ROOM };
	shared_ptr<vector<PacketVariant>> retCol = make_shared<vector<PacketVariant>>();
	retCol->emplace_back(0);
	auto packet = Serializer::Serialization(header, retCol);
	session->Send(make_shared<BYTE*>(packet->buffer));*/

}

void HandleEnterRoom(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection)
{

	cout << "Enter Room Calls" << endl;
}
