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
	std::vector<char*> fieldE;
	/*char* tmpTank;
	recv(newConnection, tmpTank, sizeof(tankE[0]), NULL);*/
	//tankE.push_back()
	recv(newConnection, tankE[1], sizeof(tankE[1]), NULL);
	recv(newConnection, tankE[2], sizeof(tankE[2]), NULL);
	recv(newConnection, tankE[3], sizeof(tankE[3]), NULL);
	recv(newConnection, tankE[4], sizeof(tankE[4]), NULL);
	recv(newConnection, tankE[5], sizeof(tankE[5]), NULL);
	recv(newConnection, tankE[6], sizeof(tankE[6]), NULL);
	recv(newConnection, tankE[7], sizeof(tankE[7]), NULL);
	tankE.resize(4 * convertBackFromCharArrayToInt(tankE[7] + 8));
	for (int i = 8; i < tankE.size(); i += 3)
	{
		recv(newConnection, tankE[i], sizeof(tankE[i]), NULL);
		recv(newConnection, tankE[i + 1], sizeof(tankE[i + 1]), NULL);
		recv(newConnection, tankE[i + 2], sizeof(tankE[i + 2]), NULL);
	}
	Tank ansTank(tank, tankE);
	tankE = tank.sendToServer();
	fieldE = field.sendToServer();

	for (int i = 0; i < fieldE.size(); ++i)
		for (int j = 0; j < fieldE.size(); ++j)
			fieldE[i][j] = convertBackFromCharArrayToInt(fieldE[i * fieldE.size() + j]);
	for (int i = 0; i < tankE.size(); ++i)
		send(newConnection, tankE[i], sizeof(tankE[i]), NULL);
	for (int i = 0; i < fieldE.size(); ++i)
		send(newConnection, fieldE[i], sizeof(fieldE[i]), NULL);
}