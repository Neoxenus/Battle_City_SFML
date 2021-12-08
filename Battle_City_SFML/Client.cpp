#include "Client.h"

void Client::client()
{
	//WSAStartup
	DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) 
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	//int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("26.248.220.2");
	addr.sin_port = htons(3490);
	addr.sin_family = AF_INET;
	
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) 
	{
		std::cout << "Error: failed connect to server.\n";
		exit(1);
	}
	std::cout << "Connected!\n";
	//char msg[256];
	//recv(Connection, msg, sizeof(msg), NULL);
	//std::cout << msg << std::endl;



	//char msg1[256];
	//while (true) {
	//	std::cin.getline(msg1, sizeof(msg1));
	//	send(Connection, msg1, sizeof(msg1), NULL);
	//	Sleep(10);
	//}
}

void Client::exchange(Field& field, Tank& tank1, Tank& tank2, std::vector<Tank>& tankAI)
{
	/*char tmp[256] = "s a ";
	send(Connection, tmp, sizeof(256), NULL);*/
	
	//int bufSize;
	//char* buf;

	std::vector<char*> tankE = tank2.sendToServer();
	//std::vector<char*> fieldE = field.sendToServer();
	char* tankE1 = convertVectorToCharArray(tankE);
	//std::cout << sizeof(tankE1)<<" " << tankE1;
	//for (int i = 0; i < tankE.size(); ++i)
	//{
	//	double bufSize = tankE.size()*sizeof(double)+1;
	//	send(Connection, convertToCharArray(bufSize), sizeof(double), NULL);
	//	send(Connection, tankE1, sizeof(double), NULL);
	//}
	double bufSize = tankE.size() * sizeof(double) + 1;
	send(Connection, convertToCharArray(bufSize), sizeof(double), NULL);
	send(Connection, tankE1, (int)bufSize, NULL);
	Sleep(5);
	//tank1
	std::vector<std::string> tankA;
	char tmpBufSize3[sizeof(double)];
	recv(Connection, tmpBufSize3, sizeof(double), NULL);
	int bufSize3 = static_cast<int>(convertBackFromCharArrayToDouble(tmpBufSize3));
	char* buf = new char[bufSize3];
	recv(Connection, buf, bufSize3, NULL);
	tankA = ConvertFromCharArrayToStringVector(buf, bufSize3);
	tank1.newTank(tankA);
	tankA.clear();

	//tank2
	char tmpBufSize2[sizeof(double)];
	recv(Connection, tmpBufSize2, sizeof(double), NULL);
	int bufSize2 = static_cast<int>(convertBackFromCharArrayToDouble(tmpBufSize2));
	buf = new char[bufSize2];
	recv(Connection, buf, bufSize2, NULL);
	tankA = ConvertFromCharArrayToStringVector(buf, bufSize2);
	tank2.newTank(tankA);
	tankA.clear();
	//field
	//std::vector<std::string> fieldE;
	//for (int i = 0; i < constants::FIELD_HEIGHT; ++i)
	//	for (int j = 0; j < constants::FIELD_WIDTH; ++j)
	//	{
	//		char buf[sizeof(int)];
	//		recv(Connection, buf, sizeof(buf), NULL);
	//		field.setField(j, i, static_cast<constants::Tiles>(convertBackFromCharArrayToInt(
	//			convertFromStringToCharArray(buf))));
	//	}
	std::vector<std::string> fieldE;
	char tmpBufSize4[sizeof(double)];
	recv(Connection, tmpBufSize4, sizeof(double), NULL);
	int bufSize4 = static_cast<int>(convertBackFromCharArrayToDouble(tmpBufSize4));
	buf = new char[bufSize4];
	recv(Connection, buf, bufSize4, NULL);
	tankA = ConvertFromCharArrayToStringVector(buf, bufSize4);
	field.newField(tankA);
	tankA.clear();

	{
		char buf[sizeof(int)];
		recv(Connection, buf, sizeof(buf), NULL);
		field.setEnemyCount(convertBackFromCharArrayToInt(
			convertFromStringToCharArray(buf)));
	}
	{
		char buf[sizeof(int)];
		recv(Connection, buf, sizeof(buf), NULL);
		field.setPlayerLives(convertBackFromCharArrayToInt(
			convertFromStringToCharArray(buf)));
	}
	{
		char buf[sizeof(int)];
		recv(Connection, buf, sizeof(buf), NULL);
		field.setEnemyToSpawn(convertBackFromCharArrayToInt(
			convertFromStringToCharArray(buf)));
	}

	//tankAI
	for (int j = 0; j < tankAI.size(); ++j)
	{
		char tmpBufSize3[sizeof(double)];
		recv(Connection, tmpBufSize3, sizeof(double), NULL);
		int bufSize3 = static_cast<int>(convertBackFromCharArrayToDouble(tmpBufSize3));
		char* buf = new char[bufSize3];
		recv(Connection, buf, bufSize3, NULL);
		tankA = ConvertFromCharArrayToStringVector(buf, bufSize3);
		tankAI[j].newTank(tankA);
		tankA.clear();
	}
}
