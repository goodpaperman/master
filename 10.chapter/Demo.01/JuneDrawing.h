#if !defined(AFX_JUNEDRAWING_H__CAF12588_6B95_4E1D_81BD_596F3283D3E7__INCLUDED_)
#define AFX_JUNEDRAWING_H__CAF12588_6B95_4E1D_81BD_596F3283D3E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JuneDrawing.h : main header file for JUNEDRAWING.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingApp : See JuneDrawing.cpp for implementation.

class CJuneDrawingApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNEDRAWING_H__CAF12588_6B95_4E1D_81BD_596F3283D3E7__INCLUDED)
