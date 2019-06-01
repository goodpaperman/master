// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0DD60FB8_60FB_47AE_88F8_2D270CF992D6__INCLUDED_)
#define AFX_MAINFRM_H__0DD60FB8_60FB_47AE_88F8_2D270CF992D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_THREADCEASE (WM_USER+100)
extern volatile BOOL bThreadCeased; 

class CWorkerThread
{
public:
	HWND m_hWnd; 
public:
	CWorkerThread(HWND hWnd); 
	BOOL OutputMsg()
	{
		::MessageBox(m_hWnd, "Thread has activated.", "Thread", MB_OK); 
		return TRUE; 
	}
}; 

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnThreadStart();
	//}}AFX_MSG
	afx_msg LONG OnThreadCease(WPARAM wParam, LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0DD60FB8_60FB_47AE_88F8_2D270CF992D6__INCLUDED_)
