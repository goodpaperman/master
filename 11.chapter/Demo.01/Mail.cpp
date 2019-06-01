// Mail.cpp: implementation of the CMail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Demo.h"
#include "Mail.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HINSTANCE CMail::m_hInstMail = (HINSTANCE)NULL; 
BOOL CMail::m_bIsAvailable = (BOOL)-1; 

CMail::CMail()
{
	m_nError = 0; 
	memset(&m_mapiMessage, 0, sizeof(MapiMessage)); 
	memset(&m_lpszFrom, 0, sizeof(MapiRecipDesc)); 
	m_mapiMessage.lpOriginator = &m_lpszFrom; 
	m_lpszFrom.ulRecipClass = MAPI_ORIG; 

	if(m_hInstMail == (HINSTANCE)NULL)
		m_hInstMail = ::LoadLibraryA("MAPI32.DLL"); 

	if(m_hInstMail == (HINSTANCE)NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_LOAD); 
		m_nError = IMAPI_LOADFAILED; 
		return; 
	}

	ASSERT(m_hInstMail != (HINSTANCE)NULL); 
	(FARPROC&)m_lpfnSendMail = GetProcAddress(m_hInstMail, "MAPISendMail"); 
	if(m_lpfnSendMail == NULL)
	{
		AfxMessageBox(AFX_IDP_INVALID_MAPI_DLL); 
		m_nError = IMAPI_INVALIDDLL; 
		return; 
	}

	ASSERT(m_lpfnSendMail != NULL); 
}

CMail::~CMail()
{
	if(m_hInstMail != (HINSTANCE)NULL)
		::FreeLibrary(m_hInstMail); 

	m_hInstMail = (HINSTANCE)NULL; 
	free(m_mapiMessage.lpFiles); 
	free(m_mapiMessage.lpRecips); 
}

BOOL CMail::HasEmail()
{
	if(m_bIsAvailable == (BOOL)-1)
	{
		m_bIsAvailable = ::GetProfileInt(_T("MAIL"), _T("MAPI"), 0) != 0 && 
			SearchPath(NULL, _T("MAPI32.DLL"), NULL, 0, NULL, NULL) != 0; 
	}

	return m_bIsAvailable; 
}

UINT CMail::GetLastError()
{
	UINT temp = m_nError; 
	m_nError = IMAPI_SUCCESS; 
	return temp; 
}

BOOL CMail::AllocNewTo()
{
	m_mapiMessage.lpRecips = (MapiRecipDesc*)realloc(m_mapiMessage.lpRecips, 
		(m_mapiMessage.nRecipCount+1)*sizeof(MapiRecipDesc)); 
	memset(&m_mapiMessage.lpRecips[m_mapiMessage.nRecipCount], 0, sizeof(MapiRecipDesc)); 
	ASSERT(m_mapiMessage.lpRecips); 
	return m_mapiMessage.lpRecips != (MapiRecipDesc*)NULL; 
}

BOOL CMail::To(LPCTSTR lpszRecip)
{
	if(AllocNewTo())
	{
		m_mapiMessage.lpRecips[m_mapiMessage.nRecipCount].lpszName = (LPTSTR)lpszRecip; 
		m_mapiMessage.lpRecips[m_mapiMessage.nRecipCount].ulRecipClass = MAPI_TO; 
		m_mapiMessage.nRecipCount++; 
		return TRUE; 
	}

	m_nError = IMAPI_FAILTO; 
	return FALSE; 
}

BOOL CMail::Cc(LPCTSTR lpszRecip)
{
	if(AllocNewTo())
	{
		m_mapiMessage.lpRecips[m_mapiMessage.nRecipCount].lpszName = (LPTSTR)lpszRecip; 
		m_mapiMessage.lpRecips[m_mapiMessage.nRecipCount].ulRecipClass = MAPI_CC; 
		m_mapiMessage.nRecipCount++; 
		return TRUE; 
	}

	m_nError = IMAPI_FAILCC; 
	return FALSE; 
}

BOOL CMail::SetAttachment(LPCTSTR lpszPath, LPCTSTR lpszName)
{
	m_mapiMessage.lpFiles = (MapiFileDesc*)realloc(m_mapiMessage.lpFiles, 
		(m_mapiMessage.nFileCount+1)*sizeof(MapiFileDesc)); 
	memset(&m_mapiMessage.lpFiles[m_mapiMessage.nFileCount], 0, sizeof(MapiFileDesc)); 
	ASSERT(m_mapiMessage.lpFiles); 
	if(m_mapiMessage.lpFiles == (MapiFileDesc*)NULL)
	{
		m_nError = IMAPI_FAILATTACH; 
		return FALSE; 
	}

	m_mapiMessage.lpFiles[m_mapiMessage.nFileCount].lpszPathName = (LPTSTR)lpszPath; 
	m_mapiMessage.lpFiles[m_mapiMessage.nFileCount].lpszFileName = (LPTSTR)lpszName; 
	m_mapiMessage.nFileCount++; 
	return TRUE; 
}

BOOL CMail::Send(ULONG ulFlags)
{
	CWaitCursor theWaitCursor; 
	int nOffset = m_strText.GetLength(); 
	m_strText += CString(' ', m_mapiMessage.nFileCount); 
	for(UINT i=0; i<m_mapiMessage.nFileCount; i++)
		m_mapiMessage.lpFiles[i].nPosition = nOffset++; 

	m_mapiMessage.lpszNoteText = (LPTSTR)(LPCTSTR)m_strText; 
	AfxGetApp()->EnableModeless(FALSE); 
	HWND hWndTop; 
	CWnd* pParentWnd = CWnd::GetSafeOwner(NULL, &hWndTop); 
	pParentWnd->SetCapture(); 
	::SetFocus(NULL); 
	pParentWnd->m_nFlags |= WF_STAYDISABLED; 

	int nError = m_lpfnSendMail(0, (ULONG)pParentWnd->GetSafeHwnd(), &m_mapiMessage, MAPI_LOGON_UI | ulFlags, 0); 
	::ReleaseCapture(); 
	pParentWnd->m_nFlags &= ~WF_STAYDISABLED; 

	pParentWnd->EnableWindow(TRUE); 
	::SetActiveWindow(NULL); 
	pParentWnd->SetActiveWindow(); 
	pParentWnd->SetFocus(); 

	if(hWndTop != NULL)
		::EnableWindow(hWndTop, TRUE); 

	AfxGetApp()->EnableModeless(TRUE); 
	if(nError != SUCCESS_SUCCESS && 
		nError != MAPI_USER_ABORT && 
		nError != MAPI_E_LOGIN_FAILURE)
	{
		AfxMessageBox(AFX_IDP_FAILED_MAPI_SEND); 
		return FALSE; 
	}

	return TRUE; 
}