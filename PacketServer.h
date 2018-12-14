#ifndef __PACKET_SERVER_H__
#define __PACKET_SERVER_H__
#include <time.h>
#include "TcpServer.h"
#include "PacketStatistic.h"

class PacketServer : public TcpServer, public PacketStatistic
{
protected:
	TimeValue cnntime;
	TcpSocket worksocket;
public:
	PacketServer(void)
	{
		Nonblock();
	}
	bool RecvWork(void)
	{
		if(DoRecv() > 0)
		{
			return true;
		}
		AcceptWork();
		return false;
	}
	void AcceptWork(void)
	{
		if(cnntime.Diff().Second() > 0)
		{
			if(worksocket.IsEstablished() == false 
			|| worksocket.GetIoTime().Diff().Second() > 30)
			{
				worksocket.Close();
				if(Accept(worksocket))
				{
					sendPacketCount = 0LL;
					recvPacketCount = 0LL;
					worksocket.Nonblock();
				}
			}
			cnntime.Update();
		}
	}
	bool SendPacket(Packet& packet)
	{
		int len = packet.GetLength() + 4;
		if(worksocket.Send(packet.GetData(), len) == len)
		{
			sendPacketCount += 1LL;
			totalSendPacket += 1LL;
			return true;
		}
		return false;
	}
	bool GetPacket(Packet& packet)
	{
		for(int i = Count(); i > 5; i--)
		{
			if(packet.GetPacket(*this))
			{
				recvPacketCount += 1LL;
				totalRecvPacket += 1LL;
				return true;
			}
		}
		return false;
	}
	bool IsEstablished(void)
	{
		return worksocket.IsEstablished();
	}
	int DoRecv(void)
	{
		int ret = worksocket.Recv(buffer, sizeof(buffer));
		if(ret > 0)
		{
			Push(buffer, ret);
		}
		return ret;
	}
	const xstring GetStatisticString(void)const
	{
		return	xstring("\tacceptCount=%lld\n", acceptcount)
			+	worksocket.GetSocketStatisticString() 
			+	GetPacketStatisticString();
	}
};
#endif//__PACKET_SERVER_H__
