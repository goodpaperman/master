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
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
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
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView printing

BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
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

BOOL CDemoView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, 
					   DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
					   UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(!CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext))
	{
		TRACE("Can't create view.\n"); 
		return FALSE; 
	}

	return TRUE; 
}

int CDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect client;  
	GetClientRect(&client); 
 	if(!m_wndBrowser.CreateControl(CLSID_WebBrowser, NULL, WS_VISIBLE | WS_CHILD, client, this, AFX_IDW_PANE_FIRST))
	{
		TRACE("Can't create Web Browser control window.\n"); 
		return -1;  
	}

	IUnknown* pUnk = m_wndBrowser.GetControlUnknown(); 
	ASSERT(pUnk); 
	IWebBrowser2* pBrowser; 
	HRESULT hr = pUnk->QueryInterface(IID_IWebBrowser2, (void**)&pBrowser); 
	if(!SUCCEEDED(hr))
	{
		TRACE("WebBrowser interface not supported.\n"); 
		return -1; 
	}

	CString url("http://1.1.1.6/"); 
	BSTR bUrl = url.AllocSysString(); 
	hr = pBrowser->Navigate(bUrl, &COleVariant((long)0, VT_I4), 
		&COleVariant((LPCTSTR)NULL, VT_BSTR), NULL, 
		&COleVariant((LPCTSTR)NULL, VT_BSTR)); 

	if(!SUCCEEDED(hr))
	{
		AfxMessageBox("Can't browse!!!"); 
		return -1; 
	}

	return 0;
}


void CDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(::IsWindow(m_wndBrowser.m_hWnd))
	{
		CRect client; 
		GetClientRect(&client); 
		m_wndBrowser.SetWindowPos(NULL, 0, 0, client.right, client.bottom, SWP_NOACTIVATE | SWP_NOZORDER); 
	}
}

void CDemoView::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	Default(); 
	// Do not call CView::OnPaint() for painting messages
}