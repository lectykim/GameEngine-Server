#pragma once


//패킷 규칙
//첫 2바이트는 패킷의 크기, 이후 2바이트는 패킷의 id이다.
//패킷의 ID에 따라 패킷 내 들어있는 자료형이 파싱되며,
//최종적으로 패킷을 생성해낸 후 ClientPacketHandeler에서 request를 처리한다.
//indicator: 1=uint16, 2=double, 3=string , 4=uint16 array , 5=double array


class DeSerilizer
{
public:
	static shared_ptr<vector<PacketVariant>> DeSerialize(BYTE* buffer, int len);
	static void NextStep(const shared_ptr<vector<PacketVariant>>& collection, BYTE* buffer, int bufferLen);
};

