
// NetLoggerSrvDlg.h : header file
//

#pragma once

#include "LogSrvSocket.h"
#include "DefaultReader.h"
#include "CNetUI.h"
#include "CDialogDetails.h"

class CRawData
{
public:
	CRawData(const char* d, int s)
	{
		data = NULL;
		size = 0;

		if (d && s > 0)
		{
			data = (char*)malloc(s);
			if (data)
			{
				memmove(data, d, s);
				size = s;
			}
		}
	};

	virtual ~CRawData()
	{
		if (data)
			free(data);

		data = NULL;
		size = 0;
	};

	char* data;
	int size;
};
// CNetLoggerSrvDlg dialog
class CNetLoggerSrvDlg : public CDialogEx, public CNetUI
{
// Construction
public:
	CNetLoggerSrvDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETLOGGERSRV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LogList;
	virtual UINT get_port();
	virtual void log(LPTSTR ip, const char* raw, int length);
private:
	CDefaultReader* m_printer;
	CLogSrvSocket* m_srv;
	int m_last_raw;
	int m_cur_raw;
	int m_panel_height;
	CMenu m_popup;
	CDialogDetails* m_details;

	void clear_all();
	void save_binary();
	void add_rows(int count);
	void compare_rows();
	CRawData* get_data();
public:
	CButton RunSniffer;
	afx_msg void OnNMDblclkLogList(NMHDR *pNMHDR, LRESULT *pResult);
	CString MaxLength;
	CString MinLength;
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnNMRClickLogList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CString ServerPort;
};
