// JuneDrawingCtl.cpp : Implementation of the CJuneDrawingCtrl ActiveX Control class.

#include "stdafx.h"
#include "JuneDrawing.h"
#include "JuneDrawingCtl.h"
#include "JuneDrawingPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CJuneDrawingCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJuneDrawingCtrl, COleControl)
	//{{AFX_MSG_MAP(CJuneDrawingCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CJuneDrawingCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CJuneDrawingCtrl)
	DISP_PROPERTY_NOTIFY(CJuneDrawingCtrl, "DrawingShape", m_drawingShape, OnDrawingShapeChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CJuneDrawingCtrl, "FlashColor", m_flashColor, OnFlashColorChanged, VT_COLOR)
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_CAPTION()
	DISP_STOCKPROP_FONT()
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CJuneDrawingCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CJuneDrawingCtrl, COleControl)
	//{{AFX_EVENT_MAP(CJuneDrawingCtrl)
	EVENT_CUSTOM("ClickIn", FireClickIn, VTS_XPOS_PIXELS  VTS_YPOS_PIXELS)
	EVENT_CUSTOM("ClickOut", FireClickOut, VTS_NONE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CJuneDrawingCtrl, 1)
	PROPPAGEID(CJuneDrawingPropPage::guid)
END_PROPPAGEIDS(CJuneDrawingCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJuneDrawingCtrl, "JUNEDRAWING.JuneDrawingCtrl.1",
	0xb24e6cdd, 0x2f0d, 0x4419, 0x8c, 0x35, 0xd8, 0x9b, 0xb6, 0x66, 0x19, 0x71)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CJuneDrawingCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DJuneDrawing =
		{ 0x94265535, 0x6fed, 0x4f0a, { 0x87, 0x8f, 0x40, 0xb0, 0xa8, 0xed, 0x46, 0x5c } };
const IID BASED_CODE IID_DJuneDrawingEvents =
		{ 0xf55227f5, 0xcc4d, 0x43c0, { 0xb2, 0xbd, 0xa7, 0x1e, 0xec, 0x73, 0x4b, 0x74 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwJuneDrawingOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CJuneDrawingCtrl, IDS_JUNEDRAWING, _dwJuneDrawingOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::CJuneDrawingCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CJuneDrawingCtrl

BOOL CJuneDrawingCtrl::CJuneDrawingCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_JUNEDRAWING,
			IDB_JUNEDRAWING,
			afxRegApartmentThreading,
			_dwJuneDrawingOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::CJuneDrawingCtrl - Constructor

CJuneDrawingCtrl::CJuneDrawingCtrl()
{
	InitializeIIDs(&IID_DJuneDrawing, &IID_DJuneDrawingEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::~CJuneDrawingCtrl - Destructor

CJuneDrawingCtrl::~CJuneDrawingCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::OnDraw - Drawing function

void CJuneDrawingCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
    //pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
    //pdc->Ellipse(rcBounds);

    CRect rc = rcBounds; 
    CBrush bkBrush(TranslateColor(GetBackColor())); 
    CBrush* pOldBrush = pdc->SelectObject(&bkBrush); 
    pdc->FillRect(rcBounds, &bkBrush); 

    if(m_drawingShape)
        GetDrawRect(&rc); 

    CPen* pOldPen = (CPen*)pdc->SelectStockObject(BLACK_PEN); 
    pdc->Ellipse(rc); 

    CFont* pOldFont = SelectStockFont(pdc); 
    TEXTMETRIC tm; 
    pdc->GetTextMetrics(&tm); 
    const CString& strCaption = InternalGetText(); 
    pdc->SetTextColor(TranslateColor(GetForeColor())); 
    pdc->SetBkMode(TRANSPARENT); 
    pdc->SetTextAlign(TA_CENTER | TA_TOP); 
    pdc->ExtTextOut((rc.left + rc.right)/2, (rc.top + rc.bottom - tm.tmHeight)/2, 
        ETO_CLIPPED, rc, strCaption, strCaption.GetLength(), NULL); 
    pdc->SelectObject(pOldFont); 
    pdc->SelectObject(pOldPen); 
    pdc->SelectObject(pOldBrush); 
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::DoPropExchange - Persistence support

void CJuneDrawingCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
    PX_Bool(pPX, _T("DrawingShape"), m_drawingShape, TRUE); 
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::OnResetState - Reset control to default state

void CJuneDrawingCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl::AboutBox - Display an "About" box to the user

void CJuneDrawingCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_JUNEDRAWING);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CJuneDrawingCtrl message handlers

void CJuneDrawingCtrl::OnDrawingShapeChanged() 
{
	// TODO: Add notification handler code
    InvalidateControl(); 
	SetModifiedFlag();
}

void CJuneDrawingCtrl::GetDrawRect(CRect *rc)
{
    int cx = rc->right - rc->left; 
    int cy = rc->bottom - rc->top; 
    if(cx > cy)
    {
        rc->left += (cx - cy)/2; 
        rc->right = rc->left + cy; 
    }
    else 
    {
        rc->top += (cy - cx)/2; 
        rc->bottom = rc->top + cx; 
    }
}

void CJuneDrawingCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pdc; 
    if(IsInDrawingRegion(point))
    {
        pdc = GetDC(); 
        FlashColor(pdc); 
        ReleaseDC(pdc); 
        FireClickIn(point.x, point.y); 
    }
    else 
        FireClickOut(); 
	
	COleControl::OnLButtonDown(nFlags, point);
}

void CJuneDrawingCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pdc; 
    if(IsInDrawingRegion(point))
    {
        pdc = GetDC(); 
        FlashColor(pdc); 
        ReleaseDC(pdc); 
    }

	COleControl::OnLButtonDblClk(nFlags, point);
}

void CJuneDrawingCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(IsInDrawingRegion(point))
        InvalidateControl(); 

	COleControl::OnLButtonUp(nFlags, point);
}

BOOL CJuneDrawingCtrl::IsInDrawingRegion(CPoint &point)
{
    CRect rc; 
    GetClientRect(&rc); 
    if(m_drawingShape)
        GetDrawRect(&rc); 

    double a = (rc.right - rc.left) / 2; 
    double b = (rc.bottom - rc.top) / 2; 

    double x = point.x - (rc.left + rc.right) / 2; 
    double y = point.y - (rc.top + rc.bottom) / 2; 

    return ((x*x)/(a*a) + (y*y)/(b*b) <= 1); 
}

void CJuneDrawingCtrl::OnFlashColorChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CJuneDrawingCtrl::FlashColor(CDC *pdc)
{
    CRect rc; 
    GetClientRect(&rc); 
    if(m_drawingShape)
        GetDrawRect(&rc); 

    CBrush flashBrush(TranslateColor(m_flashColor)); 
    CBrush* pOldBrush = pdc->SelectObject(&flashBrush); 
    CPen* pOldPen = (CPen*)pdc->SelectStockObject(BLACK_PEN); 
    pdc->Ellipse(rc); 
    pdc->SelectObject(pOldPen); 
    pdc->SelectObject(pOldBrush); 
}
