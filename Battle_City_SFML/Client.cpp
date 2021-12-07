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

void Client::exchange(Field& field, Tank& tank, Tank& tank2, std::vector<Tank>& tankAI)
{
	/*char tmp[256] = "s a ";
	send(Connection, tmp, sizeof(256), NULL);*/
	
	//int bufSize;
	//char* buf;

	std::vector<char*> tankE = tank.sendToServer();
	//std::vector<char*> fieldE = field.sendToServer();
	

	for (int i = 0; i < tankE.size(); ++i)
	{
		//int bufSize = sizeof(tankE[i]);
		//send(Connection, (char*)&bufSize, sizeof(int), NULL);
		send(Connection, tankE[i], sizeof(double), NULL);
	}


	//tank1
	std::vector<std::string> tankS1;
	for (int i = 0; i < 14; ++i)
	{
		char buf[sizeof(double)];
		recv(Connection, buf, sizeof(buf), NULL);
		tankS1.push_back(buf);

	}
	
	for (int i = 14; i < 13 + 3 * convertBackFromCharArrayToDouble(convertFromStringToCharArray(tankE[static_cast<int>(constants::PacketsIndexes::TankBulletsSize)])); ++i)
	{
		char buf[sizeof(double)];
		recv(Connection, buf, sizeof(buf), NULL);
		tankS1.push_back(buf);
	}

	tank.newTank(tankS1);
	tankS1.clear();

	//tank2
	std::vector<std::string> tankS2;
	for (int i = 0; i < 14; ++i)
	{
		char buf[sizeof(double)];
		recv(Connection, buf, sizeof(buf), NULL);
		tankS2.push_back(buf);

	}

	for (int i = 14; i < 13 + 3 * convertBackFromCharArrayToDouble(convertFromStringToCharArray(tankE[static_cast<int>(constants::PacketsIndexes::TankBulletsSize)])); ++i)
	{
		char buf[sizeof(double)];
		recv(Connection, buf, sizeof(buf), NULL);
		tankS2.push_back(buf);
	}

	tank2.newTank(tankS2);
	tankS2.clear();
	//field
	//std::vector<std::string> fieldE;
	for (int i = 0; i < constants::FIELD_HEIGHT; ++i)
		for (int j = 0; j < constants::FIELD_WIDTH; ++j)
		{
			char buf[sizeof(int)];
			recv(Connection, buf, sizeof(buf), NULL);
			field.setField(j, i, static_cast<constants::Tiles>(convertBackFromCharArrayToInt(
				convertFromStringToCharArray(buf))));
		}

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
		std::vector<std::string> tankS1;
		for (int i = 0; i < 14; ++i)
		{
			char buf[sizeof(double)];
			recv(Connection, buf, sizeof(buf), NULL);
			tankS1.push_back(buf);

		}

		for (int i = 14; i < 13 + 3 * convertBackFromCharArrayToDouble(convertFromStringToCharArray(tankE[static_cast<int>(constants::PacketsIndexes::TankBulletsSize)])); ++i)
		{
			char buf[sizeof(double)];
			recv(Connection, buf, sizeof(buf), NULL);
			tankS1.push_back(buf);
		}

		tankAI[j].newTank(tankS1);
		tankS1.clear();
	}
}
