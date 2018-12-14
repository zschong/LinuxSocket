#ifndef __SOCKET_COUNTER_H__
#define __SOCKET_COUNTER_H__
#include "xstring.h"

class SocketStatistic
{
protected:
	long long sendcount;
	long long recvcount;
	long long totalSend;
	long long totalRecv;
public:
	SocketStatistic(void):
	sendcount(0LL),
	recvcount(0LL),
	totalSend(0LL),
	totalRecv(0LL)
	{
	}
public:
	const long long GetSendCount(void)const
	{
		return sendcount;
	}
	const long long GetRecvCount(void)const
	{
		return recvcount;
	}
	const long long GetTotalSend(void)const
	{
		return totalSend;
	}
	const long long GetTotalRecv(void)const
	{
		return totalRecv;
	}
public:
	const xstring GetSocketStatisticString(void)const
	{
		return xstring("\trecvcount=%lld\n"
					   "\tsendcount=%lld\n"
					   "\ttotalRecv=%lld\n"
					   "\ttotalSend=%lld\n",
					   this->recvcount,
					   this->sendcount,
					   this->totalRecv,
					   this->totalSend);
	}
};

#endif//__SOCKET_COUNTER_H__
