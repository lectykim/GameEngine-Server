#pragma once

struct PacketStructure
{
	BYTE* buffer;
	int len;
};

//패킷 규칙
//첫 2바이트는 패킷의 크기, 이후 2바이트는 패킷의 id이다.
//패킷의 ID에 따라 패킷 내 들어있는 자료형이 파싱되며,
//최종적으로 패킷을 생성해낸 후 ClientPacketHandeler에서 request를 처리한다.
//indicator: 1=uint16, 2=double, 3=string , 4=uint16 array , 5=double array
//4번 배열의 마지막 값은 uint16_max를,
//5번 배열의 마지막 값은 double_max를 넣음으로서 LEN을 판별한다.
class Serializer
{
public:
	static bool Serialization(const vector<PacketVariant>& collection, BYTE* pos, uint16_t len);
	static long GetDataSize(const vector<PacketVariant>& collection);
};

