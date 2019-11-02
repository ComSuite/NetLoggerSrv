#pragma once

#include "LogSrvSocket.h"

class CDefaultReader : public CAbstractProtocolReader
{
public:
	CDefaultReader();
	virtual ~CDefaultReader();

	virtual void Parse(LPTSTR ip);
};
