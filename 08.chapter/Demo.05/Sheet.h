#if !defined(AFX_SHEET_H__7A69F363_EE8A_4E0B_B945_55C1FB439C1B__INCLUDED_)
#define AFX_SHEET_H__7A69F363_EE8A_4E0B_B945_55C1FB439C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSheet

class CSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheet)

// Construction
public:
    CSheet(); 

// Attributes
public:
    CPropertyPage m_page[4]; 
    CMenu m_menu; 
    CDC m_dc; 
    CBitmap m_bmp; 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheet)
	afx_msg void OnPaint();
	//}}AFX_MSG
    afx_msg void OnDisplayPage(int nPage); 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHEET_H__7A69F363_EE8A_4E0B_B945_55C1FB439C1B__INCLUDED_)
