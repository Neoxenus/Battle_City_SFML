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
	char msg[256];
	//recv(Connection, msg, sizeof(msg), NULL);
	//std::cout << msg << std::endl;



	char msg1[256];
	while (true) {
		std::cin.getline(msg1, sizeof(msg1));
		send(Connection, msg1, sizeof(msg1), NULL);
		Sleep(10);
	}
}

void Client::exchange(Field& field, Tank& tank)
{
	std::string tmp = "sdasdfsasf";
	int tmpSize = tmp.size();

	send(Connection, (char*)&tmpSize, sizeof(int), NULL);
	send(Connection, tmp.c_str(), tmpSize, NULL);
	//std::vector<char*> tankE = tank.sendToServer();
	//std::vector<char*> fieldE = field.sendToServer();
	//char bufSize = sizeof(tankE[0]);
	//send(Connection, (char*)&bufSize, sizeof(char), NULL);
	//send(Connection, tankE[0], bufSize, NULL);

	//for (int i = 0; i < tankE.size(); ++i)
	//{
	//	int bufSize = sizeof(tankE[i]);
	//	send(Connection, (char*)&bufSize, sizeof(int), NULL);
	//	send(Connection, tankE[i], bufSize, NULL);
	//}
	//	
	//for (int i = 0; i < fieldE.size(); ++i)
	//{
	//	int bufSize = sizeof(fieldE[i]);
	//	send(Connection, (char*)&bufSize, sizeof(int), NULL);
	//	send(Connection, fieldE[i], bufSize, NULL);
	//}
		

	//
	//for (int i = 0; i < 8; i+=2)
	//{
	//	recv(Connection, (char*)&tankE[i], sizeof(int), NULL);
	//	recv(Connection, tankE[i+1], convertBackFromCharArrayToInt(tankE[i]), NULL);
	//}
	//tankE.resize(4 * convertBackFromCharArrayToInt(tankE[7] +8));
	//for (int i = 8; i < 8 + 6 * convertBackFromCharArrayToInt(tankE[7]); i+=2)
	//{
	//	recv(Connection, tankE[i], sizeof(int), NULL);
	//	recv(Connection, tankE[i + 1], convertBackFromCharArrayToInt(tankE[i]), NULL);
	//}
	//tank.newTank(tank, tankE);

	//for (int i = 0; i < constants::FIELD_HEIGHT; ++i)
	//	for (int j = 0; j < constants::FIELD_WIDTH; ++j)
	//		field.setField(j,i, static_cast<constants::Tiles>(convertBackFromCharArrayToInt(fieldE[i * constants::FIELD_WIDTH + j])));
}
