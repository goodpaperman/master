#if !defined(AFX_FORMATBAR_H__FFBD812B_C961_49C4_A000_92999C114E6C__INCLUDED_)
#define AFX_FORMATBAR_H__FFBD812B_C961_49C4_A000_92999C114E6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormatBar.h : header file
//

struct CHARNMHDR : public NMHDR
{
    CHARFORMAT cf; 
    CHARNMHDR()
    {
        cf.cbSize = sizeof(CHARFORMAT); 
    }
}; 

#define FN_SETFORMAT 0x1000
#define FN_GETFORMAT 0x1001

/////////////////////////////////////////////////////////////////////////////
// CFormatBar window

class CFormatBar : public CToolBar
{
// Construction
public:
    enum { IDD = IDR_FORMATBAR }; 
	CFormatBar(UINT nID = IDD);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatBar)
	//}}AFX_VIRTUAL
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg); 

// Implementation
public:
	virtual ~CFormatBar();

protected:
    void FillFontName(CDC* pDC); 
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler); 

    CComboBox m_cmbFontName; 
    CComboBox m_cmbFontSize; 

private:
    UINT nToolbarID; 
    static int CALLBACK EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam); 

	// Generated message map functions
protected:
	//{{AFX_MSG(CFormatBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    afx_msg void OnSelectFontName(); 
    afx_msg void OnSelectFontSize(); 

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATBAR_H__FFBD812B_C961_49C4_A000_92999C114E6C__INCLUDED_)
