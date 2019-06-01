#if !defined(AFX_TWSCRIPTEDIT_H__75CF049A_E50A_4212_9670_CE59F74B0F72__INCLUDED_)
#define AFX_TWSCRIPTEDIT_H__75CF049A_E50A_4212_9670_CE59F74B0F72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TWScriptEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTWScriptEdit window

class CTWScriptEdit : public CRichEditCtrl
{
// Construction
public:
	CTWScriptEdit();

// Attributes
public:
    void Initialize(); 

// Operations
public:
    void SetCaseSensitive(BOOL bSensitive); 
    void SetChangeCase(BOOL bChange); 

    void SetSLComment(TCHAR chComment, TCHAR chComment2 = 0); 
    void SetSLComment(LPCTSTR lpszComment); 
    void SetStringQuotes(LPCTSTR lpszStrQ); 

    void AddKeywords(LPCTSTR lpszKwd); 
    void AddConstants(LPCTSTR lpszKwd); 
    void ClearKeywords(); 
    void ClearConstants(); 

    void SetKeywordColor(COLORREF clr, BOOL bBold); 
    void SetConstantColor(COLORREF clr, BOOL bBold); 
    void SetCommentColor(COLORREF clr, BOOL bBold); 
    void SetNumberColor(COLORREF clr, BOOL bBold); 
    void SetStringColor(COLORREF clr, BOOL bBold); 

    void FormatAll(); 

protected:
    BOOL IsStringQuote(TCHAR ch); 
    int IsKeyword(LPCTSTR lpszSymbol); 
    int IsConstant(LPCTSTR lpszSymbol); 

    void SetFormatRange(int nStart, int nEnd, BOOL bBold, COLORREF clr); 
    void FormatTextRange(int nStart, int nEnd); 
    void FormatTextLines(int nStart, int nEnd); 
    void ChangeCase(int nStart, int nEnd, LPCTSTR lpszStr); 

protected:
    struct SymbolColor
    {
        COLORREF clrColor; 
        BOOL bBold; 
    }; 

    enum ChangeType { ctUndo, ctUnknown, ctReplSel, ctDelete, ctBack, ctCut, ctPaste, ctMove }; 

    BOOL m_bCaseSensitive; 
    BOOL m_bChangeCase; 
    TCHAR m_chComment; 
    TCHAR m_chComment2; 
    CString m_strComment; 
    CString m_strStringQuotes; 
    CString m_strKeywords; 
    CString m_strKeywordsLower; 
    CString m_strConstants; 
    CString m_strConstantsLower; 

    SymbolColor m_icComment; 
    SymbolColor m_icNumber; 
    SymbolColor m_icString; 
    SymbolColor m_icKeyword; 
    SymbolColor m_icConstant; 

    BOOL m_bInForcedChange; 
    ChangeType m_changeType; 
    CHARRANGE m_crOldSel; 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTWScriptEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTWScriptEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTWScriptEdit)
	afx_msg void OnChange();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
    afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam); 
    afx_msg void OnProtected(NMHDR* pNMHDR, LRESULT* pResult); 
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TWSCRIPTEDIT_H__75CF049A_E50A_4212_9670_CE59F74B0F72__INCLUDED_)
