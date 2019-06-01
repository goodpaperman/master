#if !defined(AFX_SMALLPAGE_H__2EE614DC_96FF_4011_A877_3A94F84824DD__INCLUDED_)
#define AFX_SMALLPAGE_H__2EE614DC_96FF_4011_A877_3A94F84824DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmallPage.h : header file
//

#include "WizPropertyPage.h" 

/////////////////////////////////////////////////////////////////////////////
// CSmallPage dialog

class CSmallPage : public CWizPropertyPage
{
	DECLARE_DYNCREATE(CSmallPage)

// Construction
public:
	CSmallPage();
	~CSmallPage();

// Dialog Data
	//{{AFX_DATA(CSmallPage)
	enum { IDD = IDD_PROPPAGE_SMALL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSmallPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSmallPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLPAGE_H__2EE614DC_96FF_4011_A877_3A94F84824DD__INCLUDED_)
