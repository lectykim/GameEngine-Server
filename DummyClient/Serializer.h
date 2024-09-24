#pragma once

struct PacketStructure
{
	BYTE* buffer;
	int len;
};

//��Ŷ ��Ģ
//ù 2����Ʈ�� ��Ŷ�� ũ��, ���� 2����Ʈ�� ��Ŷ�� id�̴�.
//��Ŷ�� ID�� ���� ��Ŷ �� ����ִ� �ڷ����� �Ľ̵Ǹ�,
//���������� ��Ŷ�� �����س� �� ClientPacketHandeler���� request�� ó���Ѵ�.
//indicator: 1=uint16, 2=double, 3=string , 4=uint16 array , 5=double array
//4�� �迭�� ������ ���� uint16_max��,
//5�� �迭�� ������ ���� double_max�� �������μ� LEN�� �Ǻ��Ѵ�.
class Serializer
{
public:
	static bool Serialization(const vector<PacketVariant>& collection, BYTE* pos, uint16_t len);
	static long GetDataSize(const vector<PacketVariant>& collection);
};

