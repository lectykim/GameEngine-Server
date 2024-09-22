#include "pch.h"
#include "DeSerializer.h"
shared_ptr<vector<PacketVariant>> DeSerilizer::DeSerialize(BYTE* buffer, int len)
{

    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    uint16_t num = header->id;

    shared_ptr<vector<PacketVariant>> collection = make_shared<vector<PacketVariant>>();
    collection->emplace_back(num);
    NextStep(collection, buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

    return collection;


}



void DeSerilizer::NextStep(const shared_ptr<vector<PacketVariant>>& collection, BYTE* buffer, int bufferLen)
{
    while (bufferLen > 0)
    {
        //Ã¹±ÛÀÚ ÆÄ½Ì
        uint8_t* indicator = reinterpret_cast<uint8_t*>(buffer);
        buffer += sizeof(uint8_t);
        int dataSize = 0;
        if (*indicator == 1)
        {
            uint16_t* data = reinterpret_cast<uint16_t*>(buffer);
            collection->emplace_back(data);
            buffer += sizeof(uint16_t);
            dataSize += sizeof(uint16_t);
        }
        else if (*indicator == 2)
        {
            double* data = reinterpret_cast<double*>(buffer);
            collection->emplace_back(data);
            buffer += sizeof(double);
            dataSize += sizeof(double);
        }
        else if (*indicator == 3)
        {
            uint16_t* len = reinterpret_cast<uint16_t*>(buffer);
            buffer += sizeof(uint16_t);
            dataSize += sizeof(uint16_t);
            dataSize += *len;

            if (dataSize > bufferLen)
            {
                collection->clear();
                return;
            }

            string data(reinterpret_cast<char*>(buffer), *len);
            buffer += *len;

            collection->emplace_back(data);
        }
        else if (*indicator == 4)
        {
            uint16_t* len = reinterpret_cast<uint16_t*>(buffer);
            buffer += sizeof(uint16_t);
            dataSize += sizeof(uint16_t);
            dataSize += sizeof(uint16_t) * (*len);

            if (dataSize > bufferLen)
            {
                collection->clear();
                return;
            }

            uint16_t* dataArray = new uint16_t[*len];
            for (int i = 0; i < *len; i++)
            {
                uint16_t* data = reinterpret_cast<uint16_t*>(buffer);
                buffer += sizeof(uint16_t);
                dataArray[i] = *data;
            }

            collection->emplace_back(dataArray);
        }
        else if (*indicator == 5)
        {
            uint16_t* len = reinterpret_cast<uint16_t*>(buffer);
            buffer += sizeof(uint16_t);
            dataSize += sizeof(uint16_t);
            dataSize += sizeof(double) * (*len);

            if (dataSize > bufferLen)
            {
                collection->clear();
                return;
            }

            double* dataArray = new double[*len];
            for (int i = 0; i < *len; i++)
            {
                double* data = reinterpret_cast<double*>(buffer);
                buffer += sizeof(double);
                dataArray[i] = *data;
            }

            collection->emplace_back(dataArray);
        }
        else
        {
            collection->clear();
            return;
        }

        bufferLen -= dataSize;
    }





}
