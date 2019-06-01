// FormatBar.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "FormatBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const static int nFontSizes[] = 
{ 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72}; 

/////////////////////////////////////////////////////////////////////////////
// CFormatBar

CFormatBar::CFormatBar(UINT nID)
{
    nToolbarID = nID; 
}

CFormatBar::~CFormatBar()
{
}


BEGIN_MESSAGE_MAP(CFormatBar, CToolBar)
	//{{AFX_MSG_MAP(CFormatBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_CBN_SELENDOK(IDC_FONTNAME, OnSelectFontName)
    ON_CBN_SELENDOK(IDC_FONTSIZE, OnSelectFontSize) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatBar message handlers

int CFormatBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if(!LoadToolBar(nToolbarID))
        return -1; 

    CClientDC dc(this); 
    HGDIOBJ hFont = GetStockObject(DEFAULT_GUI_FONT); 
    CFont font; 
    font.Attach(hFont); 
    dc.SelectObject(&font); 
    TEXTMETRIC tm; 
    dc.GetTextMetrics(&tm); 
    int cxChar = tm.tmAveCharWidth; 
    int cyChar = tm.tmHeight + tm.tmExternalLeading; 

    CRect rect; 
    GetItemRect(CommandToIndex(IDC_FONTNAME), &rect); 
    rect.right = rect.left + (LF_FACESIZE+4)*cxChar; 
    rect.bottom = rect.top + 16 * cyChar; 
    SetButtonInfo(CommandToIndex(IDC_FONTNAME), IDC_FONTNAME, TBBS_SEPARATOR, rect.Width()); 

    UINT nCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_VSCROLL; 
    if(!m_cmbFontName.Create(nCreateStyle | CBS_DROPDOWNLIST | CBS_SORT, rect, this, IDC_FONTNAME))
        return -1; 

    GetItemRect(CommandToIndex(IDC_FONTSIZE), &rect); 
    rect.right = rect.left + 10 * cxChar; 
    rect.bottom = rect.top + 16 * cyChar; 
    SetButtonInfo(CommandToIndex(IDC_FONTSIZE), IDC_FONTSIZE, TBBS_SEPARATOR, rect.Width()); 

    if(!m_cmbFontSize.Create(nCreateStyle | CBS_DROPDOWN | WS_HSCROLL, rect, this, IDC_FONTSIZE))
        return -1; 

    m_cmbFontSize.LimitText(4); 
    m_cmbFontName.SetFont(&font); 
    m_cmbFontSize.SetFont(&font); 
    ::EnumFontFamilies(dc.m_hDC, NULL, (FONTENUMPROC)EnumFontFamProc, (LPARAM)this); 

    CString strSize; 
    int nSizeCount = sizeof(nFontSizes) / sizeof(nFontSizes[0]); 
    for(int i=0; i<nSizeCount; i++)
    {
        strSize.Format("%d", nFontSizes[i]); 
        m_cmbFontSize.AddString(strSize); 
    }

	return 0;
}

int CALLBACK CFormatBar::EnumFontFamProc(ENUMLOGFONT* lpelf, NEWTEXTMETRIC* lpntm, int nFontType, LPARAM lParam) 
{
    CFormatBar* pWnd = (CFormatBar*)lParam; 
    pWnd->m_cmbFontName.AddString(lpelf->elfLogFont.lfFaceName); 
    return 1; 
}

void CFormatBar::OnSelectFontName()
{
    TCHAR szFontName[LF_FACESIZE]; 
    int nIndex = m_cmbFontName.GetCurSel(); 
    m_cmbFontName.GetLBText(nIndex, szFontName); 

    if(szFontName[0] == 0)
        return; 

    CHARNMHDR fh; 
    CHARFORMAT& cf = fh.cf; 
    fh.hwndFrom = m_hWnd;
    fh.idFrom = GetDlgCtrlID(); 
    fh.code = FN_SETFORMAT; 
    cf.dwMask = CFM_FACE; 
    _tcsncpy(cf.szFaceName, szFontName, LF_FACESIZE); 

    GetOwner()->SendMessage(WM_NOTIFY, fh.idFrom, (LPARAM)&fh); 
}

void CFormatBar::OnSelectFontSize()
{
    TCHAR szSize[5]; 
    int index = m_cmbFontSize.GetCurSel(); 
    if(index != CB_ERR)
        m_cmbFontSize.GetLBText(index, szSize); 
    else 
        m_cmbFontSize.GetWindowText(szSize, 5); 

    int nSize = _ttoi(szSize) * 20; 
    if(!nSize)
        return; 
    
    CHARNMHDR fh; 
    CHARFORMAT& cf = fh.cf; 
    fh.hwndFrom = m_hWnd; 
    fh.idFrom = GetDlgCtrlID(); 
    fh.code = FN_SETFORMAT; 
    cf.dwMask = CFM_SIZE; 
    cf.yHeight = nSize; 

    GetOwner()->SendMessage(WM_NOTIFY, fh.idFrom, (LPARAM)&fh); 
}

void CFormatBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)
{
    CToolBar::OnUpdateCmdUI(pTarget, bDisableIfNoHandler); 

    CWnd* pWnd = GetFocus(); 
    if(pWnd == &m_cmbFontName || m_cmbFontSize.IsChild(pWnd))
        return; 

    CHARNMHDR fh; 
    CHARFORMAT& cf = fh.cf; 
    fh.hwndFrom = m_hWnd; 
    fh.idFrom = GetDlgCtrlID(); 
    fh.code = FN_GETFORMAT; 

    CWnd* pOwnerWnd = GetOwner(); 
    if(!pOwnerWnd->SendMessage(WM_NOTIFY, fh.idFrom, (LPARAM)&fh))
        return; 

    TCHAR szName[LF_FACESIZE]; 
    m_cmbFontName.GetWindowText(szName, LF_FACESIZE); 

    if((cf.dwMask & (CFM_FACE | CFM_CHARSET)) != (CFM_FACE | CFM_CHARSET))
        m_cmbFontName.SetCurSel(-1); 
    else if(_tcscmp(szName, cf.szFaceName) != 0)
    {
        if(m_cmbFontName.SelectString(-1, cf.szFaceName) == CB_ERR)
            m_cmbFontName.SetCurSel(-1); 
    }

    TCHAR szSize[5]; 
    m_cmbFontSize.GetWindowText(szSize, 5); 
    int nSize = _ttoi(szSize); 

    int nSelSize = (cf.dwMask & CFM_SIZE) ? cf.yHeight / 20 : 0; 
    if(nSize != nSelSize)
    {
        if(cf.dwMask & CFM_SIZE)
        {
            CString strSize; 
            strSize.Format("%d", nSelSize); 
            m_cmbFontSize.SetWindowText(strSize); 
        }
        else 
            m_cmbFontSize.SetCurSel(-1); 
    }
}

BOOL CFormatBar::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_KEYDOWN)
    {
        NMHDR nm; 
        nm.hwndFrom = m_hWnd; 
        nm.idFrom = GetDlgCtrlID();
        nm.code = NM_RETURN; 
        switch(pMsg->wParam)
        {
        case VK_RETURN:
            if(m_cmbFontName.IsChild(GetFocus()))
                OnSelectFontName(); 
            else if(m_cmbFontSize.IsChild(GetFocus()))
                OnSelectFontSize(); 
        case VK_SPACE:
            GetOwner()->SendMessage(WM_NOTIFY, nm.idFrom, (LPARAM)&nm); 
            return TRUE; 
        }
    }

    return CToolBar::PreTranslateMessage(pMsg); 
}