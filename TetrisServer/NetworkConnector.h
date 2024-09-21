#pragma once
class NetworkConnector
{
public:
	NetworkConnector() = default;
	NetworkConnector(SOCKADDR_IN sockAddr);
	NetworkConnector(wstring ip, UINT16 port);

	//Ŭ���̾�Ʈ�� �����س����Ҷ� <- ���� �������� �� , ���� ��? �̰� �����Ҷ� �� �Լ��� ����Ͽ� 
	SOCKADDR_IN& GetSockAddr() { return _sockAddr; }
	wstring GetIpAddress();
	UINT16 GetPort() { return ::ntohs(_sockAddr.sin_port); }

	static IN_ADDR Ip2Address(const WCHAR* ip);

private:
	SOCKADDR_IN _sockAddr = {};

};

