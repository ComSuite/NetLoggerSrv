/****************************************************************************************
* Copyright (C) 2018-2019, Jovibor: https://github.com/jovibor/                         *
* This is a Hex Control for MFC/Win32 applications.                                     *
* Official git repository: https://github.com/jovibor/HexCtrl/                          *
* This software is available under the "MIT License modified with�The�Commons Clause".  *
* https://github.com/jovibor/HexCtrl/blob/master/LICENSE                                *
* For more information visit the project's official repository.                         *
****************************************************************************************/
#pragma once
#include <afxcontrolbars.h>  //Standard MFC's controls header.
#include "../CHexCtrl.h"
#include "../../res/HexCtrlRes.h"

namespace HEXCTRL {
	namespace INTERNAL {
		class CHexDlgOperations : public CDialogEx
		{
		public:
			explicit CHexDlgOperations() : CDialogEx(IDD_HEXCTRL_OPERATIONS) {}
			virtual ~CHexDlgOperations() {}
			BOOL Create(UINT nIDTemplate, CHexCtrl* pHexCtrl);
		protected:
			virtual void DoDataExchange(CDataExchange* pDX);
			virtual BOOL OnInitDialog();
			afx_msg void OnBnClickedOk();
			DECLARE_MESSAGE_MAP()
		private:
			CHexCtrl* GetHexCtrl()const;
		private:
			CHexCtrl* m_pHexCtrl { };
			virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
		};
	}
}