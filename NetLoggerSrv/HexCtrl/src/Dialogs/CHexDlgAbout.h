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
#include "../../res/HexCtrlRes.h"

namespace HEXCTRL {
	namespace INTERNAL {
		/********************************************
		* CHexDlgAbout class definition.			*
		********************************************/
		class CHexDlgAbout : public CDialogEx
		{
		public:
			explicit CHexDlgAbout(CWnd* pParent) : CDialogEx(IDD_HEXCTRL_ABOUT, pParent) {}
			virtual ~CHexDlgAbout() {}
		protected:
			virtual BOOL OnInitDialog() override;
			DECLARE_MESSAGE_MAP()
		};
	}
}