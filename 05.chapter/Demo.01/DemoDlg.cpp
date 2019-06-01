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

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_LIST_DEMO, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CLEAR, OnClear)
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
    
    CString str; 
    //CHeaderCtrl* pHeader = m_list.GetHeaderCtrl(); 
    //for(int i=0; i<7; i++)
    //{
    //    str.Format("%d", i); 
    //    m_list.InsertColumn(i, str); 
    //    m_list.SetColumnWidth(i, 60);         
    //    m_list.InsertItem(i, str); 
    //    for(int j=0; j<7; j++)
    //        m_list.SetItemText(i, j, str);     
        
    //    HD_ITEM hdi; 
    //    hdi.mask = HDI_FORMAT; 
    //    pHeader->GetItem(i, &hdi); 
    //    hdi.mask = HDI_BITMAP | HDI_FORMAT; 
    //    hdi.fmt |= HDF_BITMAP; 
    //    hdi.fmt &= ~HDF_STRING; 
    //    hdi.hbm = (HBITMAP)LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1 + i)); 
    //    pHeader->SetItem(i, &hdi); 
    //}

    m_ImageList.Create(16, 16, ILC_COLOR8, 8, 1); 
    for(int i=0; i<7; i++)
        m_ImageList.Add(CBitmap::FromHandle((HBITMAP)LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1+i))), RGB(0, 0, 0)); 

    CHeaderCtrlEx* pHeader = m_list.GetHeaderCtrl(); 
    pHeader->SetImageList(&m_ImageList);
    for(i=0; i<7; i++)
    {        
        str.Format("%d", i); 
        m_list.InsertColumn(i, str); 
        m_list.SetColumnWidth(i, 60);         
        m_list.InsertItem(i, str); 
        for(int j=0; j<i; j++)
            m_list.SetItemText(i, j, str);     

        pHeader->SetItemImage(i, i); 
    }
    
    m_list.SetItemState(3, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 
    m_list.SetItemState(4, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 
    m_list.SetItemState(5, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED); 
    
    m_list.SetItemRange(TRUE, 0, 6); 
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

void CDemoDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
    //CHeaderCtrl* pHeader = m_list.GetHeaderCtrl(); 
    //for(int i=0; i<pHeader->GetItemCount(); i++)
    //{
    //    HD_ITEM hdi; 
    //    hdi.mask = HDI_FORMAT; 
    //    pHeader->GetItem(i, &hdi); 
    //    hdi.mask = HDI_FORMAT; 
    //    hdi.fmt |= HDF_STRING; 
    //    hdi.fmt &= ~HDF_BITMAP; 
    //    pHeader->SetItem(i, &hdi); 
    //}

    CHeaderCtrlEx* pHeader = m_list.GetHeaderCtrl(); 
    for(int i=0; i<pHeader->GetItemCount(); i++)
        pHeader->SetItemImage(i, -1); 

    i = m_list.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED); 
    while(i != -1)
    {
        TRACE("%d\n", i); 
        i = m_list.GetNextItem(i, LVNI_ALL | LVNI_SELECTED); 
    }

    m_list.SetHighlightType(CListCtrlEx::HIGHLIGHT_ALLCOLUMNS); 
}
