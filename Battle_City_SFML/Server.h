#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <SDKDDKVer.h>
#pragma warning(disable: 4996)

class Server
{
public:
	void server();
};

