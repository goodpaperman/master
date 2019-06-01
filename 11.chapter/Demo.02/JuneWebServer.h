#if !defined(AFX_JUNEWEBSERVER_H__513E3F31_FF2F_4E2B_A1F4_09DF866FAF05__INCLUDED_)
#define AFX_JUNEWEBSERVER_H__513E3F31_FF2F_4E2B_A1F4_09DF866FAF05__INCLUDED_

// JUNEWEBSERVER.H - Header file for your Internet Server
//    JuneWebServer Filter and JuneWebServer Extension

#include "resource.h"

class CJuneWebServerExtension : public CHttpServer
{
public:
	CJuneWebServerExtension();
	~CJuneWebServerExtension();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CJuneWebServerExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL
	virtual BOOL TerminateExtension(DWORD dwFlags);

	// TODO: Add handlers for your commands here.
	// For example:

	void Default(CHttpServerContext* pCtxt);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CJuneWebServerExtension)
	//}}AFX_MSG
};

class CJuneWebServerFilter : public CHttpFilter
{
public:
	CJuneWebServerFilter();
	~CJuneWebServerFilter();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CJuneWebServerFilter)
	public:
	virtual BOOL GetFilterVersion(PHTTP_FILTER_VERSION pVer);
	virtual DWORD OnPreprocHeaders(CHttpFilterContext* pCtxt, PHTTP_FILTER_PREPROC_HEADERS pHeaderInfo);
	virtual DWORD OnAuthentication(CHttpFilterContext* pCtxt, PHTTP_FILTER_AUTHENT pAuthent);
	virtual DWORD OnUrlMap(CHttpFilterContext* pCtxt, PHTTP_FILTER_URL_MAP pMapInfo);
	virtual DWORD OnSendRawData(CHttpFilterContext* pCtxt, PHTTP_FILTER_RAW_DATA pRawData);
	virtual DWORD OnReadRawData(CHttpFilterContext* pCtxt, PHTTP_FILTER_RAW_DATA pRawData);
	virtual DWORD OnLog(CHttpFilterContext* pfc, PHTTP_FILTER_LOG pLog);
	virtual DWORD OnEndOfNetSession(CHttpFilterContext* pCtxt);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CJuneWebServerFilter)
	//}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNEWEBSERVER_H__513E3F31_FF2F_4E2B_A1F4_09DF866FAF05__INCLUDED)
