CXX:=$(ARCH)g++
STRIP:=$(ARCH)strip
TARGET:=client.exe 
TARGET+=server.exe 
TARGET+=packetclient.exe 
TARGET+=packetserver.exe

all:$(TARGET)
	@$(STRIP) $+
	@ls -sh $+
client.exe:ztest/client.cpp
	$(CXX) $+ -I. -o $@ -g
server.exe:ztest/server.cpp
	$(CXX) $+ -I. -o $@ -g
packetclient.exe:ztest/packetclient.cpp
	$(CXX) $+ -I. -o $@ -g
packetserver.exe:ztest/packetserver.cpp
	$(CXX) $+ -I. -o $@ -g
powerpc:
	make ARCH=powerpc-e300c3-linux-gnu-

clean:
	@rm -rfv *.exe
