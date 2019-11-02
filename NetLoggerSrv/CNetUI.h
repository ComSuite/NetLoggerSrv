#pragma once
class CNetUI
{
public:
	CNetUI() {};
	~CNetUI() {};

	virtual UINT get_port() { return 0; };
	virtual void log(LPTSTR ip, const char* raw, int length) {};
};

