// SmallPage.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "SmallPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmallPage property page

IMPLEMENT_DYNCREATE(CSmallPage, CWizPropertyPage)

CSmallPage::CSmallPage() : CWizPropertyPage(CSmallPage::IDD)
{
	//{{AFX_DATA_INIT(CSmallPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSmallPage::~CSmallPage()
{
}

void CSmallPage::DoDataExchange(CDataExchange* pDX)
{
	CWizPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmallPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmallPage, CWizPropertyPage)
	//{{AFX_MSG_MAP(CSmallPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmallPage message handlers
