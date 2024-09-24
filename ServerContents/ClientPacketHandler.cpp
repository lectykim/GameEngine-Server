#include "pch.h"
#include "ClientPacketHandler.h"
#include <cstdio>
PacketHandlerFunc GPacketHandler[UINT16_MAX];
void HandleInvalid(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection)
{
	cout << "Invalid calls" << endl;
}

void HandleCreateRoom(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection)
{
	cout << "Create Room Calls" << endl;
	PacketVariant* datas = collection->data();
	auto arrayData = get_if<uint16_t*>(&datas[3]);
	uint16_t temp = 0, value = 0;
	printf("%d", (*arrayData)[1]);
	printf("%d", *arrayData[1]);
	auto arrayUintData = get_if<uint16_t*>(&datas[4]);

}

void HandleEnterRoom(const shared_ptr<PacketSession>& session, const shared_ptr<vector<PacketVariant>>& collection)
{

	cout << "Enter Room Calls" << endl;
}
