#if !defined(AFX_MEDIUMPAGE_H__ACC05284_9798_4092_B67F_0601308D300C__INCLUDED_)
#define AFX_MEDIUMPAGE_H__ACC05284_9798_4092_B67F_0601308D300C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MediumPage.h : header file
//

#include "WizPropertyPage.h" 

/////////////////////////////////////////////////////////////////////////////
// CMediumPage dialog

class CMediumPage : public CWizPropertyPage
{
	DECLARE_DYNCREATE(CMediumPage)

// Construction
public:
	CMediumPage();
	~CMediumPage();

// Dialog Data
	//{{AFX_DATA(CMediumPage)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMediumPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMediumPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIUMPAGE_H__ACC05284_9798_4092_B67F_0601308D300C__INCLUDED_)
