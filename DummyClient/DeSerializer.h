#pragma once


//��Ŷ ��Ģ
//ù 2����Ʈ�� ��Ŷ�� ũ��, ���� 2����Ʈ�� ��Ŷ�� id�̴�.
//��Ŷ�� ID�� ���� ��Ŷ �� ����ִ� �ڷ����� �Ľ̵Ǹ�,
//���������� ��Ŷ�� �����س� �� ClientPacketHandeler���� request�� ó���Ѵ�.
//indicator: 1=uint16, 2=double, 3=string , 4=uint16 array , 5=double array


class DeSerilizer
{
public:
	static shared_ptr<vector<PacketVariant>> DeSerialize(BYTE* buffer, int len);
	static void NextStep(const shared_ptr<vector<PacketVariant>>& collection, BYTE* buffer, int bufferLen);
};

