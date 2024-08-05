#pragma once

#include "GlobalHeader.h"

class NetworkConnector
{
public:
	NetworkConnector() = default;
	NetworkConnector(SOCKADDR_IN sockAddr);
	NetworkConnector(wstring ip, UINT16 port);

	//클라이언트를 색출해내야할때 <- 누가 아이템을 씀 , 누가 씀? 이걸 검출할때 이 함수를 사용하여 
	SOCKADDR_IN& GetSockAddr() { return _sockAddr; }
	wstring GetIpAddress();
	UINT16 GetPort() { return ::ntohs(_sockAddr.sin_port); }

	static IN_ADDR Ip2Address(const WCHAR* ip);

private:
	SOCKADDR_IN _sockAddr = {};

};

