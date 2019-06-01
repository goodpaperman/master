#if !defined(AFX_THREADS_H__90946ACE_A221_4408_A99E_09CD47AFC6AB__INCLUDED_)
#define AFX_THREADS_H__90946ACE_A221_4408_A99E_09CD47AFC6AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// threads.h : header file
//

class CDemoDlg; 

/////////////////////////////////////////////////////////////////////////////
// CExampleThread thread

class CExampleThread : public CWinThread
{
	DECLARE_DYNCREATE(CExampleThread)
protected:
	CExampleThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleThread)
	//}}AFX_VIRTUAL

	void SetOwner(CDemoDlg* pOwner) { m_pOwner = pOwner; }
	CDemoDlg* m_pOwner; 
	BOOL m_bDone; 

// Implementation
protected:
	virtual ~CExampleThread();

	// Generated message map functions
	//{{AFX_MSG(CExampleThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CCounterThread thread

class CCounterThread : public CExampleThread
{
	DECLARE_DYNCREATE(CCounterThread)
protected:
	CCounterThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCounterThread)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
	public:
	virtual ~CCounterThread();

	// Generated message map functions
	//{{AFX_MSG(CCounterThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDisplayThread thread

class CDisplayThread : public CExampleThread
{
	DECLARE_DYNCREATE(CDisplayThread)
protected:
	CDisplayThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayThread)
	public:
	virtual BOOL InitInstance();
	virtual int Run();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
	public:
	virtual ~CDisplayThread();

	// Generated message map functions
	//{{AFX_MSG(CDisplayThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THREADS_H__90946ACE_A221_4408_A99E_09CD47AFC6AB__INCLUDED_)
