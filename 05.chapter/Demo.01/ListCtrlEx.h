#if !defined(AFX_LISTCTRLEX_H__8B8744E1_0D05_4889_95EE_CBC17668F2D2__INCLUDED_)
#define AFX_LISTCTRLEX_H__8B8744E1_0D05_4889_95EE_CBC17668F2D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlEx.h : header file
//

//#include <afxcoll.h>
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx window

class CHeaderCtrlEx : public CHeaderCtrl
{
// Construction
public:
	CHeaderCtrlEx();

// Attributes
protected:
    CImageList* m_pImageList; 
    CMap<int, int, int, int> m_mapImageIndex; 

// Operations
public:
    CImageList* SetImageList(CImageList* pImageList); 
    int GetItemImage(int nItem); 
    void SetItemImage(int nItem, int nImage); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHeaderCtrlEx();
    virtual void DrawItem(LPDRAWITEMSTRUCT);

	// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window

class CListCtrlEx : public CListCtrl
{
// Construction
public:
	CListCtrlEx();

// Attributes
protected:
    int m_nHighlight; 
    CHeaderCtrlEx m_header; 

public:
    enum EHighlight { HIGHLIGHT_NORMAL, HIGHLIGHT_ALLCOLUMNS, HIGHLIGHT_ROW }; 
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); 
    int SetHighlightType(EHighlight hilite); 

protected:
    void RepaintSelectedItems(); 
    int HitTestEx(CPoint& point, int* col) const; 
    CEdit* EditSubLabel(int nItem, int nCol); 

// Operations
public:
    CHeaderCtrlEx* GetHeaderCtrl(); 
    int SetItemRange(BOOL bSelect, int nFirstItem, int nLastItem); 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit window

#define IDC_IPEDIT 1

class CInPlaceEdit : public CEdit
{
// Construction
public:
	CInPlaceEdit(int iItem, int iSubItem, CString sInitText);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
    int m_iItem; 
    int m_iSubItem; 
    CString m_sInitText; 
    BOOL m_bESC; 
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEX_H__8B8744E1_0D05_4889_95EE_CBC17668F2D2__INCLUDED_)
