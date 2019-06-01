// LargePage.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "LargePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLargePage property page

IMPLEMENT_DYNCREATE(CLargePage, CWizPropertyPage)

CLargePage::CLargePage() : CWizPropertyPage(CLargePage::IDD)
{
	//{{AFX_DATA_INIT(CLargePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CLargePage::~CLargePage()
{
}

void CLargePage::DoDataExchange(CDataExchange* pDX)
{
	CWizPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLargePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLargePage, CWizPropertyPage)
	//{{AFX_MSG_MAP(CLargePage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLargePage message handlers
