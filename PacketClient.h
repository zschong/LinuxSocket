#ifndef __PACKET_CLIENT_H__
#define __PACKET_CLIENT_H__
#include "TcpClient.h"
#include "PacketStatistic.h"

class PacketClient : public TcpClient, public PacketStatistic
{
protected:
	TimeValue cnntime;
public:
	PacketClient(void)
	{
		Nonblock();
	}
	bool RecvWork(void)
	{
		if(DoRecv() > 0)
		{
			return true;
		}
		ConnectWork();
		return false;
	}
	void ConnectWork(void)
	{
		if(cnntime.Diff().Second() > 0)
		{
			if(IsEstablished() == false || iotime.Diff().Second() > 30)
			{
				Reconnect();
				iotime.Update();
				sendPacketCount=0LL;
				recvPacketCount=0LL;
			}
			cnntime.Update();
		}
	}
public:
	bool SendPacket(Packet& packet)
	{
		int len = packet.GetLength() + 4;
		if(Send(packet.GetData(), len) == len)
		{
			sendPacketCount += 1LL;
			totalSendPacket += 1LL;
			return true;
		}
		return false;
	}
	int DoRecv(void)
	{
		int ret = Recv(buffer, sizeof(buffer));
		if(ret > 0)
		{
			Push(buffer, ret);
		}
		return ret;
	}
	const xstring GetStatisticString(void)const
	{
		return xstring("\tconnectionCount=%lld\n", cnncount)
			+  GetSocketStatisticString() 
			+  GetPacketStatisticString();
	}
};
#endif//__PACKET_CLIENT_H__
