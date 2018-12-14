#ifndef __NETPACKET_H__
#define __NETPACKET_H__
#include "xstring.h"
#include "ByteQueue.h"
#include "PacketType.h"

class Packet
{
protected:
    char m_data[1<<15];//32K

public:
	Packet(void)
	{
		memset(m_data, 0, sizeof(m_data));
	}
	Packet(const char* buf, char cmd, unsigned len)
	{
		memset(m_data, 0, sizeof(m_data));
		this->MakePacket(buf, cmd, len);
	}
	bool MakePacket(const char *buf, char cmd, unsigned len)
	{
		if( buf && (4 + 1 + len) <= sizeof(m_data) )
		{
			SetLength(len + 1);
			SetCommand(cmd);
			SetData(buf, len);
			return true;
		}
		return false;
	}
	bool GetPacket(ByteQueue& queue)
	{
		int count = queue.Count();
		int length = queue.ToInt() + 4;

		if((length < 4 ) || (length > sizeof(m_data)))
		{
			queue.Pop(1);
			return false;
		}
		if(count < 5 || length > count)
		{
			return false;
		}
		queue.Peek(m_data, length);
		queue.Pop(length);
		return true;
	}
	void SetLength(unsigned length)
	{
		m_data[0] = char(length >> 24);
		m_data[1] = char(length >> 16);
		m_data[2] = char(length >> 8);
		m_data[3] = char(length >> 0);
	}
	void SetCommand(char cmd)
	{
		m_data[4] = cmd;
	}
	void SetData(const char *buf, unsigned len)
	{
		if( (4 + 1 + len) <= sizeof(m_data) )
		{
			memcpy(m_data + 5, buf, len);
		}
	}
	const void* GetData(void)const
	{
		return m_data;
	}
	const unsigned GetLength(void)const
	{
		unsigned length = 0;
		length |= (unsigned(m_data[0] & 0xFF) << 24);
		length |= (unsigned(m_data[1] & 0xFF) << 16);
		length |= (unsigned(m_data[2] & 0xFF) << 8);
		length |= (unsigned(m_data[3] & 0xFF) << 0);
		return length;
	}
	const char GetCommand(void)const
	{
		return m_data[4];
	}
	const char* GetBody(void)const
	{
		return m_data+5;
	}
	const xstring GetString(void)const
	{
		return xstring("length(%u).cmd(%02X).body(%s)", GetLength(), GetCommand(), GetBody());
	}
};

#endif//__NETPACKET_H__
