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
    //m_psh.dwFlags |= PSH_NOAPPLYNOW; 
    m_psh.dwFlags |= PSH_HASHELP; 
}

CMySheet::~CMySheet()
{
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMySheet message handlers

BOOL CMySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	
    CWnd* pWnd; 
    //pWnd = GetDlgItem(IDOK); 
    //pWnd->ShowWindow(FALSE); 

    //pWnd = GetDlgItem(IDCANCEL); 
    //pWnd->EnableWindow(FALSE); 

    //pWnd = GetDlgItem(ID_APPLY_NOW); 
    //pWnd->ShowWindow(SW_HIDE); 

    //pWnd = GetDlgItem(IDHELP); 
    //pWnd->ShowWindow(SW_HIDE); 
    //pWnd->EnableWindow(TRUE); 

    //CRect rectWnd, rectBtn;
    //GetWindowRect(rectWnd); 
    //GetDlgItem(IDOK)->GetWindowRect(&rectBtn); 

    //int btnwidth = rectBtn.Width(); 
    //int btnheight = rectBtn.Height(); 
    //int offset = rectWnd.bottom - rectBtn.bottom; 
    //int btnleft = rectWnd.right - rectWnd.left; 
    //rectWnd.bottom = rectBtn.top; 
    //rectWnd.right += btnwidth + offset; 
    //MoveWindow(rectWnd);


    //int ids[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP}; 
    //rectBtn.left = btnleft; 
    //rectBtn.right = btnleft + btnwidth; 
    //for(int i=0; i<sizeof(ids)/sizeof(ids[0]); i++)
    //{
    //    rectBtn.top = offset + i * (offset+btnheight); 
    //    rectBtn.bottom = rectBtn.top + btnheight; 
    //    GetDlgItem(ids[i])->MoveWindow(rectBtn); 
    //}


    CTabCtrl* pTabCtrl = GetTabControl(); 
    for(CWnd* pChild = GetWindow(GW_CHILD); pChild; pChild = pChild->GetNextWindow(GW_HWNDNEXT))
    {
        if(pChild == pTabCtrl)
            continue; 

        CRect rectControlWnd; 
        pChild->GetWindowRect(rectControlWnd); 
        ScreenToClient(rectControlWnd); 
        rectControlWnd.OffsetRect(0, 40); 
        pChild->MoveWindow(rectControlWnd); 
    }

    CRect rectWnd; 
    GetWindowRect(&rectWnd); 
    SetWindowPos(NULL, 0, 0, rectWnd.Width(), rectWnd.Height() + 40, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE); 
    ScreenToClient(rectWnd); 

    m_edit.CreateEx(WS_EX_CLIENTEDGE, _T("Edit"), NULL, 
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, 
        20, rectWnd.bottom - 20, 300, 24, m_hWnd, 0, 0); 
    m_edit.SetFont(GetFont()); 
    CenterWindow(); 

    CString sCaption = _T("New Caption"); 
    TC_ITEM tcItem; 
    tcItem.mask = TCIF_TEXT; 
    tcItem.pszText = (LPTSTR)((LPCTSTR)sCaption); 
    GetTabControl()->SetItem(0, &tcItem); 

    m_fontEdit.CreateFont(-8, 0, 0, 0, 700, 0, 0, 0, 1, 0, 0, 0, 0, _T("MS Sans Serif")); 
    GetTabControl()->SetFont(&m_fontEdit); 

    m_imageTab.Create(IDB_TAB, 16, 1, RGB(192, 192, 192)); 
    CTabCtrl* pTab = GetTabControl(); 
    pTab->SetImageList(&m_imageTab); 

    tcItem.mask = TCIF_IMAGE; 
    for(int i=0; i<6; i++)
    {
        tcItem.iImage = i; 
        pTab->SetItem(i, &tcItem); 
    }

	return bResult;
}
