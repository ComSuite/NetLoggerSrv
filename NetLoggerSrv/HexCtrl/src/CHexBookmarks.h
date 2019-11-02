/****************************************************************************************
* Copyright (C) 2018-2019, Jovibor: https://github.com/jovibor/                         *
* This is a Hex Control for MFC/Win32 applications.                                     *
* Official git repository: https://github.com/jovibor/HexCtrl/                          *
* This software is available under the "MIT License modified with�The�Commons Clause".  *
* https://github.com/jovibor/HexCtrl/blob/master/LICENSE                                *
* For more information visit the project's official repository.                         *
****************************************************************************************/
#pragma once
#include "CHexCtrl.h"
#include <vector>

namespace HEXCTRL {
	namespace INTERNAL
	{
		struct BOOKMARKSTRUCT
		{
			ULONGLONG ullOffset;
			ULONGLONG ullSize;
		};

		class CHexBookmarks
		{
		public:
			CHexBookmarks() {}
			void Attach(CHexCtrl* pHex);
			void Add(ULONGLONG ullOffset, ULONGLONG ullSize);
			void Remove(ULONGLONG ullOffset);
			void ClearAll();
			void GoNext();
			void GoPrev();
			bool HitTest(ULONGLONG ullByte);
			bool HasBookmarks()const;
		private:
			std::vector<BOOKMARKSTRUCT> m_vecBookmarks;
			CHexCtrl* m_pHex { };
			int m_iCurrent { };
		};
	}
}