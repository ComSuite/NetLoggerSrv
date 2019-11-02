// NetLoggerTestClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include "NetLoggerClient.h"

#pragma comment(lib, "Ws2_32.lib")

#define BUF_SIZE 512

int main()
{
#ifdef NETWORK_LOG_ENABLE
	//net_log.addip(&m_cIPServer);
#endif
	char buf[BUF_SIZE];

	srand((unsigned)time(NULL));

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < BUF_SIZE; j++)
		{
			buf[j] = (BYTE)((double)rand() / (RAND_MAX + 1) * 255);
		}
#ifdef NETWORK_LOG_ENABLE
		net_log.log(100, 7000, buf, BUF_SIZE);
#endif
		Sleep(100);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
