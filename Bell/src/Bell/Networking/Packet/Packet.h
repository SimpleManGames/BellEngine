#ifndef _PACKET_H
#define _PACKET_H

#include <winsock2.h>
#include <string>
#include <vector>

namespace Bell
{
    class Packet
    {
        typedef bool (Packet::* BoolType)(std::size_t);

    public:
        Packet();
        virtual ~Packet();

        void Append(const void* data, std::size_t sizeInBytes);
        void Clear();

        const void* GetData() const;
        std::size_t GetDataSize() const;
        bool EndOfPacket() const;

    public:
        // Compare
        operator BoolType() const;

        // Read
        Packet& operator >>(bool& data);

        Packet& operator >>(Int8& data);
        Packet& operator >>(Uint8& data);

        Packet& operator >>(Int16& data);
        Packet& operator >>(Uint16& data);

        Packet& operator >>(Int32& data);
        Packet& operator >>(Uint32& data);

        Packet& operator >>(Int64& data);
        Packet& operator >>(Uint64& data);

        Packet& operator >>(float& data);
        Packet& operator >>(double& data);
        Packet& operator >>(char* data);
        Packet& operator >>(std::string& data);
        Packet& operator >>(wchar_t* data);
        Packet& operator >>(std::wstring& data);

        // Write
        Packet& operator <<(bool data);

        Packet& operator <<(Int8 data);
        Packet& operator <<(Uint8 data);

        Packet& operator <<(Int16 data);
        Packet& operator <<(Uint16 data);

        Packet& operator <<(Int32 data);
        Packet& operator <<(Uint32 data);

        Packet& operator <<(Int64 data);
        Packet& operator <<(Uint64 data);

        Packet& operator <<(float data);
        Packet& operator <<(double data);
        Packet& operator <<(const char* data);
        Packet& operator <<(const std::string& data);
        Packet& operator <<(const wchar_t* data);
        Packet& operator <<(const std::wstring& data);

    private:
        bool operator ==(const Packet& right) const;
        bool operator !=(const Packet& right) const;

        bool CheckSize(std::size_t size);

    private:
        std::vector<char> m_Data;
        std::size_t m_ReadPos;
        bool m_IsValid;
    };
}

#endif // !_PACKET_H