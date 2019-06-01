// Sheet.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "Sheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSheet

IMPLEMENT_DYNAMIC(CSheet, CPropertySheet)

CSheet::CSheet() : CPropertySheet("CPropertySheet By Piperopoulos Panagiotis")
{
    m_page[0].Construct(IDD_DEMO_DIALOG); 
    m_page[1].Construct(IDD_PROPPAGE_SMALL); 
    m_page[2].Construct(IDD_PROPPAGE_MEDIUM); 
    m_page[3].Construct(IDD_PROPPAGE_LARGE); 

    for(int i=0; i<4; i++)
        AddPage(&m_page[i]); 
}

CSheet::~CSheet()
{
}


BEGIN_MESSAGE_MAP(CSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSheet)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
    ON_COMMAND_RANGE(ID_PAGE1, ID_PAGE4, OnDisplayPage) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheet message handlers

BOOL CSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
    GetDlgItem(IDOK)->ShowWindow(SW_HIDE); 
    GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE); 
    GetDlgItem(ID_APPLY_NOW)->ShowWindow(SW_HIDE); 
    GetDlgItem(IDHELP)->ShowWindow(SW_HIDE); 

	m_menu.LoadMenu(IDR_MENU); 
    SetMenu(&m_menu); 

    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE); 
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE); 

    ::SetWindowLong(m_hWnd, GWL_STYLE, GetStyle() | WS_MINIMIZEBOX); 
    GetSystemMenu(FALSE)->InsertMenu(-1, MF_BYPOSITION | MF_STRING, SC_ICON, "Minimize"); 
    DrawMenuBar(); 

    CRect rect; 
    GetWindowRect(&rect); 
    MoveWindow(rect.left, rect.top, rect.Width(), rect.Height() + 40); 
	return bResult;
}

void CSheet::OnDisplayPage(int nPage)
{
    int nIndex = nPage - ID_PAGE1; 
    ASSERT(nIndex >= 0 && nIndex < 4); 
    SetActivePage(&m_page[nIndex]); 
}

void CSheet::OnPaint() 
{
    CRect rect; 
    GetClientRect(rect); 
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    if(m_dc.m_hDC == NULL)
        m_dc.CreateCompatibleDC(&dc); 

	if(m_bmp.m_hObject == NULL)
        m_bmp.LoadBitmap(IDB_LOGO); 

    BITMAP bm; 
    m_bmp.GetBitmap(&bm); 
    m_dc.SelectObject(&m_bmp); 
    dc.BitBlt(rect.right - bm.bmWidth, rect.bottom - bm.bmHeight, bm.bmWidth, bm.bmHeight, &m_dc, 0, 0, SRCCOPY); 
	// Do not call CPropertySheet::OnPaint() for painting messages
}
