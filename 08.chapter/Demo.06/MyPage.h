#if !defined(AFX_MYPAGE_H__6F96E599_37AF_4BF9_86B7_E899D3BB32BA__INCLUDED_)
#define AFX_MYPAGE_H__6F96E599_37AF_4BF9_86B7_E899D3BB32BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyPage dialog

class CMyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMyPage)

// Construction
public:
	CMyPage();
	~CMyPage();

// Dialog Data
	//{{AFX_DATA(CMyPage)
	enum { IDD = IDD_PROPPAGE_1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAGE_H__6F96E599_37AF_4BF9_86B7_E899D3BB32BA__INCLUDED_)
