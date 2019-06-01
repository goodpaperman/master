// MediumPage.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "MediumPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMediumPage property page

IMPLEMENT_DYNCREATE(CMediumPage, CWizPropertyPage)

CMediumPage::CMediumPage() : CWizPropertyPage(CMediumPage::IDD)
{
	//{{AFX_DATA_INIT(CMediumPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMediumPage::~CMediumPage()
{
}

void CMediumPage::DoDataExchange(CDataExchange* pDX)
{
	CWizPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMediumPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMediumPage, CWizPropertyPage)
	//{{AFX_MSG_MAP(CMediumPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediumPage message handlers
