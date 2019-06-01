// JuneDrawingPpg.cpp : Implementation of the CJuneDrawingPropPage property page class.

#include "stdafx.h"
#include "JuneDrawing.h"
#include "JuneDrawingPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CJuneDrawingPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJuneDrawingPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CJuneDrawingPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJuneDrawingPropPage, "JUNEDRAWING.JuneDrawingPropPage.1",
	0xa6f3572c, 0x671c, 0x40de, 0xbe, 0xb1, 0xe7, 0x16, 0x58, 0x8c, 0xc0, 0x58)


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingPropPage::CJuneDrawingPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CJuneDrawingPropPage

BOOL CJuneDrawingPropPage::CJuneDrawingPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_JUNEDRAWING_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingPropPage::CJuneDrawingPropPage - Constructor

CJuneDrawingPropPage::CJuneDrawingPropPage() :
	COlePropertyPage(IDD, IDS_JUNEDRAWING_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CJuneDrawingPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingPropPage::DoDataExchange - Moves data between page and properties

void CJuneDrawingPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CJuneDrawingPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingPropPage message handlers
