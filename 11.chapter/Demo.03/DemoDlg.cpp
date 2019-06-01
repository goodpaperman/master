// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDemoDlg::~CDemoDlg()
{
	if(m_pFtpConnection != NULL)
	{
		m_pFtpConnection->Close(); 
		delete m_pFtpConnection; 
	}

	if(m_pInetSession != NULL)
	{
		m_pInetSession->Close(); 
		delete m_pInetSession; 
	}
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_COMBO, m_comboFtpSite);
	DDX_Control(pDX, IDC_TREE, m_FtpTreeCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON, OnButton)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rect; 
	GetWindowRect(&rect); 
	m_OrigSize = rect.Size(); 
	m_pFtpConnection = NULL; 
	CString str; 
	if(!str.LoadString(IDS_APPNAME))
		str = _T("AppUnknown"); 

	m_pInetSession = new CInternetSession(str, 1, PRE_CONFIG_INTERNET_ACCESS); 
	if(!m_pInetSession)
	{
		AfxMessageBox(IDS_BAD_SESSION, MB_OK); 
		OnCancel(); 
	}

	CImageList* pImageList = new CImageList(); 
	pImageList->Create(16, 16, TRUE, 3, 2); 
	CBitmap bitmap; 
	for(UINT iCnt = IDB_BMERROR; iCnt <= IDB_BMFILE; iCnt ++)
	{
		bitmap.LoadBitmap(iCnt); 
		pImageList->Add(&bitmap, (COLORREF)0xFFFFFF); 
		bitmap.DeleteObject(); 
	}

	m_FtpTreeCtrl.SetImageList(pImageList, TVSIL_NORMAL); 
	m_FtpTreeCtrl.PopulateTree(); 

	if(m_comboFtpSite.GetCount() > 0)
		m_comboFtpSite.SetCurSel(0); 
	
//	m_comboFtpSite.GetLBText(0, str); 
//	m_comboFtpSite.SetWindowText(str); 

	return TRUE;  // return TRUE  unless you set the focus to a control
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

void CDemoDlg::OnButton() 
{
	// TODO: Add your control notification handler code here
	CString strFtpSite, strServerName, strObject; 
	INTERNET_PORT nPort; 
	DWORD dwServiceType; 
	if(m_pFtpConnection != NULL)
		m_pFtpConnection->Close(); 
	delete m_pFtpConnection; 
	m_pFtpConnection = NULL; 

	m_comboFtpSite.GetWindowText(strFtpSite); 
	int nListCount = m_comboFtpSite.GetCount(); 
	CString strTemp; 
	while(nListCount > 0)
	{
		m_comboFtpSite.GetLBText(--nListCount, strTemp); 
		if(strFtpSite.Compare(strTemp) == 0)
		{
			m_comboFtpSite.DeleteString(nListCount); 
			nListCount = 0; 
		}
	}

	m_comboFtpSite.InsertString(0, strFtpSite); 
	if(m_comboFtpSite.GetCount() > 5)
		m_comboFtpSite.DeleteString(5); 

	if(!AfxParseURL(strFtpSite, dwServiceType, strServerName, strObject, nPort))
	{
		CString strFtpURL = _T("ftp://"); 
		strFtpURL += strFtpSite; 
		if(!AfxParseURL(strFtpURL, dwServiceType, strServerName, strObject, nPort))
		{
			AfxMessageBox(IDS_INVALID_URL, MB_OK); 
			m_FtpTreeCtrl.PopulateTree(); 
			return; 
		}
	}

	CWaitCursor cursor; 
	m_comboFtpSite.SetWindowText(strFtpSite); 
	m_comboFtpSite.SetEditSel(-1, -1); 
	if((dwServiceType == INTERNET_SERVICE_FTP) && !strServerName.IsEmpty())
	{
		try
		{
			m_pFtpConnection = m_pInetSession->GetFtpConnection(strServerName); 
		}
		catch(CInternetException* pEx)
		{
			TCHAR szErr[1024]; 
			if(pEx->GetErrorMessage(szErr, 1024))
				AfxMessageBox(szErr, MB_OK); 
			else 
				AfxMessageBox(IDS_EXCEPTION, MB_OK); 

			pEx->Delete(); 
			m_pFtpConnection = NULL; 
		}
	}
	else 
		AfxMessageBox(IDS_INVALID_URL, MB_OK); 

	if(m_pFtpConnection != NULL)
		m_FtpTreeCtrl.PopulateTree(m_pFtpConnection, strObject); 
	else 
		m_FtpTreeCtrl.PopulateTree(); 
}

void CDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(cx > 0 && cy > 0)
	{
		CRect rect; 
		if(m_FtpTreeCtrl.m_hWnd != NULL)
		{
			m_FtpTreeCtrl.GetWindowRect(&rect); 
			ScreenToClient(&rect); 
			m_FtpTreeCtrl.MoveWindow(rect.left, rect.top, cx - (2 * rect.left), cy - rect.top - rect.left); 
		}
	}
}

void CDemoDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnGetMinMaxInfo(lpMMI);

	static BOOL bSetSize; 
	if(bSetSize)
	{
		lpMMI->ptMinTrackSize.x = m_OrigSize.cx; 
		lpMMI->ptMinTrackSize.y = m_OrigSize.cy; 
	}
	else 
		bSetSize = TRUE; 
}
