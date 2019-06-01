// DemoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CView)

BEGIN_MESSAGE_MAP(CDemoView, CView)
	//{{AFX_MSG_MAP(CDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here

}

CDemoView::~CDemoView()
{
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

    int nPosition = 0; 
    for(int i=6; i<=60; i+=2)
    {
        ShowFont(pDC, nPosition, i); 
    }
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView printing

BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
    pInfo->SetMaxPage(2); 
	return DoPreparePrinting(pInfo);
}

void CDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
    pInfo->SetMaxPage(2); 
}

void CDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers


void CDemoView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	pDC->SetMapMode(MM_ANISOTROPIC); 
    pDC->SetWindowExt(1440, 1440); 
    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX), 
        -pDC->GetDeviceCaps(LOGPIXELSY)); 
	//CView::OnPrepareDC(pDC, pInfo);

    if(pDC->IsPrinting())
    {
        int nPageHeight = pDC->GetDeviceCaps(VERTRES); 
        int nOriginY = nPageHeight * (pInfo->m_nCurPage - 1); 
        pDC->SetViewportOrg(0, -nOriginY); 
    }
}

void CDemoView::ShowFont(CDC* pDC, int& nPos, int nPoints)
{
    TEXTMETRIC tm; 
    CFont NewFont; 
    char psOrigin[100]; 
    CSize ExtentSize; 
    NewFont.CreateFont(-nPoints*20, 0, 0, 0, FW_BOLD, TRUE, FALSE, FALSE, 
        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
        DEFAULT_PITCH | FF_SWISS, "Times New Roman"); 

    CFont* pOldFont = (CFont*)pDC->SelectObject(&NewFont); 
    pDC->GetTextMetrics(&tm); 
    TRACE("Points = %d, tmHeight = %d, tmInternalLeading = %d, "
        "tmExternalLeading = %d\n", nPoints, tm.tmHeight, 
        tm.tmInternalLeading, tm.tmExternalLeading); 

    wsprintf(psOrigin, "This is %d-point Times New Roman.", nPoints); 
    CString str(psOrigin); 
    ExtentSize = pDC->GetTextExtent(str); 
    pDC->TextOut(0, nPos, str); 
    pDC->SelectObject(pOldFont); 
    nPos -= tm.tmHeight + tm.tmExternalLeading + 50; 
}

void CDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	PrintHeader(pDC, pInfo); 
    PrintFooter(pDC, pInfo); 
	CView::OnPrint(pDC, pInfo);
}

void CDemoView::PrintHeader(CDC* pDC, CPrintInfo* pInfo)
{
    CRect rect = pInfo->m_rectDraw; 
    rect.bottom = rect.top - 1000; 
    pInfo->m_rectDraw.top = rect.bottom; 
    pDC->DrawText(GetDocument()->GetPathName(), rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 
}

void CDemoView::PrintFooter(CDC* pDC, CPrintInfo* pInfo)
{
    CString str; 
    str.Format("Page %d", pInfo->m_nCurPage); 
    CRect rect = pInfo->m_rectDraw; 
    rect.top = rect.bottom + 1000;
    pInfo->m_rectDraw.bottom = rect.top; 
    pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); 
}
