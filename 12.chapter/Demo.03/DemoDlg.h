// DemoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__D862DBB5_CB80_4BB7_B027_6897FEED0A9A__INCLUDED_)
#define AFX_DEMODLG_H__D862DBB5_CB80_4BB7_B027_6897FEED0A9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCounterThread; 
class CDisplayThread; 

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
	CString m_strNumber; 
	CMutex m_mutex; 
	CCounterThread* m_pCounterThread; 
	CDisplayThread* m_pDisplayThread; 
	void AddToListBox(LPCTSTR szBuffer); 
	void OnPriorityChange(UINT nID); 

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPriorityClassChange();
	afx_msg void OnPriorityChangeCntr();
	afx_msg void OnPriorityChangeDisp();
	afx_msg void OnClose();
	afx_msg void OnPause();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__D862DBB5_CB80_4BB7_B027_6897FEED0A9A__INCLUDED_)
