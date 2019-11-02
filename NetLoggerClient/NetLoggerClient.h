#pragma once

#include <WinSock2.h>

class CNetLoggerClient
{
public:
	CNetLoggerClient(const char* log_server_ip = NULL, int port = 0);
	virtual ~CNetLoggerClient();

	void connect(const char* log_server_ip = NULL, int port = 0);
	void disconnect();
	void addip(const sockaddr_in* serverip);
	void log(int ip, int port, const char* buffer, int len);
private:
	SOCKET log_socket;
	void log(const char* buffer, int len);
};

#define NETWORK_LOG_ENABLE

#ifdef NETWORK_LOG_ENABLE
#define LOG_SERVER_IP	"192.168.0.147" 
#define LOG_SERVER_PORT 8187
extern CNetLoggerClient net_log; 
#endif

