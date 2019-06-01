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
    DDX_Control(pDX, IDC_TREE_DEMO, m_tree); 
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(ID_EXPAND, OnBtnExpand) 
    ON_BN_CLICKED(ID_COLLAPSE, OnBtnCollapse) 
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_BN_CLICKED(ID_SAVE, OnSave)
	ON_BN_CLICKED(ID_LOAD, OnLoad)
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
    m_tree.m_imageState.Create(IDB_STATE, 13, 1, RGB(255, 255, 255)); 
    m_tree.SetImageList(&m_tree.m_imageState, TVSIL_STATE); 
	m_tree.m_image.Create(IDB_NORMAL, 16, 1, RGB(255, 255, 255)); 
    m_tree.SetImageList(&m_tree.m_image, TVSIL_NORMAL); 

    CString str; 
    for(int i=0; i<5; i++)
    {
        str.Format("%d", i); 
        HTREEITEM hItem = m_tree.InsertItem(str, i, i+5); 
        m_tree.SetItemState(hItem, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK); 
        for(int j=0; j<5; j++)
        {
            str.Format("%d", j); 
            HTREEITEM hItem2 = m_tree.InsertItem(str, j, j+5, hItem); 
            m_tree.SetItemState(hItem2, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK); 
        }
    }

    m_tree.ExpandBranchCompletely(m_tree.GetRootItem(), TVE_EXPAND); 

    HTREEITEM hRoot = m_tree.GetRootItem(); 
    while(hRoot)
    {
        LOGFONT logfont; 
        CFont* pFont = GetFont(); 
        pFont->GetLogFont(&logfont); 
        logfont.lfItalic = TRUE; 
        logfont.lfUnderline = TRUE; 
        m_tree.SetItemFont(hRoot, logfont); 
        m_tree.SetItemBold(hRoot, TRUE); 
        m_tree.SetItemColor(hRoot, RGB(255, 0, 0)); 


        TRACE("%s\n", m_tree.GetItemText(hRoot)); 
        hRoot = m_tree.GetNextItem(hRoot); 
    }

    hRoot = m_tree.GetLastItem(NULL); 
    TRACE("Last: %s\n", m_tree.GetItemText(hRoot)); 
    while(hRoot)
    {
        TRACE("%s\n", m_tree.GetItemText(hRoot)); 
        hRoot = m_tree.GetPrevItem(hRoot); 
    }

    CString strFind = "2"; 
    hRoot = m_tree.FindItem(strFind, TRUE, FALSE, TRUE, NULL); 
    TRACE("Find 2: %s\n", m_tree.GetItemText(hRoot)); 
    TRACE("Parent: %s\n", m_tree.GetItemText(m_tree.GetParentItem(hRoot))); 

    m_tree.SetBkImage(IDB_BITMAP1); 
    //m_tree.SetBkImage(IDB_BITMAP2); 
    //m_tree.SetBkImage(IDB_BITMAP3); 
    //m_tree.SetBkImage(IDB_BITMAP4); 
    //m_tree.SetBkImage(IDB_BITMAP5); 
    //m_tree.SetBkImage(IDB_BITMAP6); 

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


void CDemoDlg::OnBtnExpand()
{
    m_tree.ExpandAll(TVE_EXPAND); 
}

void CDemoDlg::OnBtnCollapse()
{
    m_tree.ExpandAll(TVE_COLLAPSE); 
}

BOOL CDemoDlg::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnQueryNewPalette();
    return m_tree.SendMessage(WM_QUERYNEWPALETTE); 
}

void CDemoDlg::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CDialog::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
    m_tree.SendMessage(WM_PALETTECHANGED, (WPARAM)pFocusWnd->m_hWnd); 	
}

void CDemoDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(FALSE, "", "*.txt"); 
    if(dlg.DoModal() == IDOK)
    {
        CString strFile = dlg.GetPathName(); 
        CFile file; 
        file.Open(strFile, CFile::modeCreate | CFile::modeWrite); 
        CArchive ar(&file, CArchive::store); 
        m_tree.Serialize(ar); 
        ar.Close(); 
        file.Close(); 
    }
}

void CDemoDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE, "", "*.txt"); 
    if(dlg.DoModal() == IDOK)
    {
        CString strFile = dlg.GetPathName(); 
        CFile file; 
        file.Open(strFile, CFile::modeRead); 
        CArchive ar(&file, CArchive::load); 
        m_tree.Serialize(ar); 
        ar.Close(); 
        file.Close(); 
    }
}
