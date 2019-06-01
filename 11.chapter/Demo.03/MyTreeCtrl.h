#if !defined(AFX_MYTREECTRL_H__B2E9CDB5_3E5D_4AE5_AEE1_C4733EEF5CFB__INCLUDED_)
#define AFX_MYTREECTRL_H__B2E9CDB5_3E5D_4AE5_AEE1_C4733EEF5CFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window

class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
protected:
	CFtpConnection* m_pFtpConnection; 

// Operations
public:
	void PopulateTree(CFtpConnection* pConnection = NULL, const CString& strDir = CString((LPCTSTR)NULL)); 

protected:
	void ExploreDir(const CString& strDir, HTREEITEM hParent); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeCtrl)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__B2E9CDB5_3E5D_4AE5_AEE1_C4733EEF5CFB__INCLUDED_)
