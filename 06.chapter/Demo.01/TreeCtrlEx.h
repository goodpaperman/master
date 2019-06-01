#if !defined(AFX_TREECTRLEX_H__AF9D23E2_B2FE_4FE5_847E_D9A16B5E18FF__INCLUDED_)
#define AFX_TREECTRLEX_H__AF9D23E2_B2FE_4FE5_847E_D9A16B5E18FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlEx.h : header file
//

#include <AfxTempl.h> 

#ifndef ID_MOVEASCHILD
#define ID_MOVEASCHILD 32857
#endif 

#ifndef ID_MOVEASSIBLING
#define ID_MOVEASSIBLING 32858
#endif

#ifndef ID_COPYASCHILD
#define ID_COPYASCHILD 32859
#endif

#ifndef ID_COPYASSIBLING
#define ID_COPYASSIBLING 32860
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx window

class CTreeCtrlEx : public CTreeCtrl
{
// Construction
public:
	CTreeCtrlEx();

// Attributes
public:
    CImageList m_image; 
    CImageList m_imageState; 

    enum CheckState{ NOSTATE = 0, UNCHECKED, CHECKED, CHILD_CHECKED, FULL_CHECKED }; 
    enum CheckType{ CHECK, UNCHECK, TOGGLE, REFRESH }; 

// Operations
public:
    void ExpandBranchCompletely(HTREEITEM hti, UINT nFlag); 
    void ExpandAll(UINT nFlag); 

    HTREEITEM GetLastItem(HTREEITEM hItem); 
    HTREEITEM GetNextItem(HTREEITEM hItem); 
    HTREEITEM GetPrevItem(HTREEITEM hItem); 
    HTREEITEM FindItem(CString& str, BOOL bCaseSensitive = FALSE, 
        BOOL bDownDir = TRUE, BOOL bWholeWord = FALSE, HTREEITEM hItem = NULL); 
    HTREEITEM FindItemData(DWORD lparam, BOOL bDownDir = TRUE, HTREEITEM hItem = NULL); 
    HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST); 
    HTREEITEM CopyBranch(HTREEITEM htiBrach, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST); 

    void ClearSelection(); 
    BOOL SelectItems(HTREEITEM hItemFrom, HTREEITEM hItemTo); 
    HTREEITEM GetFirstSelectedItem(); 
    HTREEITEM GetNextSelectedItem(HTREEITEM hItem); 
    HTREEITEM GetPrevSelectedItem(HTREEITEM hItem); 

    BOOL IsItemChecked(HTREEITEM hItem); 
    HTREEITEM GetFirstCheckedItem(); 
    HTREEITEM GetNextCheckedItem(HTREEITEM hItem); 
    HTREEITEM GetPrevCheckedItem(HTREEITEM hItem); 
    BOOL SetCheck(HTREEITEM hItem, CheckType nCheck); 

    void SetItemFont(HTREEITEM hItem, LOGFONT& logfont); 
    void SetItemBold(HTREEITEM hItem, BOOL bBold); 
    void SetItemColor(HTREEITEM hItem, COLORREF color); 
    BOOL GetItemFont(HTREEITEM hItem, LOGFONT* plogfont); 
    BOOL GetItemBold(HTREEITEM hItem); 
    COLORREF GetItemColor(HTREEITEM hItem); 

    BOOL SetBkImage(UINT nIDResource); 
    BOOL SetBkImage(LPCTSTR lpszResourceName); 

    void Serialize(CArchive& ar); 

protected:
    virtual BOOL IsFindValid(HTREEITEM); 
    virtual void OnItemCopied(HTREEITEM, HTREEITEM); 
    HMENU GetRDragMenu(); 
    int GetIndentLevel(HTREEITEM hItem); 

    CImageList* m_pDragImage; 
    BOOL m_bLDragging; 
    HTREEITEM m_hitemDrag, m_hitemDrop; 

    UINT m_nTimerID, m_timerticks; 

    //CImageList m_pDragImage; 
    BOOL m_bRDragging; 
    BOOL m_bRDragCanceled; 
    //HTREEITEM m_hitemDrag, m_hitemDrop; 

    HTREEITEM m_hItemFirstSel; 

    struct Color_Font
    {
        COLORREF color; 
        LOGFONT logfont; 
    }; 
    CMap<void*, void*, Color_Font, Color_Font&> m_mapColorFont; 

    CPalette m_pal; 
    CBitmap m_bitmap; 
    int m_cxBitmap, m_cyBitmap; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlEx)
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBeginRDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
    afx_msg void OnMoveAsChild(); 
    afx_msg void OnMoveAsSibling(); 
    afx_msg void OnCopyAsChild(); 
    afx_msg void OnCopyAsSibling(); 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLEX_H__AF9D23E2_B2FE_4FE5_847E_D9A16B5E18FF__INCLUDED_)
