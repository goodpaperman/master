// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"
#include "threads.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent), 
	m_mutex(FALSE, NULL), 
	m_strNumber(_T("0"))
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pCounterThread = NULL; 
	m_pDisplayThread = NULL; 
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_PRIORITYCLASS, OnPriorityClassChange)
	ON_CBN_SELCHANGE(IDC_CNTRTHRDPRIORITY, OnPriorityChangeCntr)
	ON_CBN_SELCHANGE(IDC_DSPYTHRDPRIORITY, OnPriorityChangeDisp)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CComboBox* pBox; 
	pBox = (CComboBox*)GetDlgItem(IDC_PRIORITYCLASS); 
	ASSERT(pBox != NULL); 
	if(pBox)
	{
		pBox->AddString(_T("Idle")); 
		pBox->AddString(_T("Normal")); 
		pBox->AddString(_T("High")); 
		pBox->AddString(_T("Realtime")); 
		pBox->SetCurSel(1); 
	}

	pBox = (CComboBox*)GetDlgItem(IDC_DSPYTHRDPRIORITY); 
	ASSERT(pBox != NULL); 
	if(pBox)
	{
		pBox->AddString(_T("Idle")); 
		pBox->AddString(_T("Lowest")); 
		pBox->AddString(_T("Below Normal")); 
		pBox->AddString(_T("Normal")); 
		pBox->AddString(_T("Above Normal")); 
		pBox->AddString(_T("Highest")); 
		pBox->AddString(_T("TimeCritical")); 
		pBox->SetCurSel(3); 
	}

	pBox = (CComboBox*)GetDlgItem(IDC_CNTRTHRDPRIORITY); 
	ASSERT(pBox != NULL); 
	if(pBox)
	{
		pBox->AddString(_T("Idle")); 
		pBox->AddString(_T("Lowest")); 
		pBox->AddString(_T("Below Normal")); 
		pBox->AddString(_T("Normal")); 
		pBox->AddString(_T("Above Normal")); 
		pBox->AddString(_T("Highest")); 
		pBox->AddString(_T("TimeCritical")); 
		pBox->SetCurSel(3); 
	}

	CheckDlgButton(IDC_SYNCHRONIZE, TRUE); 
	m_pDisplayThread = (CDisplayThread*)AfxBeginThread(
		RUNTIME_CLASS(CDisplayThread), 
		THREAD_PRIORITY_NORMAL, 
		0, CREATE_SUSPENDED); 

	m_pDisplayThread->SetOwner(this); 
	m_pDisplayThread->ResumeThread(); 

	m_pCounterThread = (CCounterThread*)AfxBeginThread(
		RUNTIME_CLASS(CCounterThread), 
		THREAD_PRIORITY_NORMAL, 
		0, CREATE_SUSPENDED); 

	m_pCounterThread->SetOwner(this); 
	m_pCounterThread->ResumeThread(); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::AddToListBox(LPCTSTR szBuffer)
{
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_DATABOX); 
	ASSERT(pBox != NULL); 

	if(pBox)
	{
		while(pBox->GetCount() > 100)
			pBox->DeleteString(0); 

		//int x = pBox->AddString(szBuffer); 
		//if(x >= 0)
		//	pBox->SetCurSel(x); 

		int x = pBox->InsertString(pBox->GetCount(), szBuffer); 
		if(x >= 0)
			pBox->SetCurSel(x); 
	}
}

void CDemoDlg::OnPriorityClassChange() 
{
	// TODO: Add your control notification handler code here
	DWORD dw; 
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_PRIORITYCLASS); 
	int nCurSel = pBox->GetCurSel(); 
	switch(nCurSel)
	{
	case 0:
		dw = IDLE_PRIORITY_CLASS; 
		break; 
	default:
	case 1:
		dw = NORMAL_PRIORITY_CLASS; 
		break; 
	case 2:
		dw = HIGH_PRIORITY_CLASS; 
		break; 
	case 3:
		dw = REALTIME_PRIORITY_CLASS; 
		break; 
	}

	SetPriorityClass(GetCurrentProcess(), dw); 
}

void CDemoDlg::OnPriorityChangeCntr() 
{
	// TODO: Add your control notification handler code here
	OnPriorityChange(IDC_CNTRTHRDPRIORITY); 
}

void CDemoDlg::OnPriorityChangeDisp() 
{
	// TODO: Add your control notification handler code here
	OnPriorityChange(IDC_DSPYTHRDPRIORITY); 
}

void CDemoDlg::OnPriorityChange(UINT nID)
{
	ASSERT(nID == IDC_CNTRTHRDPRIORITY || nID == IDC_DSPYTHRDPRIORITY); 
	DWORD dw; 
	CComboBox* pBox = (CComboBox*)GetDlgItem(nID); 
	int nCurSel = pBox->GetCurSel(); 
	switch(nCurSel)
	{
	case 0:
		dw = (DWORD)THREAD_PRIORITY_IDLE; 
		break; 
	case 1:
		dw = (DWORD)THREAD_PRIORITY_LOWEST; 
		break; 
	case 2:
		dw = (DWORD)THREAD_PRIORITY_BELOW_NORMAL; 
		break; 
	case 3:
	default:
		dw = (DWORD)THREAD_PRIORITY_NORMAL; 
		break; 
	case 4:
		dw = (DWORD)THREAD_PRIORITY_ABOVE_NORMAL; 
		break; 
	case 5:
		dw = (DWORD)THREAD_PRIORITY_HIGHEST; 
		break; 
	case 6:
		dw = (DWORD)THREAD_PRIORITY_TIME_CRITICAL; 
		break; 
	}

	if(nID == IDC_CNTRTHRDPRIORITY)
		m_pCounterThread->SetThreadPriority(dw); 
	else 
		m_pDisplayThread->SetThreadPriority(dw); 
}

void CDemoDlg::OnPause() 
{
	// TODO: Add your control notification handler code here
	CButton* pCheck = (CButton*)GetDlgItem(IDC_PAUSE); 
	BOOL bPaused = ((pCheck->GetState() & 0x003) != 0); 
	if(bPaused)
	{
		m_pCounterThread->SuspendThread(); 
		m_pDisplayThread->SuspendThread(); 
	}
	else 
	{
		m_pCounterThread->ResumeThread(); 
		m_pDisplayThread->ResumeThread(); 
	}
}


void CDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	int nCount = 0; 
	DWORD dwStatus; 
	CButton* pCheck = (CButton*)GetDlgItem(IDC_PAUSE); 
	BOOL bPaused = ((pCheck->GetState() & 0x003) != 0); 
	if(bPaused)
	{
		pCheck->SetCheck(0); 
		m_pCounterThread->ResumeThread(); 
		m_pDisplayThread->ResumeThread(); 
	}

	if(m_pCounterThread)
	{
		VERIFY(::GetExitCodeThread(m_pCounterThread->m_hThread, &dwStatus)); 
		if(dwStatus == STILL_ACTIVE)
		{
			nCount ++; 
			m_pCounterThread->m_bDone = TRUE; 
		}
		else 
		{
			delete m_pCounterThread; 
			m_pCounterThread = NULL; 
		}
	}

	if(m_pDisplayThread != NULL)
	{
		VERIFY(::GetExitCodeThread(m_pDisplayThread->m_hThread, &dwStatus)); 
		if(dwStatus == STILL_ACTIVE)
		{
			nCount ++; 
			m_pDisplayThread->m_bDone = TRUE; 
		}
		else 
		{
			delete m_pDisplayThread; 
			m_pDisplayThread = NULL; 
		}
	}

	if(nCount == 0)
		CDialog::OnClose(); 
	else 
	{
		Sleep(50); 
		PostMessage(WM_CLOSE); 
	}
}