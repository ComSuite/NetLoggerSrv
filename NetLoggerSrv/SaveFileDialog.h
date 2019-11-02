#pragma once
#include <afxdlgs.h>
class CSaveFileDialog : public CFileDialog
{
public:
	CSaveFileDialog(BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL,
		DWORD dwSize = 0,
		BOOL bVistaStyle = TRUE);
	virtual ~CSaveFileDialog();

	BOOL OnInitDialog();
};

