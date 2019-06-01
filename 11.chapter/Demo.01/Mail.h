// Mail.h: interface for the CMail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAIL_H__168A5DE2_95F1_4BB7_AD3B_3EB402BCFD07__INCLUDED_)
#define AFX_MAIL_H__168A5DE2_95F1_4BB7_AD3B_3EB402BCFD07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mapi.h> 

class CMail  
{
public:
	CMail();
	virtual ~CMail();

	enum EC_ERRORCODES
	{
		IMAPI_SUCCESS = 0, 
		IMAPI_LOADFAILED, 
		IMAPI_INVALIDDLL, 
		IMAPI_FAILTO, 
		IMAPI_FAILCC, 
		IMAPI_FAILATTACH, 
	}; 

	void SetSubject(LPCTSTR lpszSubject)
	{
		m_mapiMessage.lpszSubject = (LPTSTR)lpszSubject; 
	}

	void SetText(LPCTSTR lpszText)
	{
		m_strText = lpszText; 
	}

	UINT GetLastError(); 

	void From(LPCTSTR lpszFrom)
	{
		m_lpszFrom.lpszName = (LPTSTR)lpszFrom; 
	}

	static BOOL HasEmail(); 

	BOOL To(LPCTSTR lpszRecip); 
	BOOL Cc(LPCTSTR lpszRecip); 
	BOOL SetAttachment(LPCTSTR lpszPath, LPCTSTR lpszName = NULL); 
	BOOL Send(ULONG ulFlags = 0); 

private:
	BOOL AllocNewTo(); 
	MapiMessage m_mapiMessage; 
	MapiRecipDesc m_lpszFrom; 
	UINT m_nError; 
	CString m_strText; 

	ULONG (PASCAL *m_lpfnSendMail)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG); 
	static HINSTANCE m_hInstMail; 
	static BOOL m_bIsAvailable; 
};

#endif // !defined(AFX_MAIL_H__168A5DE2_95F1_4BB7_AD3B_3EB402BCFD07__INCLUDED_)
