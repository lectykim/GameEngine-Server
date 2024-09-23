#include "pch.h"
#include "GameSession.h"
#include "DeSerializer.h"
#include "ClientPacketHandler.h"
void GameSession::OnConnected()
{
	wcout << L"Connected : " << GetSessionRef()->GetAddress().GetIpAddress() << endl;
}

void GameSession::OnDisconnected()
{
	wcout  << L"DisConnected" << GetSessionRef()->GetAddress().GetIpAddress() << endl;
}

void GameSession::OnRecvPacket(BYTE* buffer, int len)
{
	shared_ptr<PacketSession> session = GetPacketSessionRef();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	//TODO : PacketId 대역 체크
	auto collection = DeSerilizer::DeSerialize(buffer, len);
	ClientPacketHandler::HandlePacket(session,collection);
}

void GameSession::OnSend(int len)
{
}
