#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "TcpSocket.h"

class TcpServer:public TcpSocket
{
protected:
	long long acceptcount;
public:
	TcpServer(void):acceptcount(0LL)
	{
		Open();
	}
	~TcpServer(void)
	{
		Close();
	}
public:
	bool Bind(const string& ip="", int port=0)
	{
		if(!ip.empty() && 0 != port)
		{
			_ip = ip;
			_port = port;
		}
		iaddress.sin_family		= AF_INET;
		iaddress.sin_port		= htons(_port);
		iaddress.sin_addr.s_addr= inet_addr(_ip.data());
		if( bind(fd, &address, socklen) )
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	bool Listen(int backlog)
	{
		if( listen(fd, backlog) )
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	bool Listen(const string& ip, int port, int backlog)
	{
		return ReuseAddress(1) && Bind(ip, port) && Listen(backlog);
	}
	bool Accept(TcpSocket& sock)
	{
		TcpServer &s = *(TcpServer*)&sock;

		s.socklen = sizeof(s.address);
		s.fd = accept(fd, &s.address, &s.socklen);
		if(-1 == s.fd)
		{
			errmsg = strerror(errno);
			return false;
		}
		acceptcount += 1LL;
		return true;
	}
	bool ReuseAddress(int value=1)
	{
		return SetOption(&value, sizeof(value), SO_REUSEADDR, SOL_SOCKET);
	}
	const long long GetAcceptCount(void)const
	{
		return acceptcount;
	}
};

#endif//__TCPSERVER_H__
