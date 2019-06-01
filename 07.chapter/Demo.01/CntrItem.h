// CntrItem.h : interface of the CDemoCntrItem class
//

#if !defined(AFX_CNTRITEM_H__DAC8CAEB_1E02_4F40_AE97_6860B35C26CE__INCLUDED_)
#define AFX_CNTRITEM_H__DAC8CAEB_1E02_4F40_AE97_6860B35C26CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDemoDoc;
class CDemoView;

class CDemoCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CDemoCntrItem)

// Constructors
public:
	CDemoCntrItem(REOBJECT* preo = NULL, CDemoDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CDemoDoc* GetDocument()
		{ return (CDemoDoc*)CRichEditCntrItem::GetDocument(); }
	CDemoView* GetActiveView()
		{ return (CDemoView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CDemoCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__DAC8CAEB_1E02_4F40_AE97_6860B35C26CE__INCLUDED_)
