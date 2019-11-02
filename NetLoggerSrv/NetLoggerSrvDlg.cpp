
// NetLoggerSrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetLoggerSrv.h"
#include "NetLoggerSrvDlg.h"
#include "SaveFileDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetLoggerSrvDlg dialog
CNetLoggerSrvDlg::CNetLoggerSrvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETLOGGERSRV_DIALOG, pParent)
	, MaxLength(_T("0"))
	, MinLength(_T("0"))
	, ServerPort(_T("8187"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MAIN);

	m_last_raw = 0;
	m_cur_raw = 0;
	m_details = NULL;
}

void CNetLoggerSrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_LIST, LogList);
	DDX_Control(pDX, IDC_CHECK_RUN_SNIFFER, RunSniffer);
	DDX_Text(pDX, IDC_EDIT_MAX_SIZE, MaxLength);
	DDX_Text(pDX, IDC_EDIT_MIN_SIZE, MinLength);
	DDX_Text(pDX, IDC_EDIT_PORT, ServerPort);
}

BEGIN_MESSAGE_MAP(CNetLoggerSrvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CNetLoggerSrvDlg::OnBnClickedCancel)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LOG_LIST, &CNetLoggerSrvDlg::OnNMDblclkLogList)
	ON_WM_SETFOCUS()
	ON_WM_ACTIVATE()
	ON_NOTIFY(NM_RCLICK, IDC_LOG_LIST, &CNetLoggerSrvDlg::OnNMRClickLogList)
	ON_WM_MENUSELECT()
END_MESSAGE_MAP()


// CNetLoggerSrvDlg message handlers

BOOL CNetLoggerSrvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LogList.SetExtendedStyle(LVS_EX_AUTOAUTOARRANGE | LVS_EX_GRIDLINES | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_FULLROWSELECT);
	LogList.InsertColumn(0, L"ASCII", 0, 100);
	LogList.InsertColumn(0, L"Hex", 0, 400);
	LogList.InsertColumn(0, L"Length", 0, 100);
	LogList.InsertColumn(0, L"IP", 0, 200);

	RECT rect;
	LogList.GetClientRect(&rect);
	LogList.SetColumnWidth(2, (rect.right - rect.left - 300) / 2);
	LogList.SetColumnWidth(3, (rect.right - rect.left - 300) / 2);

	add_rows(10000);

	RECT rect_m;
	LogList.GetWindowRect(&rect);
	GetWindowRect(&rect_m);
	m_panel_height = rect_m.bottom - rect.bottom;

	RunSniffer.SetCheck(TRUE);
	
	if (m_details == NULL)
	{
		m_details = new CDialogDetails(this);
		m_details->Create(IDD_DIALOG_DETAILS, this);
	}

	m_popup.LoadMenu(IDR_MENU_MAIN_POPUP);

	m_printer = new CDefaultReader();
	m_srv = new CLogSrvSocket();
	m_srv->Execute(this, m_printer);

	UpdateData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetLoggerSrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetLoggerSrvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetLoggerSrvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNetLoggerSrvDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CNetLoggerSrvDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (LogList)
	{
		RECT rect;
		LogList.GetWindowRect(&rect);
		ScreenToClient(&rect);
		LogList.MoveWindow(rect.left, rect.top, cx - rect.left * 2, cy - rect.top - m_panel_height);
	}
}

UINT CNetLoggerSrvDlg::get_port()
{
	return _ttoi(ServerPort);
}

void CNetLoggerSrvDlg::add_rows(int count)
{
	LogList.SetRedraw(FALSE);

	for (int i = 0; i < count; i++)
	{
		LogList.InsertItem(LVIF_TEXT, m_last_raw, _T(""), 0, 0, 0, 0);
		m_last_raw++;
	}

	LogList.SetRedraw(TRUE);
}

void CNetLoggerSrvDlg::log(LPTSTR ip, const char* raw, int length)
{
	if (!RunSniffer.GetCheck() || !raw || length == 0)
		return;

	LogList.SetRedraw(FALSE);

	CString hex = _T("");
	CString ascii = _T("");
	CString s = _T("");

	s.Format(_T("%d"), length);

	LogList.SetItemText(m_cur_raw, 0, ip);
	LogList.SetItemText(m_cur_raw, 1, s);

	for (int i = 0; i < length; i++)
	{
		s.Format(_T("%02X "), (BYTE)raw[i]);
		hex += s;
		if (isalnum((BYTE)raw[i]) || ispunct((BYTE)raw[i]))
			s.Format(_T("%C"), (BYTE)raw[i]);
		else
			s = ".";
		ascii += s;
	}

	LogList.SetItemText(m_cur_raw, 2, hex);
	LogList.SetItemText(m_cur_raw, 3, ascii);

	CRawData* data = new CRawData(raw, length);
	LogList.SetItemData(m_cur_raw, (DWORD_PTR)data);

	LogList.SetRedraw(TRUE);

	m_cur_raw++;
	if (m_cur_raw >= m_last_raw)
		add_rows(10000);
}

void CNetLoggerSrvDlg::OnClose()
{
	clear_all();

	delete m_printer;
	delete m_srv;

	CDialogEx::OnClose();
}

CRawData* CNetLoggerSrvDlg::get_data()
{
	CRawData* data = NULL;
	POSITION pos = LogList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int n = LogList.GetNextSelectedItem(pos);
		data = (CRawData*)LogList.GetItemData(n);
	}

	return data;
}

void CNetLoggerSrvDlg::OnNMDblclkLogList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	m_details->ShowWindow(SW_SHOW);
	CRawData* data = get_data();
	if (data)
		m_details->set_data(data->data, data->size);

	*pResult = 0;
}

void CNetLoggerSrvDlg::OnSetFocus(CWnd* pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
}


void CNetLoggerSrvDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	__super::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}

void CNetLoggerSrvDlg::OnNMRClickLogList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	POINT point;
	point = pNMItemActivate->ptAction;
	LogList.ClientToScreen(&point);

	CMenu* popup = m_popup.GetSubMenu(0);
	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}

BOOL CNetLoggerSrvDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case ID_SAVE_COMPARE:
		compare_rows();
		break;
	case ID_SAVE_SAVE:
		save_binary();
		break;
	case ID_SAVE_CLEAR:
		clear_all();
		break;
	}

	return CWnd::OnCommand(wParam, lParam);
}

void CNetLoggerSrvDlg::compare_rows()
{
	if (LogList.GetSelectedCount() != 2)
	{
		AfxMessageBox(_T("You can compare only two rows"), MB_OK, 0);
		return;
	}

	m_details->ShowWindow(SW_SHOW);
	CRawData* data = NULL;
	CRawData* comp = NULL;
	POSITION pos = LogList.GetFirstSelectedItemPosition();

	int n = LogList.GetNextSelectedItem(pos);
	data = (CRawData*)LogList.GetItemData(n);
	n = LogList.GetNextSelectedItem(pos);
	comp = (CRawData*)LogList.GetItemData(n);

	if (data)
	{
		m_details->set_data(data->data, data->size);

		if (comp)
		{
			LONGLONG start = -1;
			LONGLONG count = 0;
			LONGLONG i = 0;
			while (i < data->size && i < comp->size)
			{
				if (data->data[i] != comp->data[i])
				{
					if (start < 0)
						start = i;

					count++;
				} 
				else
				{
					if (start >= 0)
						m_details->set_bookmark(start, count);

					start = -1;
					count = 0;
				}

				i++;
			}

			if (start >= 0)
				m_details->set_bookmark(start, count);
		}
	}

	m_details->SetActiveWindow();
}

void CNetLoggerSrvDlg::save_binary()
{
	LPTSTR fileTypes = _T("Binary files (*.bin)|*.bin|All files|*.*||");
	CFileDialog dlg(FALSE, _T("bin"), _T("*.bin"), OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_EXPLORER, fileTypes);
	dlg.m_ofn.lpstrTitle = _T("");
	//dlg.SetControlText(IDOK, _T("Save"));
	
	if (dlg.DoModal() == IDOK)
	{
		CString path = dlg.GetPathName();
		CFile file;
		CFileException ex;

		if (file.Open(path, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex))
		{
			CRawData* data = NULL;
			POSITION pos = LogList.GetFirstSelectedItemPosition();
			while (pos != NULL)
			{
				int n = LogList.GetNextSelectedItem(pos);
				data = (CRawData*)LogList.GetItemData(n);
				if (data)
				{
					file.Write(data->data, data->size);
				}
			}

			file.Close();
		}
	}
}

void CNetLoggerSrvDlg::clear_all()
{
	for (int i = 0; i < m_cur_raw; i++)
	{
		CRawData* data = (CRawData*)LogList.GetItemData(i);
		if (data)
			delete data;

		LogList.SetItemData(i, NULL);

		CHeaderCtrl* hdr = LogList.GetHeaderCtrl();
		for (int j = 0; j < hdr->GetItemCount(); j++)
			LogList.SetItemText(i, j, _T(""));
	}

	m_cur_raw = 0;
}

void CNetLoggerSrvDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	__super::OnMenuSelect(nItemID, nFlags, hSysMenu);
}
