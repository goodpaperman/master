// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Demo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_THREAD_START, OnThreadStart)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_THREADCEASE, OnThreadCease) 
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

volatile BOOL bThreadCeased = TRUE; 

CWorkerThread::CWorkerThread(HWND hWnd)
{
	m_hWnd = hWnd; 
}

UINT ThreadProc(LPVOID lpParam)
{
	CWorkerThread* pWorkerThread = (CWorkerThread*)lpParam; 
	pWorkerThread->OutputMsg(); 
	while(!bThreadCeased)
		; 

	if(::IsWindow(pWorkerThread->m_hWnd))
		::PostMessage(pWorkerThread->m_hWnd, WM_THREADCEASE, 0, 0); 

	delete pWorkerThread;  
	//::SendMessage((HWND)lpParam, WM_THREADCEASE, 0, 0); 
	return 0; 
}

void CMainFrame::OnThreadStart() 
{
	// TODO: Add your command handler code here
	// bThreadCeased = FALSE; 
	HWND hWnd = GetSafeHwnd(); 
	CWorkerThread* pWorkerThread = new CWorkerThread(hWnd); 
	AfxBeginThread(ThreadProc, pWorkerThread); 	
}

LONG CMainFrame::OnThreadCease(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("Thread is died."); 
	return 0; 
}
