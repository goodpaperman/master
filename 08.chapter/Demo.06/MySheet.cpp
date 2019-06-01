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

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
    Init(); 
}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    Init(); 
}

void CMySheet::Init()
{
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
    ON_COMMAND(ID_APPLY_NOW, OnApplyNow) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySheet message handlers

BOOL CMySheet::OnInitDialog()
{
    BOOL bRes = CPropertySheet::OnInitDialog(); 
    CRect rectWnd; 
    GetWindowRect(&rectWnd); 
    SetWindowPos(NULL, 0, 0, rectWnd.Width() + 100, rectWnd.Height(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE); 

    GetTabControl()->GetWindowRect(&rectWnd); 
    GetTabControl()->SetWindowPos(NULL, 0, 0, rectWnd.Width() + 100, rectWnd.Height(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE); 

    CPropertyPage* pPage = GetActivePage(); 
    pPage->GetWindowRect(&m_rectPage); 
    ScreenToClient(&m_rectPage); 
    m_rectPage.right += 100; 
    pPage->MoveWindow(&m_rectPage); 
    return bRes; 
}

void CMySheet::OnApplyNow()
{
    Default(); 
    GetActivePage()->MoveWindow(&m_rectPage); 
}

BOOL CMySheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	NMHDR* pNMHDR = (NMHDR*)lParam; 
	BOOL bRes =  CPropertySheet::OnNotify(wParam, lParam, pResult);
    if(TCN_SELCHANGE == pNMHDR->code)
    {
        if(!bRes)
        {
            LRESULT lRes = Default(); 
            if(pResult)
                *pResult = lRes; 
        }

        GetActivePage()->MoveWindow(&m_rectPage); 
        return TRUE; 
    }

    return bRes; 
}
