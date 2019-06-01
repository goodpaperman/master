#if !defined(AFX_MYSHEET_H__85AF81EF_53FF_49B8_BECE_23960B70D8FD__INCLUDED_)
#define AFX_MYSHEET_H__85AF81EF_53FF_49B8_BECE_23960B70D8FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySheet.h : header file
//

#include "MyPage.h" 
#define WM_RESIZEPAGE (WM_USER + 250) 

/////////////////////////////////////////////////////////////////////////////
// CMySheet

class CMySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMySheet)

// Construction
public:
	CMySheet(CWnd* pParentWnd);

protected:
    void Init(); 

// Attributes
public:
    CMyPage m_page1, m_page2; 

protected:
    CRect m_rectPage; 

// Operations
public:
    void Resize(); 
    void AutoArrangeButtons(); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySheet)
	public:
	virtual BOOL OnInitDialog();
    virtual void PostNcDestroy(); 
    virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult); 
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
    afx_msg LRESULT OnResizePage(WPARAM wParam, LPARAM lParam); 
    afx_msg void OnApplyNow(); 
    afx_msg void OnSize(UINT nType, int cx, int cy); 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSHEET_H__85AF81EF_53FF_49B8_BECE_23960B70D8FD__INCLUDED_)
