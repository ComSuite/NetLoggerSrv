#pragma once

#include "HexCtrl/HexCtrl.h"

using namespace HEXCTRL;

class CDialogDetails : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDetails)

public:
	CDialogDetails(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogDetails();

	void set_data(char* data, int size);
	void set_bookmark(ULONGLONG start_index, ULONGLONG selection_size);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAILS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	IHexCtrlPtr m_hex{CreateHexCtrl()};
	HEXDATASTRUCT m_hds;

	virtual BOOL OnInitDialog();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

