#pragma once

#include <afxsock.h>
#include "CNetUI.h"

#define SERVER_SOCKET_BUFFER_LENGTH	10000

class CAbstractProtocolReader : public CAsyncSocket
{
public:
	CAbstractProtocolReader();
	virtual ~CAbstractProtocolReader();
	void set_dialog(CNetUI* dialog);

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void Parse(LPTSTR ip) = 0;
protected:
	CNetUI* m_dialog;
	char* m_buf;
	int m_length;
};

class CLogSrvSocket : public CAsyncSocket
{
public:
	CLogSrvSocket();
	virtual ~CLogSrvSocket();

	virtual void OnAccept(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void Execute(CNetUI* dialog, CAbstractProtocolReader* client);
private:
	CNetUI* m_dlg;
	CAbstractProtocolReader* m_client;
};

