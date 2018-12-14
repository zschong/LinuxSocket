#ifndef __PACKET_HELPER_H__
#define __PACKET_HELPER_H__
#include "Packet.h"
#include "ByteQueue.h"

class PacketStatistic : public ByteQueue
{
protected:
	char buffer[1024];
	long long totalRecvPacket;
	long long totalSendPacket;
	long long sendPacketCount;
	long long recvPacketCount;
public:
	PacketStatistic(void):
	sendPacketCount(0LL),
	recvPacketCount(0LL),
	totalRecvPacket(0LL),
	totalSendPacket(0LL)
	{
	}
	const long long GetSendPacketCount(void)const
	{
		return sendPacketCount;
	}
	const long long GetRecvPacketCount(void)const
	{
		return recvPacketCount;
	}
	const long long GetTotalSendPacket(void)const
	{
		return totalSendPacket;
	}
	const long long GetTotalRecvPacket(void)const
	{
		return totalRecvPacket;
	}
	const xstring GetPacketStatisticString(void)const
	{
		return xstring("\ttotalRecvPacket(%lld)\n"
					   "\ttotalSendPacket(%lld)\n"
					   "\trecvPacketCount(%lld)\n"
					   "\tsendPacketCount(%lld)\n",
					   this->totalRecvPacket,
					   this->totalSendPacket,
					   this->recvPacketCount,
					   this->sendPacketCount);
	}
public:
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
};
#endif//__PACKET_HELPER_H__
