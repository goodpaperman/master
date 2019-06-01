// threads.cpp : implementation file
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
// CExampleThread

IMPLEMENT_DYNCREATE(CExampleThread, CWinThread)

CExampleThread::CExampleThread()
{
	m_bDone = FALSE; 
	m_pOwner = NULL; 
	m_bAutoDelete = FALSE; 
}

CExampleThread::~CExampleThread()
{
}

BEGIN_MESSAGE_MAP(CExampleThread, CWinThread)
	//{{AFX_MSG_MAP(CExampleThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleThread message handlers
/////////////////////////////////////////////////////////////////////////////
// CCounterThread

IMPLEMENT_DYNCREATE(CCounterThread, CExampleThread)

CCounterThread::CCounterThread()
{
}

CCounterThread::~CCounterThread()
{
}

BOOL CCounterThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

BEGIN_MESSAGE_MAP(CCounterThread, CExampleThread)
	//{{AFX_MSG_MAP(CCounterThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCounterThread message handlers

int CCounterThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL fSyncChecked; 
	unsigned int nNumber; 
	if(m_pOwner == NULL)
		return -1; 

	CSingleLock sLock(&(m_pOwner->m_mutex)); 
	while(!m_bDone)
	{
		// Get the status of the Synchronize 
		// check box and save it 
		fSyncChecked = m_pOwner->IsDlgButtonChecked(IDC_SYNCHRONIZE); 

		// If the user wants us synchronize, do it!
		if(fSyncChecked)
			sLock.Lock(); 

		_stscanf((LPCTSTR)m_pOwner->m_strNumber, _T("%d"), &nNumber); 
		nNumber++; 
		m_pOwner->m_strNumber.Empty(); 
		while(nNumber != 0)
		{
			m_pOwner->m_strNumber += (TCHAR)('0' + nNumber%10); 

			// A call to Sleep() here tells the system that we want 
			// to relinguis the remainder of our time slice to 
			// another thread. this call is needed for 
			// single-CPU systems so that the results of the 
			// synchronization or lack thereof are obvious. 
			// Normally, your programs would NOT call Sleep() here.
			Sleep(0); 

			// get ready to get the next digit.
			nNumber /= 10; 
		}

		// Characters were generated in reverse order, 
		// reverse the string. 
		m_pOwner->m_strNumber.MakeReverse(); 
		if(fSyncChecked)
			// If the user wants synchronization, do it 
			sLock.Unlock(); 
		
		// If the user wants to display something after each iteration, do it.
		if(m_pOwner->IsDlgButtonChecked(IDC_SHOWCNTRTHRD))
			m_pOwner->AddToListBox(_T("Cntr: Increment")); 

		Sleep(50); 
	}

	m_pOwner->PostMessage(WM_CLOSE, 0, 0); 
	return 0; 
}

BOOL CCounterThread::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CExampleThread::PreTranslateMessage(pMsg);
	return FALSE; 
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayThread

IMPLEMENT_DYNCREATE(CDisplayThread, CExampleThread)

CDisplayThread::CDisplayThread()
{
}

CDisplayThread::~CDisplayThread()
{
}

BOOL CDisplayThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDisplayThread, CExampleThread)
	//{{AFX_MSG_MAP(CDisplayThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayThread message handlers

int CDisplayThread::Run() 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL fSyncChecked; 
	CString strBuffer; 
	ASSERT(m_pOwner != NULL); 
	if(m_pOwner == NULL)
		return -1; 

	CSingleLock sLock(&(m_pOwner->m_mutex)); 
	while(!m_bDone)
	{
		// Determine whether the user wants the threads 
		// to be synchronized.
		fSyncChecked = m_pOwner->IsDlgButtonChecked(IDC_SYNCHRONIZE); 
		if(fSyncChecked)
			sLock.Lock(); 

		// Construct a string with the string form of the number. 
		strBuffer = _T("Dspy: "); 
		strBuffer += m_pOwner->m_strNumber; 
		if(fSyncChecked)
			sLock.Unlock(); 

		// Add the string form of the number to the list box. 
		m_pOwner->AddToListBox(strBuffer); 
		Sleep(50); 
	}

	m_pOwner->PostMessage(WM_CLOSE, 0, 0); 
	return 0; 
}

BOOL CDisplayThread::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	//return CExampleThread::PreTranslateMessage(pMsg);
	return FALSE; 
}