#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "xstring.h"
#include "Socket.h"

class TcpSocket:public Socket
{
protected:
	int _port;
	string _ip;
	struct tcp_info info;
	struct sockaddr_in &iaddress;
public:
	TcpSocket(void):iaddress(*(struct sockaddr_in*)&address)
	{
		_ip = "0.0.0.0";
		_port = 0;
	}
public:
	bool IsEstablished(void)
	{
		if(GetOption(&info, sizeof(info), TCP_INFO, IPPROTO_TCP)) 
		{
			return (info.tcpi_state == TCP_ESTABLISHED);
		}
		return false;
	}
	const xstring GetSocketString(void)
	{
		if(GetSocketName())
		{
			return xstring("{\"ip\":\"%s\",\"port\":\"%d\"}", 
					inet_ntoa(iaddress.sin_addr), 
					ntohs(iaddress.sin_port));
		}
		return "";
	}
	const xstring GetPeerString(void)
	{
		if(GetPeerName())
		{
			return xstring("{\"ip\":\"%s\",\"port\":\"%d\"}", 
					inet_ntoa(iaddress.sin_addr), 
					ntohs(iaddress.sin_port));
		}
		return "";
	}
};
#endif//__TCPSOCKET_H__
