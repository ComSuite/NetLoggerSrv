#include "stdafx.h"
#include "DefaultReader.h"
#include "cJSON.h"
#include "base64.h"

CDefaultReader::CDefaultReader()
{
}

CDefaultReader::~CDefaultReader()
{
}

void CDefaultReader::Parse(LPTSTR ip)
{
	int ret = Receive(m_buf + m_length, SERVER_SOCKET_BUFFER_LENGTH - m_length);
	if (ret > 0)
	{
		cJSON *root = cJSON_Parse(m_buf + m_length);
		if (root != NULL)
		{
			cJSON *msg = cJSON_GetObjectItem(root, "msg");
			if (msg != NULL)
			{
				char* enc = NULL;
				char* dec = NULL;
				int len = 0;
				size_t dec_len = 0;

				if (cJSON_GetObjectItem(msg, "len") != NULL)
					len = cJSON_GetObjectItem(msg, "len")->valueint;

				if (cJSON_GetObjectItem(msg, "data") != NULL)
				{
					enc = cJSON_GetObjectItem(msg, "data")->valuestring;
					dec = (char*)base64_decode((unsigned char*)enc, strlen(enc), &dec_len);
				}

				m_dialog->log(ip, dec, dec_len);

				if (dec != NULL)
					free(dec);
			}

			cJSON_Delete(root);
		}

		m_length += ret;
		m_length -= ret;
	}
}
