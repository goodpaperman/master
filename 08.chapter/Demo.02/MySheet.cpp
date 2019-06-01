// MySheet.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "MySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet(CWnd* pParentWnd)
	:CPropertySheet("Test", pParentWnd)
{
    Init(); 
}

void CMySheet::Init()
{
    //m_psh.dwFlags |= PSH_NOAPPLYNOW; 
    m_psh.dwFlags |= PSH_HASHELP; 

    AddPage(&m_page1); 
    AddPage(&m_page2); 
}

CMySheet::~CMySheet()
{
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_RESIZEPAGE, OnResizePage) 
    ON_COMMAND(ID_APPLY_NOW, OnApplyNow) 
    ON_WM_SIZE() 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySheet message handlers

BOOL CMySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
    //m_bModeless = TRUE; 
    Resize(); 
	return bResult;
}

void CMySheet::Resize()
{
    CRect rectParent; 
    CWnd* pParent = GetParent(); //AfxGetMainWnd(); 
    if(pParent == NULL)
    {
        AfxMessageBox("Cannot resize property sheet, Sheet has no parent.", 
            MB_ICONEXCLAMATION | MB_OK | MB_APPLMODAL); 
        return; 
    }

    pParent->GetClientRect(&rectParent); 
    //TRACE("parent rect: %d, %d, %d, %d\n", rectParent.left, rectParent.top, rectParent.right, rectParent.bottom); 

    CSize sizeRelChange; 
    CRect rectWindow; 

    GetWindowRect(&rectWindow); 
    ScreenToClient(&rectWindow); 
    sizeRelChange.cx = rectWindow.Width() - rectParent.Width() + 20; 
    sizeRelChange.cy = rectWindow.Height() - rectParent.Height() + 20; 

    TRACE("cx: %d\n", sizeRelChange.cx); 
    TRACE("cy: %d\n\n", sizeRelChange.cy); 
    rectWindow.right -= sizeRelChange.cx; 
    rectWindow.bottom -= sizeRelChange.cy; 
    MoveWindow(&rectWindow); 

    CTabCtrl* pTab = GetTabControl(); 
    pTab->GetWindowRect(&rectWindow); 
    ScreenToClient(&rectWindow); 
    rectWindow.right -= sizeRelChange.cx; 
    rectWindow.bottom -= sizeRelChange.cy; 
    pTab->MoveWindow(&rectWindow); 

    CPropertyPage* pPage = GetActivePage(); 
    pPage->GetWindowRect(&m_rectPage); 
    ScreenToClient(&m_rectPage);
    m_rectPage.right -= sizeRelChange.cx; 
    m_rectPage.bottom -= sizeRelChange.cy; 
    pPage->MoveWindow(&m_rectPage); 
}

LRESULT CMySheet::OnResizePage(WPARAM wParam, LPARAM lParam)
{
    CPropertyPage* pPage = GetActivePage(); 
    pPage->MoveWindow(&m_rectPage); 
    return 0; 
}

void CMySheet::OnApplyNow()
{
    PostMessage(WM_RESIZEPAGE); 
}

BOOL CMySheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    NMHDR* pNMHDR = (LPNMHDR)lParam; 
    if(pNMHDR->code == TCN_SELCHANGE)
        PostMessage(WM_RESIZEPAGE); 

    return CPropertySheet::OnNotify(wParam, lParam, pResult); 
}

void CMySheet::OnSize(UINT nType, int cx, int cy)
{
    AutoArrangeButtons(); 
    CPropertySheet::OnSize(nType, cx, cy); 
}

void CMySheet::AutoArrangeButtons()
{
    CWnd* pWnd = GetDlgItem(ID_APPLY_NOW); 
    if(pWnd && ::IsWindow(pWnd->m_hWnd)) 
    {
        pWnd = pWnd->GetWindow(GW_HWNDLAST); 
        CTabCtrl* pTab = GetTabControl(); 
        if(!pTab->GetSafeHwnd())
            return; 

        CRect rcTab(0, 0, 0, 0); 
        pTab->GetWindowRect(&rcTab); 
        ScreenToClient(&rcTab); 

        CRect rcTemp(0, 0, 0, 0); 
        GetClientRect(&rcTemp); 

        int nLeft = rcTemp.right; 
        int nSpacing = rcTemp.right - rcTab.right; 
        while(pWnd)
        {
            if(pWnd->GetSafeHwnd() == pTab->GetSafeHwnd())
            {
                pWnd = pWnd->GetWindow(GW_HWNDPREV); 
                continue; 
            }

            pWnd->GetWindowRect(&rcTemp); 
            ScreenToClient(&rcTemp); 
            BOOL bVisible = (pWnd->GetStyle() & WS_VISIBLE) == WS_VISIBLE; 
            if((rcTemp.top > rcTab.bottom) && bVisible)
            {
                nLeft -= nSpacing + rcTemp.Width(); 
                pWnd->MoveWindow(nLeft, rcTemp.top, rcTemp.Width(), rcTemp.Height()); 
            }

            pWnd = pWnd->GetWindow(GW_HWNDPREV);
        }
    }
}

void CMySheet::PostNcDestroy()
{
    delete this; 
}