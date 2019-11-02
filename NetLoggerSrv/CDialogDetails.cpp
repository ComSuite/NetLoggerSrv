// CDialogDetails.cpp : implementation file
//

#include "stdafx.h"
#include "NetLoggerSrv.h"
#include "CDialogDetails.h"
#include "afxdialogex.h"


// CDialogDetails dialog

IMPLEMENT_DYNAMIC(CDialogDetails, CDialogEx)

CDialogDetails::CDialogDetails(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DETAILS, pParent)
{

}

CDialogDetails::~CDialogDetails()
{
}

void CDialogDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CDialogDetails::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_hex->CreateDialogCtrl(IDC_HEX_CONTROL, m_hWnd);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_MAIN));
	SetIcon(hIcon, FALSE);
	SetIcon(hIcon, TRUE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CDialogDetails, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDialogDetails message handlers


void CDialogDetails::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void CDialogDetails::set_data(char* data, int size)
{
	m_hds.pData = (PBYTE)data;
	m_hds.ullDataSize = size;

	m_hex->SetData(m_hds);
}

void CDialogDetails::set_bookmark(ULONGLONG start_index, ULONGLONG selection_size)
{
	m_hex->SetBookmark(start_index, selection_size);
	m_hex->Update();
}
