#pragma once

//��Ŷ ��Ģ
//ù 2����Ʈ�� ��Ŷ�� ũ��, ���� 2����Ʈ�� ��Ŷ�� id�̴�.
//��Ŷ�� ID�� ���� ��Ŷ �� ����ִ� �ڷ����� �Ľ̵Ǹ�,
//���������� ��Ŷ�� �����س� �� ClientPacketHandeler���� request�� ó���Ѵ�.
//indicator: 1=uint8, 2=uint16, 3=string, 4=uint64 , 5=uint16 array , 6=uint64 array
//5�� �迭�� ������ ���� uint16_max��,
//6�� �迭�� ������ ���� double_max�� �������μ� LEN�� �Ǻ��Ѵ�.
class Serializer
{
public:
	static bool Serialization(const vector<PacketVariant>& collection, BYTE* pos, uint16_t len);
	static long GetDataSize(const vector<PacketVariant>& collection);

	static void InsertMemory(BYTE* pos, void* data, size_t len, int currentByte);
};

