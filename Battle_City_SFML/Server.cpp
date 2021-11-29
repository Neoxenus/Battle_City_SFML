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
}

void Server::loop(Field& field, Tank& tank)
{
	std::vector<char*> tankE;
	std::vector <char*> fieldE;
	int bufSize;
	for (int i = 0; i < 8; i += 2)
	{
		recv(Connection, (char*)&bufSize, sizeof(int), NULL);
		char* buf = new char[bufSize + 1];
		tankE.push_back((char*)&bufSize);
		recv(Connection, buf, bufSize, NULL);
		tankE.push_back(buf);
	}
	tankE.resize(4 * convertBackFromCharArrayToInt(tankE[7] + 8));
	for (int i = 8; i < 8 + 6 * convertBackFromCharArrayToInt(tankE[7]); i += 2)
	{
		recv(Connection, (char*)&bufSize, sizeof(int), NULL);
		char* buf = new char[bufSize + 1];
		tankE.push_back((char*)&bufSize);
		recv(Connection, buf, bufSize, NULL);
		tankE.push_back(buf);
	}
	tank.newTank(tank, tankE);

	for (int i = 0; i < constants::FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < constants::FIELD_WIDTH; ++j)
			field.setField(j, i, static_cast<constants::Tiles>(convertBackFromCharArrayToInt(fieldE[i * constants::FIELD_WIDTH + j])));
	}
		
}