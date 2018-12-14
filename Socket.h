#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "SocketStatistic.h"
#include "TimeValue.h"

class Socket : public SocketStatistic
{
protected:
	int fd;
	string errmsg;
	TimeValue iotime;
	socklen_t socklen;
	struct sockaddr address;
public:
	Socket(void):fd(-1),socklen(sizeof(address))
	{	
		memset(&address, 0, sizeof(address));
	}
	const bool IsValid(void)const
	{
		return (-1 != fd);
	}
	const string& GetErrorMessage(void)const
	{
		return errmsg;
	}
	const socklen_t GetSocketLength(void)const
	{
		return socklen;
	}
	const sockaddr& GetSocketAddress(void)const
	{
		return address;
	}
	const TimeValue& GetIoTime(void)const
	{
		return iotime;
	}
public:
	bool Open(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0)
	{
		fd = socket(domain, type, protocol);
		if(-1 == fd)
		{
			errmsg = strerror(errno);
		}
		return (-1 != fd);
	}
	int Send(const void* buf, int len, int flags=MSG_DONTWAIT|MSG_NOSIGNAL)
	{
		int ret = send(fd, buf, len, flags);
		if(ret < 1)
		{
			errmsg = strerror(errno);
			return ret;
		}
		totalSend += ret;
		sendcount += ret;
		return ret;
	}
	int Recv(void* buf, int len, int flags=MSG_DONTWAIT|MSG_NOSIGNAL)
	{
		int ret = recv(fd, buf, len, flags);
		if(ret < 1)
		{
			errmsg = strerror(errno);
			return ret;
		}
		iotime.Update();
		totalRecv += ret;
		recvcount += ret;
		return ret;
	}
	bool GetOption(void* buf, int len, int optname, int level=SOL_SOCKET)
	{
		socklen = len;
		if( getsockopt(fd, level, optname, buf, &socklen) )
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	bool SetOption(void* buf, int len, int optname, int level=SOL_SOCKET)
	{
		if( setsockopt(fd, level, optname, buf, (socklen_t)len) )
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	bool GetSocketName(void)
	{
		socklen = sizeof(address);
		if( getsockname(fd, &address, &socklen) )
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	bool GetPeerName(void)
	{
		socklen = sizeof(address);
		if( getpeername(fd, &address, &socklen) )
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	bool Nonblock(int nonblock=1)
	{
		int flags = fcntl(fd, F_GETFL);
		if(-1 == flags)
		{
			errmsg = strerror(errno);
			return false;
		}
		if(nonblock)
		{
			flags |= O_NONBLOCK;
		}
		else
		{
			flags &= ~O_NONBLOCK;
		}
		if(fcntl(fd, F_SETFL, flags))
		{
			errmsg = strerror(errno);
			return false;
		}
		return true;
	}
	void Close(void)
	{
		this->recvcount = 0LL;
		this->sendcount = 0LL;
		this->iotime.Update();
		if(-1 != fd)close(fd);
		this->fd = -1;
	}
};
#endif//__SOCKET_H__
