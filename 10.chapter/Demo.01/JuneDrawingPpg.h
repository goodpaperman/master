#if !defined(AFX_JUNEDRAWINGPPG_H__C217D077_D0C6_4768_B38F_05D83796EAD2__INCLUDED_)
#define AFX_JUNEDRAWINGPPG_H__C217D077_D0C6_4768_B38F_05D83796EAD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JuneDrawingPpg.h : Declaration of the CJuneDrawingPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CJuneDrawingPropPage : See JuneDrawingPpg.cpp.cpp for implementation.

class CJuneDrawingPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CJuneDrawingPropPage)
	DECLARE_OLECREATE_EX(CJuneDrawingPropPage)

// Constructor
public:
	CJuneDrawingPropPage();

// Dialog Data
	//{{AFX_DATA(CJuneDrawingPropPage)
	enum { IDD = IDD_PROPPAGE_JUNEDRAWING };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CJuneDrawingPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNEDRAWINGPPG_H__C217D077_D0C6_4768_B38F_05D83796EAD2__INCLUDED)
