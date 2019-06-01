// MyPage.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "MyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPage property page

IMPLEMENT_DYNCREATE(CMyPage, CPropertyPage)

CMyPage::CMyPage() : CPropertyPage(CMyPage::IDD)
{
	//{{AFX_DATA_INIT(CMyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyPage::~CMyPage()
{
}

void CMyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPage message handlers
