#pragma once
#include "Tank.h"
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <SDKDDKVer.h>
#include <ctime>
#pragma warning(disable: 4996)



class Server
{
public:
	void server();
	void loop(Field& field1, std::vector<Bullet>& bullets);
};

