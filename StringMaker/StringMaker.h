
// StringMaker.h : main header file for the TextMaker application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CStringMakerApp:
// See StringMaker.cpp for the implementation of this class
//

class CStringMakerApp : public CWinApp
{
public:
	CStringMakerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CStringMakerApp theApp;
