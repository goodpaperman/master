// TWScriptEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "TWScriptEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTWScriptEdit

CTWScriptEdit::CTWScriptEdit()
{
    m_chComment = 1; 
    m_bCaseSensitive = FALSE; 
    m_bChangeCase = TRUE; 
    
    SetStringQuotes(_T("\"")); 
    SetKeywordColor(RGB(0, 0, 255), FALSE); 
    SetConstantColor(RGB(0, 0, 0), TRUE); 
    SetCommentColor(RGB(0, 128, 0), FALSE); 
    SetNumberColor(RGB(255, 0, 255), FALSE); 
    SetStringColor(RGB(255, 0, 255), FALSE); 

    m_bInForcedChange = FALSE; 
    m_changeType = ctUndo; 
    m_crOldSel.cpMin = m_crOldSel.cpMax = 0; 
}

CTWScriptEdit::~CTWScriptEdit()
{
}


BEGIN_MESSAGE_MAP(CTWScriptEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CTWScriptEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CHAR()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_SETTEXT, OnSetText) 
    ON_NOTIFY_REFLECT(EN_PROTECTED, OnProtected) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTWScriptEdit message handlers

void CTWScriptEdit::Initialize()
{
    PARAFORMAT pf; 
    pf.cbSize = sizeof(PARAFORMAT); 
    pf.dwMask = PFM_TABSTOPS; 
    pf.cTabCount = MAX_TAB_STOPS; 
    for(int itab = 0; itab < pf.cTabCount; itab++)
        pf.rgxTabs[itab] = (itab + 1) * 1440 / 5; 

    SetParaFormat(pf); 

    CHARFORMAT cfDefault; 
    cfDefault.cbSize = sizeof(cfDefault); 
    cfDefault.dwEffects = CFE_PROTECTED; 
    cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED; 
    cfDefault.yHeight = 200; 
    cfDefault.bCharSet = 0xEE; 
    strcpy(cfDefault.szFaceName, _T("Courier New")); 

    SetDefaultCharFormat(cfDefault); 
    SetEventMask(ENM_CHANGE | ENM_SELCHANGE | ENM_PROTECTED); 
}

void CTWScriptEdit::SetSLComment(TCHAR chComment, TCHAR chComment2)
{
    m_chComment = chComment; 
    m_chComment2 = chComment2; 
}

void CTWScriptEdit::SetSLComment(LPCTSTR lpszComment)
{
    m_strComment = lpszComment; 
}

void CTWScriptEdit::AddKeywords(LPCTSTR lpszKwd)
{
    CString str; 
    str.Format(" %s ", lpszKwd); 
    m_strKeywords = m_strKeywords + str; 
    m_strKeywordsLower = m_strKeywords; 
    if(!m_bCaseSensitive)
        m_strKeywordsLower.MakeLower(); 
}

void CTWScriptEdit::ClearKeywords()
{
    m_strKeywords.Empty(); 
    m_strKeywordsLower.Empty(); 
}

void CTWScriptEdit::AddConstants(LPCTSTR lpszConst)
{
    CString str; 
    str.Format(" %s ", lpszConst); 
    m_strConstants = m_strConstants + str; 
    m_strConstantsLower = m_strConstants; 
    if(!m_bCaseSensitive)
        m_strConstantsLower.MakeLower(); 
}

void CTWScriptEdit::ClearConstants()
{
    m_strConstants.Empty(); 
    m_strConstantsLower.Empty(); 
}

void CTWScriptEdit::SetCaseSensitive(BOOL bSensitive)
{
    m_bCaseSensitive = bSensitive; 
}

void CTWScriptEdit::SetChangeCase(BOOL bChange)
{
    m_bChangeCase = bChange; 
}

void CTWScriptEdit::SetStringQuotes(LPCTSTR lpszStrQ)
{
    m_strStringQuotes = lpszStrQ; 
}

void CTWScriptEdit::SetKeywordColor(COLORREF clr, BOOL bBold)
{
    m_icKeyword.clrColor = clr; 
    m_icKeyword.bBold = bBold; 
}

void CTWScriptEdit::SetConstantColor(COLORREF clr, BOOL bBold)
{
    m_icConstant.clrColor = clr; 
    m_icConstant.bBold = bBold; 
}

void CTWScriptEdit::SetCommentColor(COLORREF clr, BOOL bBold)
{
    m_icComment.clrColor = clr; 
    m_icComment.bBold = bBold; 
}

void CTWScriptEdit::SetNumberColor(COLORREF clr, BOOL bBold)
{
    m_icNumber.clrColor = clr; 
    m_icNumber.bBold = bBold; 
}

void CTWScriptEdit::SetStringColor(COLORREF clr, BOOL bBold)
{
    m_icString.clrColor = clr; 
    m_icString.bBold = bBold; 
}

int CTWScriptEdit::IsKeyword(LPCTSTR lpszSymbol)
{
    CString strSymbol; 
    strSymbol.Format(" %s ", lpszSymbol); 
    if(!m_bCaseSensitive)
        strSymbol.MakeLower(); 
    return m_strKeywordsLower.Find(strSymbol); 
}

int CTWScriptEdit::IsConstant(LPCTSTR lpszSymbol)
{
    CString strSymbol; 
    strSymbol.Format(" %s ", lpszSymbol); 
    if(!m_bCaseSensitive)
        strSymbol.MakeLower(); 
    return m_strConstantsLower.Find(strSymbol); 
}

BOOL CTWScriptEdit::IsStringQuote(TCHAR ch)
{
    return (m_strStringQuotes.Find(ch) >= 0); 
}

void CTWScriptEdit::SetFormatRange(int nStart, int nEnd, BOOL bBold, COLORREF clr)
{
    if(nStart > nEnd)
        return; 

    SetSel(nStart, nEnd); 
    DWORD dwEffects = bBold ? CFE_BOLD : 0; 
    CHARFORMAT cfm; 
    cfm.cbSize = sizeof(cfm); 
    GetSelectionCharFormat(cfm); 

    if((cfm.dwMask & CFM_COLOR) && cfm.crTextColor == clr && 
        (cfm.dwMask & CFM_BOLD) && (cfm.dwEffects & CFE_BOLD) == dwEffects)
        return; 

    cfm.dwEffects = dwEffects; 
    cfm.crTextColor = clr; 
    cfm.dwMask = CFM_BOLD | CFM_COLOR; 
    SetSelectionCharFormat(cfm); 
}

void CTWScriptEdit::ChangeCase(int nStart, int nEnd, LPCTSTR lpsz)
{
    if(nEnd - nStart != int(_tcslen(lpsz)))
        return; 

    if(!m_bCaseSensitive && m_bChangeCase)
    {
        SetSel(nStart, nEnd); 
        ReplaceSel(lpsz); 
    }
}

void CTWScriptEdit::FormatTextRange(int nStart, int nEnd)
{
    if(nStart >= nEnd)
        return; 

    m_bInForcedChange = TRUE; 
    CHARRANGE crOldSel; 
    GetSel(crOldSel); 
    LockWindowUpdate(); 
    HideSelection(TRUE, FALSE); 

    TCHAR* pBuffer = NULL; 
    try
    {
        SetSel(nStart, nEnd); 
        pBuffer = new TCHAR[nEnd - nStart + 1]; 
        long nLen = GetSelText(pBuffer); 
        ASSERT(nLen <= nEnd - nStart); 
        pBuffer[nLen] = 0; 

        TCHAR* pStart, *pPtr; 
        pStart = pPtr = pBuffer; 
        TCHAR* pSymbolStart = NULL; 
        SymbolColor ic; 

        while(*pPtr != 0)
        {
            TCHAR ch = *pPtr; 
            if(ch == m_chComment && (m_chComment2 == 0 || pPtr[1] == m_chComment2))
            {
                pSymbolStart = pPtr; 
                do
                {
                    ch = *(++pPtr); 
                }while(ch != 0 && ch != '\r'); 

                ic = m_icComment; 
            }
            else if(IsStringQuote(ch))
            {
                pSymbolStart = pPtr; 
                TCHAR ch1 = ch; 
                do 
                {
                    ch = *(++pPtr); 
                }while(ch != 0 && ch != ch1 && ch != '\r'); 

                if(ch == ch1)
                    pPtr++; 

                ic = m_icString; 
            }
            else if(_istdigit(ch))
            {
                pSymbolStart = pPtr; 
                _tcstod(pSymbolStart, &pPtr); 
                ic = m_icNumber; 
            }
            else if(_istalpha(ch) || ch == '_')
            {
                pSymbolStart = pPtr; 
                do
                {
                    ch = *(++pPtr); 
                }while(_istalnum(ch) || ch == '_'); 

                *pPtr = 0; 
                int nPos = IsKeyword(pSymbolStart); 
                if(nPos >= 0)
                {
                    ChangeCase(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, 
                        m_strKeywords.Mid(nPos+1, pPtr - pSymbolStart)); 

                    if(_tcsicmp(m_strComment, pSymbolStart) == 0)
                    {
                        *pPtr = ch; 
                        *pSymbolStart = m_chComment; 
                        if(pSymbolStart[1] != 0 && m_chComment2 != 0)
                            pSymbolStart[1] = m_chComment2; 

                        pPtr = pSymbolStart; 
                        pSymbolStart = NULL; 
                        continue; 
                    }

                    ic = m_icKeyword; 
                }
                else
                {
                    nPos = IsConstant(pSymbolStart); 
                    if(nPos >= 0)
                    {
                        ChangeCase(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, 
                            m_strConstants.Mid(nPos+1, pPtr - pSymbolStart)); 

                        ic = m_icConstant; 
                    }
                    else 
                    {
                        pSymbolStart = NULL; 
                    }
                }

                *pPtr = ch; 
            }
            else 
            {
                pPtr++; 
            }

            if(pSymbolStart != NULL)
            {
                ASSERT(pSymbolStart < pPtr); 
                SetFormatRange(nStart + pStart - pBuffer, nStart + pSymbolStart - pBuffer, FALSE, RGB(0, 0, 0)); 
                SetFormatRange(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, ic.bBold, ic.clrColor); 
                pStart = pPtr; 
                pSymbolStart = 0; 
            }
            else if(*pPtr == 0)
            {
                SetFormatRange(nStart + pStart - pBuffer, nStart + pPtr - pBuffer, FALSE, RGB(0, 0, 0)); 
            }
        }
    }
    catch(...)
    {
    }

    delete [] pBuffer; 
    SetSel(crOldSel); 

    HideSelection(FALSE, FALSE); 
    UnlockWindowUpdate(); 
    m_bInForcedChange = FALSE; 
}

void CTWScriptEdit::FormatTextLines(int nLineStart, int nLineEnd)
{
    long nStart = LineIndex(LineFromChar(nLineStart)); 
    long nEnd = LineIndex(LineFromChar(nLineEnd)); 
    nEnd += LineLength(nLineEnd); 

    FormatTextRange(nStart, nEnd); 
}

void CTWScriptEdit::FormatAll()
{
    FormatTextRange(0, GetTextLength()); 
}



void CTWScriptEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == '\t' && GetKeyState(VK_CONTROL) >= 0)
    {
        ReplaceSel("\t"); 
        return; 
    }

	CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
}

UINT CTWScriptEdit::OnGetDlgCode() 
{
	// TODO: Add your message handler code here and/or call default
	
	UINT uCode = CRichEditCtrl::OnGetDlgCode();
    uCode = DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTMESSAGE | DLGC_WANTTAB; 
    return uCode; 
}

void CTWScriptEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CRichEditCtrl::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_bInForcedChange)
        return; 

    CHARRANGE crCurSel; 
    GetSel(crCurSel); 

    if(m_changeType == ctMove && crCurSel.cpMin == crCurSel.cpMax)
        m_changeType = ctPaste; 

    switch(m_changeType)
    {
        case ctReplSel:
        case ctPaste:
            FormatTextLines(m_crOldSel.cpMin, m_crOldSel.cpMax); 
            break; 
        case ctDelete:
        case ctBack:
        case ctCut:
            FormatTextLines(crCurSel.cpMin, crCurSel.cpMax); 
            break; 
        case ctUndo:
            FormatTextLines(crCurSel.cpMin, crCurSel.cpMax); 
            break; 
        case ctMove:
            FormatTextLines(crCurSel.cpMin, crCurSel.cpMax); 
            if(crCurSel.cpMin > m_crOldSel.cpMin)
                FormatTextLines(m_crOldSel.cpMin, m_crOldSel.cpMin); 
            else 
                
                (m_crOldSel.cpMax, m_crOldSel.cpMax); 
            break; 
        default:
            FormatAll(); 
            break; 
    }

    m_changeType = ctUndo; 
}

LRESULT CTWScriptEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
    LRESULT res = Default(); 
    FormatAll(); 
    return res; 
}

void CTWScriptEdit::OnProtected(NMHDR* pNMHDR, LRESULT* pResult)
{
    ENPROTECTED* pEP = (ENPROTECTED*)pNMHDR; 
    switch(pEP->msg)
    {
    case WM_KEYDOWN:
        switch(pEP->wParam)
        {
        case VK_DELETE:
            m_changeType = ctDelete; 
            break; 
        case VK_BACK:
            m_changeType = ctBack; 
            break; 
        default:
            m_changeType = ctUnknown; 
            break; 
        }
        break; 
    case EM_REPLACESEL:
    case WM_CHAR:
        m_changeType = ctReplSel; 
        break; 
    case WM_PASTE:
        m_changeType = (m_changeType == ctCut) ? ctMove : ctPaste; 
        break; 
    case WM_CUT:
        m_changeType = ctCut; 
        break; 
    default:
        m_changeType = ctUnknown; 
        break; 
    }

    if(pEP->msg != EM_SETCHARFORMAT && m_changeType != ctMove)
        m_crOldSel = pEP->chrg; 

    *pResult = FALSE; 
}