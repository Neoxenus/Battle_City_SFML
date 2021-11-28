#include "Client.h"

void Client::client()
{
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) 
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("26.248.220.2");
	addr.sin_port = htons(3490);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) 
	{
		std::cout << "Error: failed connect to server.\n";
		exit(1);
	}
	std::cout << "Connected!\n";
}

//void Client::exchange(constants::Packet pk)
//{
//	//char buffer[sizeof(pk)];
//	//memcpy(buffer, &pk, sizeof(pk));
//	//int bytesSent = sendto(Connection, data, sizeof(pk), 0, (const sockaddr*)&addr, sizeof(addr));
//	//if (bytesSent > 0)
//	//{
//	//	std::cout << bytesSent << std::endl;
//	//}
//	//send(Connection, pk, sizeof(pk), NULL);
//
//}
