#include "stdafx.h"
#include "LogSrvSocket.h"

CAbstractProtocolReader::CAbstractProtocolReader()
{
	m_buf = (char*)malloc(SERVER_SOCKET_BUFFER_LENGTH);
	m_length = 0;
}

CAbstractProtocolReader::~CAbstractProtocolReader() 
{
	if (m_buf)
		free(m_buf);
}

void CAbstractProtocolReader::set_dialog(CNetUI* dialog)
{
	m_dialog = dialog;
}

void CAbstractProtocolReader::OnReceive(int nErrorCode)
{
	CString addr;
	UINT port;
	this->GetPeerName(addr, port);

	if (nErrorCode == 0)
	{
		Parse(addr.GetBuffer());
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

void CAbstractProtocolReader::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
}

//////////////////////////////////////////////////////////////////////////////////
//
CLogSrvSocket::CLogSrvSocket()
{
}

CLogSrvSocket::~CLogSrvSocket()
{
}

void CLogSrvSocket::OnAccept(int nErrorCode)
{
	m_client->ShutDown();
	m_client->Close();

	if (Accept(*m_client))
	{
		m_client->set_dialog(m_dlg);
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CLogSrvSocket::OnOutOfBandData(int nErrorCode)
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CLogSrvSocket::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CLogSrvSocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
}

void CLogSrvSocket::Execute(CNetUI* dialog, CAbstractProtocolReader* client)
{
	m_dlg = dialog;

	if (Create(m_dlg->get_port()))
	{
		m_client = client;

		if (Listen() == FALSE)
		{
			Close();
		}
	}
}
