#include <stdio.h>
#include "PacketServer.h"

int main(int argc, char **argv)
{
	time_t last;
	Packet packet;
	PacketServer server;

	if(argc > 2)
	{
		server.Listen(argv[1], atoi(argv[2]), 1);
	}
	else
	{
		server.Listen("0", 8888, 1);
	}
	time_t ss = time(0);
	while(1)
	{
		server.RecvWork();

		if(time(0) - ss > 10)
		{
			time_t xx = time(0);
			while(xx - ss < 20)
			{
				server.RecvWork();
				if(time(0) - xx)
				{
					xx = time(0);
					printf("%s\n", server.GetStatisticString().data());
					printf("buffer.Count(%d).ToInt(%d)\n\n", server.Count(), server.ToInt());
				}
				server.GetPacket(packet);
				usleep(100);
			}
			ss = xx;
		}

		int loop = server.Count() / 1024 + 3;
		for(int i = 0; i < loop; i++)
		{
			server.GetPacket(packet);
		}
		if(time(0) != last && server.IsEstablished())
		{
			last = time(0);
			printf("%s\n", server.GetStatisticString().data());
			printf("buffer.Count(%d).ToInt(%d)\n\n", server.Count(), server.ToInt());
			fflush(stdout);
		}
		xstring s = server.GetSocketString();
		packet.MakePacket(s.data(), 0x33, s.length());
		server.SendPacket(packet);
		usleep(20);
	}

	return 0;
}
