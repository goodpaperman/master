#if !defined(AFX_WIZPROPERTYPAGE_H__16E7C727_2DE6_456C_A3C7_33EB7C66209D__INCLUDED_)
#define AFX_WIZPROPERTYPAGE_H__16E7C727_2DE6_456C_A3C7_33EB7C66209D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizPropertyPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizPropertyPage dialog


class CWizPropertySheet; 
class CWizPropertyPage : public CPropertyPage
{
    friend class CWizPropertySheet; 
	DECLARE_DYNCREATE(CWizPropertyPage)

// Construction
public:
	CWizPropertyPage();
    CWizPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0); 
    CWizPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption = 0); 
	~CWizPropertyPage();

    BOOL Enable(BOOL bEnable = TRUE); 
    BOOL IsEnabled(); 

// Dialog Data
	//{{AFX_DATA(CWizPropertyPage)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

protected:
    BOOL m_bEnabled; 
    CWizPropertySheet* m_pPropSheet; 

    void Init(); 
    virtual LRESULT GetNextPage(BOOL forward = TRUE); 

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizPropertyPage)
	public:
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZPROPERTYPAGE_H__16E7C727_2DE6_456C_A3C7_33EB7C66209D__INCLUDED_)
