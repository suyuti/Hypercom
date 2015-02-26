// MonitorMFC.h : main header file for the MonitorMFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMonitorMFCApp:
// See MonitorMFC.cpp for the implementation of this class
//

class CMonitorMFCApp : public CWinApp
{
public:
	CMonitorMFCApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMonitorMFCApp theApp;