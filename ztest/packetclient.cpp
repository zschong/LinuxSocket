#include <stdio.h>
#include "PacketClient.h"

int main(int argc, char **argv)
{
	time_t last;
	Packet packet;
	PacketClient client;

	if(argc > 2)
	{
		client.Connect(argv[1], atoi(argv[2]));
	}
	else
	{
		client.Connect("0", 8888);
	}
	while(1)
	{
		client.RecvWork();
		int loop = client.Count()/1024 + 3;
		for(int i = 0; i < loop; i++)
		{
			client.GetPacket(packet);
		}
		if(client.GetRecvPacketCount()%8 && loop > 3)
		{
			client.SendPacket(packet);
		}
		if(time(0) != last && client.Count() > 0)
		{
			last = time(0);
			printf("%s\n", client.GetStatisticString().data());
			printf("iotime(%s.%d)\n", client.GetIoTime().ToString("%T").data(), client.GetIoTime().Usecond());
			printf("buffer.Count(%d).ToInt(%d)\n\n", client.Count(), client.ToInt());
			fflush(stdout);
		}
		else if(time(0)-last>1)
		{
			last = time(0);
			printf("%s\n", client.GetStatisticString().data());
			printf("buffer.Count(%d).ToInt(%d)\n\n", client.Count(), client.ToInt());
		}
		//usleep(100);
	}

	return 0;
}
