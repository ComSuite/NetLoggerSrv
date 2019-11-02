#include "NetLoggerClient.h"
#include <Ws2tcpip.h>
#include "cJSON.h"
#include "base64.h"

#ifdef NETWORK_LOG_ENABLE
CNetLoggerClient net_log(LOG_SERVER_IP, LOG_SERVER_PORT);
#endif

CNetLoggerClient::CNetLoggerClient(const char* log_server_ip, int port)
{
#ifdef _WINDOWS_
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	connect(log_server_ip, port);
}

CNetLoggerClient::~CNetLoggerClient()
{
	disconnect();
}

void CNetLoggerClient::connect(const char* log_server_ip, int port)
{
	struct sockaddr_in log_addr;

	log_socket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (log_socket != INVALID_SOCKET)
	{
		memset(&log_addr, 0x00, sizeof(log_addr));
		log_addr.sin_family = AF_INET;
		log_addr.sin_port = htons(port);
		inet_pton(AF_INET, log_server_ip, &log_addr.sin_addr);

		if (::connect(log_socket, (struct sockaddr *)&log_addr, sizeof(log_addr)) < 0)
		{
			
		}
	}
}

void CNetLoggerClient::disconnect()
{

	//::close(log_socket);
}

void CNetLoggerClient::addip(const sockaddr_in* serverip)
{
	if (!serverip)
		return;


}

void CNetLoggerClient::log(const char* buffer, int len)
{
	if (log_socket != INVALID_SOCKET)
	{
		send(log_socket, buffer, len, 0);
	}
}

void CNetLoggerClient::log(int ip, int port, const char* buffer, int len)
{
	cJSON *root = cJSON_CreateObject();
	if (root != NULL)
	{
		cJSON *msg = cJSON_CreateObject();
		if (msg != NULL)
		{
			cJSON_AddItemToObject(root, "msg", msg);
			cJSON_AddNumberToObject(msg, "ip", ip);
			cJSON_AddNumberToObject(msg, "port", port);
			cJSON_AddNumberToObject(msg, "len", len);
			
			size_t out_len = 0;
			unsigned char* enc = base64_encode((unsigned char*)buffer, (size_t)len, &out_len);
			if (enc != NULL)
			{
				cJSON_AddStringToObject(msg, "data", (char*)enc);
				free(enc);
			}

			char* jsonstr = cJSON_PrintUnformatted(root);
			if (jsonstr != NULL)
			{
				log(jsonstr, strlen(jsonstr));
				log("\r\n", 2);
				free(jsonstr);
			}
		}

		cJSON_Delete(root);
	}
}
