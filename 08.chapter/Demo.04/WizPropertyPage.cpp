// WizPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "WizPropertyPage.h"
#include "WizPropertySheet.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizPropertyPage property page

IMPLEMENT_DYNCREATE(CWizPropertyPage, CPropertyPage)

CWizPropertyPage::CWizPropertyPage() : CPropertyPage()
{
	//{{AFX_DATA_INIT(CWizPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    Init(); 
}

CWizPropertyPage::CWizPropertyPage(UINT nIDTemplate, UINT nIDCaption /*=0*/) : CPropertyPage(nIDTemplate, nIDCaption)
{
    Init(); 
}

CWizPropertyPage::CWizPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption /*=0*/) : CPropertyPage(lpszTemplateName, nIDCaption) 
{
    Init(); 
}

void CWizPropertyPage::Init()
{
    m_pPropSheet = NULL; 
    m_bEnabled = TRUE; 
}

CWizPropertyPage::~CWizPropertyPage()
{
}

void CWizPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizPropertyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CWizPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizPropertyPage message handlers

LRESULT CWizPropertyPage::GetNextPage(BOOL forward /*=TRUE*/)
{
    ASSERT(m_pPropSheet); 
    int act = m_pPropSheet->GetActiveIndex(); 
    int count = m_pPropSheet->GetPageCount(); 
    act += (forward ? 1 : -1); 
    BOOL found = FALSE; 
    CWizPropertyPage* pPage; 
    CString tmp; 

    while(!found && act < count && act >= 0)
    {
        pPage = (CWizPropertyPage*)m_pPropSheet->GetPage(act); 
        if(pPage->IsEnabled())
            found = TRUE; 
        else 
            act += (forward ? 1 : -1); 
    }    

    if(found)
        return (LRESULT)pPage->m_lpszTemplateName; 

    return -1; 
}

BOOL CWizPropertyPage::IsEnabled()
{
    return m_bEnabled; 
}

BOOL CWizPropertyPage::Enable(BOOL bEnable)
{
    BOOL old = m_bEnabled; 
    m_bEnabled = bEnable; 
    return old; 
}

LRESULT CWizPropertyPage::OnWizardNext()
{
    return GetNextPage(); 
}

LRESULT CWizPropertyPage::OnWizardBack()
{
    return GetNextPage(FALSE); 
}
