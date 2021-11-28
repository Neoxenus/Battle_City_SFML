#pragma once
#pragma comment(lib, "ws2_32.lib")
#include "Tank.h"
#include "Convert.h"
#include <winsock2.h>
#include <iostream>
#pragma warning(disable: 4996)


class Client
{
	WSAData wsaData;
	WORD DLLVersion;
	SOCKADDR_IN addr;
	SOCKET Connection;
public:
	void client();
	void exchange(Field& field, Tank& tank);
	

};

