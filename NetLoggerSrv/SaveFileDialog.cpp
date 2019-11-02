#include "stdafx.h"
#include "SaveFileDialog.h"


CSaveFileDialog::CSaveFileDialog(BOOL bOpenFileDialog,
	LPCTSTR lpszDefExt,
	LPCTSTR lpszFileName,
	DWORD dwFlags,
	LPCTSTR lpszFilter,
	CWnd* pParentWnd,
	DWORD dwSize,
	BOOL bVistaStyle) : CFileDialog(bOpenFileDialog,
		lpszDefExt,
		lpszFileName,
		dwFlags,
		lpszFilter,
		pParentWnd,
		dwSize,
		bVistaStyle)
{
	
}

CSaveFileDialog::~CSaveFileDialog()
{
}

BOOL CSaveFileDialog::OnInitDialog()
{
	// call to base class
	CFileDialog::OnInitDialog();
	SetControlText(IDOK, _T("Save"));

	return TRUE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}