#include "Socket.h"
#include "TcpClient.h"

int main(void)
{
	TcpClient client;

	if(client.Connect("0", 8888))
	{
		for(int i = 0; i < 10; i++)
		{
			printf("send=%d\n", client.Send((char*)"tttt\n", 5, 0));
		}
	}
	getchar();

	return 0;
}
