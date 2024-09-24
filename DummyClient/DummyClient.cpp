#include "pch.h"
#include "ServerPacketHandler.h"

//#include "DeSerializer.h"
char sendData[] = "Hello World";

class ServerSession : public PacketSession
{
public:
	~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	virtual void OnConnected() override
	{

		cout << "Connected" << endl;

	}

	virtual void OnRecvPacket(BYTE* buffer, int len) override
	{
		shared_ptr<PacketSession> session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		//TODO : PacketId 대역 체크
		/*auto collection = DeSerilizer::DeSerialize(buffer, len);
		ServerPacketHandler::HandlePacket(session, collection);*/
	}

	virtual void OnSend(int len) override
	{
		//cout << "OnSend Len = " << len << endl;
	}

	virtual void OnDisconnected() override
	{
		cout << "Disconnected" << endl;
	}
};

int main()
{



	ServerPacketHandler::Init();
	this_thread::sleep_for(1s);

	shared_ptr<ClientService> service = make_shared<ClientService>(
		NetworkConnector(L"127.0.0.1", 7777),
		make_shared<IocpCore>(),
		static_cast<SessionFactory>(make_shared<ServerSession>),
		1
	);

	service->Start();
	for (int i = 0; i < 2; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	GThreadManager->Launch([=]() {

		while (true)
		{
			int menu = 0;
			cout << "1. create room, 2. enter room, 3: exit" << endl;

			cin >> menu;
			switch (menu)
			{
			case 1:
			{
				uint8_t sampleId = 10;
				uint16_t roomId = 655;
				string id = "password";
				uint64_t bigId = 2133213213;
				uint16_t sampleArr[10] = { 0, };
				sampleArr[0] = 3;
				sampleArr[1] = 2;
				sampleArr[2] = 1;
				sampleArr[3] = UINT16_MAX;
				uint64_t sampleBigArr[10] = { 0, };
				sampleBigArr[0] = 3;
				sampleBigArr[1] = 2;
				sampleBigArr[2] = 1;
				sampleBigArr[3] = UINT64_MAX;
				vector<PacketVariant> collection;
				collection.emplace_back(roomId);
				collection.emplace_back(id);
				collection.emplace_back(bigId);
				collection.emplace_back(sampleArr);
				collection.emplace_back(sampleBigArr);
				auto buffer = ServerPacketHandler::MakeSendBuffer(collection, PKT_CREATE_ROOM);
				service->Broadcast(buffer);
				break;
			}
			case 2:
			{



				break;
			}
			case 3:
			{
				service->CloseService();
				break;
			}
			default:
			{
				break;
			}
			}
		}
		});

	GThreadManager->Join();
}