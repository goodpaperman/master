#if !defined(AFX_JUNEDRAWINGCTL_H__40C93F4B_D07F_4152_9D07_D18990440072__INCLUDED_)
#define AFX_JUNEDRAWINGCTL_H__40C93F4B_D07F_4152_9D07_D18990440072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JuneDrawingCtl.h : Declaration of the CJuneDrawingCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl : See JuneDrawingCtl.cpp for implementation.

class CJuneDrawingCtrl : public COleControl
{
	DECLARE_DYNCREATE(CJuneDrawingCtrl)

// Constructor
public:
	CJuneDrawingCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJuneDrawingCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void FlashColor(CDC * pdc);
	BOOL IsInDrawingRegion(CPoint& point);
	void GetDrawRect(CRect* rc);
	~CJuneDrawingCtrl();

	DECLARE_OLECREATE_EX(CJuneDrawingCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CJuneDrawingCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CJuneDrawingCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CJuneDrawingCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CJuneDrawingCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CJuneDrawingCtrl)
	BOOL m_drawingShape;
	afx_msg void OnDrawingShapeChanged();
	OLE_COLOR m_flashColor;
	afx_msg void OnFlashColorChanged();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CJuneDrawingCtrl)
	void FireClickIn(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
		{FireEvent(eventidClickIn,EVENT_PARAM(VTS_XPOS_PIXELS  VTS_YPOS_PIXELS), x, y);}
	void FireClickOut()
		{FireEvent(eventidClickOut,EVENT_PARAM(VTS_NONE));}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CJuneDrawingCtrl)
	dispidDrawingShape = 1L,
	dispidFlashColor = 2L,
	eventidClickIn = 1L,
	eventidClickOut = 2L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNEDRAWINGCTL_H__40C93F4B_D07F_4152_9D07_D18990440072__INCLUDED)
