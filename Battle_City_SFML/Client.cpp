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

void Client::exchange(Field& field, Tank& tank)
{
	std::vector<char*> tankE = tank.sendToServer();
	std::vector<char*> fieldE = field.sendToServer();
	for(int i=0;i<tankE.size();++i)
		send(Connection, tankE[i], sizeof(tankE[i]), NULL);
	for (int i = 0; i < fieldE.size(); ++i)
		send(Connection, fieldE[i], sizeof(fieldE[i]), NULL);
	recv(Connection, tankE[0], sizeof(tankE[0]), NULL);
	recv(Connection, tankE[1], sizeof(tankE[1]), NULL);
	recv(Connection, tankE[2], sizeof(tankE[2]), NULL);
	recv(Connection, tankE[3], sizeof(tankE[3]), NULL);
	recv(Connection, tankE[4], sizeof(tankE[4]), NULL);
	recv(Connection, tankE[5], sizeof(tankE[5]), NULL);
	recv(Connection, tankE[6], sizeof(tankE[6]), NULL);
	recv(Connection, tankE[7], sizeof(tankE[7]), NULL);
	tankE.resize(4 * convertBackFromCharArrayToInt(tankE[7] +8));
	for (int i = 8; i < tankE.size(); i+=3)
	{
		recv(Connection, tankE[i], sizeof(tankE[i]), NULL);
		recv(Connection, tankE[i+1], sizeof(tankE[i+1]), NULL);
		recv(Connection, tankE[i+2], sizeof(tankE[i+2]), NULL);
	}
	Tank ansTank(tank, tankE);

	for (int i = 0; i < fieldE.size(); ++i)
		for (int j = 0; j < fieldE.size(); ++j)
			fieldE[i][j] = convertBackFromCharArrayToInt(fieldE[i* fieldE.size()+ j]);
}
