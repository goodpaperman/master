#if !defined(AFX_LARGEPAGE_H__4C22E533_7F53_4AAB_A26D_70C5D557A02B__INCLUDED_)
#define AFX_LARGEPAGE_H__4C22E533_7F53_4AAB_A26D_70C5D557A02B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LargePage.h : header file
//


#include "WizPropertyPage.h" 

/////////////////////////////////////////////////////////////////////////////
// CLargePage dialog

class CLargePage : public CWizPropertyPage
{
	DECLARE_DYNCREATE(CLargePage)

// Construction
public:
	CLargePage();
	~CLargePage();

// Dialog Data
	//{{AFX_DATA(CLargePage)
	enum { IDD = IDD_PROPPAGE_LARGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLargePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLargePage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LARGEPAGE_H__4C22E533_7F53_4AAB_A26D_70C5D557A02B__INCLUDED_)
