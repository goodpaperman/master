#if !defined(AFX_WIZPROPERTYSHEET_H__4FED2570_3A82_4CBB_B057_07AC1F1A7F14__INCLUDED_)
#define AFX_WIZPROPERTYSHEET_H__4FED2570_3A82_4CBB_B057_07AC1F1A7F14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizPropertySheet.h : header file
//

#include "WizPropertyPage.h" 

/////////////////////////////////////////////////////////////////////////////
// CWizPropertySheet

class CWizPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizPropertySheet)

// Construction
public:
	CWizPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

    void EnablePages(BOOL bEnable, int nStart, int nEnd = -1); 
    void AddPage(CWizPropertyPage* pPage); 

protected:
    void Init(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZPROPERTYSHEET_H__4FED2570_3A82_4CBB_B057_07AC1F1A7F14__INCLUDED_)
