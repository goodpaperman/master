// DemoView.h : interface of the CDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOVIEW_H__C46F1C97_9C10_4212_800B_E4B9FB299979__INCLUDED_)
#define AFX_DEMOVIEW_H__C46F1C97_9C10_4212_800B_E4B9FB299979__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDemoCntrItem;

DWORD CALLBACK EditStreamCallBack2 (DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb); 

class CDemoView : public CRichEditView
{
protected: // create from serialization only
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

// Attributes
public:
	CDemoDoc* GetDocument();

// Operations
public:
    void SetSelectionProtected(); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL
    void OnGetCharFormat(NMHDR* pNMHDR, LRESULT* pRes); 
    void OnSetCharFormat(NMHDR* pNMHDR, LRESULT* pRes); 
    void OnBarReturn(NMHDR*, LRESULT*); 

// Implementation
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoView)
	afx_msg void OnDestroy();
	afx_msg void OnColorPick();
    //afx_msg void OnCharBold();
    //afx_msg void OnUpdateCharBold(CCmdUI* pCmdUI);
    //afx_msg void OnCharItalic();
    //afx_msg void OnUpdateCharItalic(CCmdUI* pCmdUI);
    //afx_msg void OnCharUnderline();
    //afx_msg void OnUpdateCharUnderline(CCmdUI* pCmdUI);
    //afx_msg void OnParaCenter();
    //afx_msg void OnUpdateParaCenter(CCmdUI* pCmdUI);
    //afx_msg void OnParaLeft();
    //afx_msg void OnUpdateParaLeft(CCmdUI* pCmdUI);
    //afx_msg void OnParaRight();
    //afx_msg void OnUpdateParaRight(CCmdUI* pCmdUI);
    //afx_msg void OnInsertBullet();
	//}}AFX_MSG
    afx_msg void OnProtected(NMHDR* pNMHDR, LRESULT* pResult); 
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOVIEW_H__C46F1C97_9C10_4212_800B_E4B9FB299979__INCLUDED_)
