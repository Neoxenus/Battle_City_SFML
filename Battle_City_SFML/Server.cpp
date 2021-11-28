#include "Server.h"

void Server::server()
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

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0) 
	{
		std::cout << "Error #2\n";
	}
	else 
	{
		std::cout << "Client Connected!\n";
		char msg[256] = "Hello. It`s my first network program!";
		send(newConnection, msg, sizeof(msg), NULL);


	}

	//system("pause");	
}

void Server::loop(Field& field, std::vector<Bullet>& bullets)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].collision_bullet(field))
		{
			bullets.erase(bullets.begin() + i);
			continue;
		}
	}
}