#include "TcpServer.h"

int main(void)
{
	TcpSocket socket;
	TcpServer server;

	if(server.Listen("0", 8888, 1)==false)
	{
		return -printf("Listen:%s", server.GetErrorMessage().data());
	}
	if(server.Accept(socket) == false)
	{
		return -printf("Accept:%s", server.GetErrorMessage().data());
	}
	if(socket.Send("test\n", 5)<1)
	{
		return -printf("Send:%s", server.GetErrorMessage().data());
	}
	for(int i = 0; i < 10; i++)
	{
		char buf[32] = {0};
		if(socket.Recv(buf, sizeof(buf), 0) > 0)
		{
			printf("%s\n", buf);
		}
	}
	return 0;
}
