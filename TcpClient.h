#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__
#include "TcpSocket.h"

class TcpClient:public TcpSocket
{
protected:
	long long cnncount;
public:
	TcpClient(void):cnncount(0LL)
	{
		Open();
	}
	~TcpClient(void)
	{
		Close();
	}
public:
	const long long GetConnectCount(void)const
	{
		return cnncount;
	}
public:
	bool Connect(const string& ip="", int port=0)
	{
		if(!ip.empty() && 0 != port)
		{
			_ip = ip;
			_port = port;
		}
		iaddress.sin_family		= AF_INET;
		iaddress.sin_port		= htons(_port);
		iaddress.sin_addr.s_addr= inet_addr(_ip.data());
		if( connect(fd, &address, socklen) )
		{
			if(EINPROGRESS != errno)
			{
				errmsg = strerror(errno);
				return false;
			}
		}
		for(int i = 0; i < 100; i++)
		{
			if(IsEstablished())
			{
				cnncount += 1LL;
				return true;
			}
		}
		return false;
	}
	bool Reconnect(void)
	{
		this->Close();
		this->Open();
		this->Nonblock();
		this->recvcount=0;
		this->sendcount=0;
		return Connect();
	}
};

#endif//__TCPCLIENT_H__
