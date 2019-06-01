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

CMySheet::CMySheet()
{
}

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
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

BOOL CMySheet::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    if(pMsg->message == WM_SYSKEYDOWN && pMsg->wParam > 32)
    {
        CTabCtrl* pTab = GetTabControl(); 
        int n = pTab->GetItemCount(); 

        TCHAR buf[80], shortcut[3]; 
        TC_ITEM tcItem; 
        tcItem.mask = TCIF_TEXT; 
        tcItem.pszText = buf; 
        shortcut[0] = _T('&'); 
        shortcut[2] = _T('\0'); 

        for(int i=0; i<n; i++)
        {
            tcItem.cchTextMax = 79; 
            pTab->GetItem(i, &tcItem); 
            shortcut[1] = (TCHAR)pMsg->wParam; 
            if(_tcsstr(buf, shortcut))
            {
                SetActivePage(i); 
                return TRUE; 
            }
        }
    }

	return CPropertySheet::PreTranslateMessage(pMsg);
}
