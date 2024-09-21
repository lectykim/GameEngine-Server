#include "pch.h"
#include "NetworkConnector.h"
NetworkConnector::NetworkConnector(SOCKADDR_IN sockAddr) : _sockAddr(sockAddr)
{
}

NetworkConnector::NetworkConnector(wstring ip, UINT16 port)
{
	::memset(&_sockAddr, 0,sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr = Ip2Address(ip.c_str());
	_sockAddr.sin_port = ::htons(port);
}

wstring NetworkConnector::GetIpAddress()
{
	WCHAR buffer[100];
	::InetNtopW(AF_INET, &_sockAddr.sin_addr, buffer, static_cast<int>(sizeof(buffer)/sizeof(buffer[0])));
	return wstring(buffer);
}

IN_ADDR NetworkConnector::Ip2Address(const WCHAR* ip)
{
	IN_ADDR address;
	::InetPtonW(AF_INET, ip, &address);
	return address;
}
