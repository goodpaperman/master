// DemoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "CntrItem.h"
#include "DemoView.h"
#include "FormatBar.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CRichEditView)

BEGIN_MESSAGE_MAP(CDemoView, CRichEditView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_CHAR_COLOR, OnColorPick)
	ON_COMMAND(ID_CHAR_BOLD, OnCharBold)
	ON_UPDATE_COMMAND_UI(ID_CHAR_BOLD, OnUpdateCharBold)
	ON_COMMAND(ID_CHAR_ITALIC, OnCharItalic)
	ON_UPDATE_COMMAND_UI(ID_CHAR_ITALIC, OnUpdateCharItalic)
	ON_COMMAND(ID_CHAR_UNDERLINE, OnCharUnderline)
	ON_UPDATE_COMMAND_UI(ID_CHAR_UNDERLINE, OnUpdateCharUnderline)
	ON_COMMAND(ID_PARA_CENTER, OnParaCenter)
	ON_UPDATE_COMMAND_UI(ID_PARA_CENTER, OnUpdateParaCenter)
	ON_COMMAND(ID_PARA_LEFT, OnParaLeft)
	ON_UPDATE_COMMAND_UI(ID_PARA_LEFT, OnUpdateParaLeft)
	ON_COMMAND(ID_PARA_RIGHT, OnParaRight)
	ON_UPDATE_COMMAND_UI(ID_PARA_RIGHT, OnUpdateParaRight)
	ON_COMMAND(ID_INSERT_BULLET, OnBullet)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
    ON_NOTIFY_REFLECT(EN_PROTECTED, OnProtected) 
    ON_NOTIFY(FN_GETFORMAT, IDR_FORMATBAR, OnGetCharFormat) 
    ON_NOTIFY(FN_SETFORMAT, IDR_FORMATBAR, OnSetCharFormat)
    ON_NOTIFY(NM_RETURN, IDR_FORMATBAR, OnBarReturn) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here

}

CDemoView::~CDemoView()
{
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CDemoView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

    long eventmask = GetRichEditCtrl().GetEventMask() | ENM_PROTECTED; 
    GetRichEditCtrl().SetEventMask(eventmask); 

    SetWindowText("Ni \thao \tma?\tblha \tblha \tblha \tblha \tblha \tblha \tlbha \tbha \tblha \tblha \tblha \tblha... \t\n"
        "blha \tblhja \tblhal \tbhla \tblha \tblha \tblhab \tlahblahb \tlahb \talb \tlahb \tlahb \tlahblahb \tlablab \tla .\t"); 
    GetRichEditCtrl().SetSel(0, -1); 
    SetSelectionProtected(); 

    ////m_nWordWrap = WrapNone; 
    //m_nWordWrap = WrapToTargetDevice; 
    //WrapChanged(); 

    GetRichEditCtrl().SetTargetDevice(NULL, 1); 
    //GetRichEditCtrl().SetTargetDevice(NULL, 0); 
    //GetRichEditCtrl().SetTargetDevice(m_dcTarget, 100); 

    PARAFORMAT pf; 
    pf.cbSize = sizeof(PARAFORMAT); 
    pf.dwMask = PFM_TABSTOPS; 
    pf.cTabCount = MAX_TAB_STOPS; 
    for(int i=0; i<pf.cTabCount; i++)
        pf.rgxTabs[i] = (i+1) * 1440; // in twips, 1 inch = 1440 twips = 72 points.

    SetParaFormat(pf); 

    CString rtfPrefix, rtfPostfix; 
    //rtfPrefix = "{\\rtf1\\ansi\\deff0\\deftab720{\\fonttb1{\\f0\\froman "
    //    "Times New Roman;}}\n{\\colortb1\\red0\\green0\\blue0;}\n" 
    //    "\\deflang1033\\pard\\tx360\\tx720\\tx1080\\tx1440\\tx1800" 
    //    "\\tx2160\\tx2520\\tx2880\\tx3240\\tx3600\\tx3960\\tx4320" 
    //    "\\tx4680\\tx5040\\tx5400\\tx5760\\tx6120" 
    //    "\\tx6480\\plain\\f3\\fs20"; 
    
    rtfPrefix = "{\\rtf1\\ansi\\deff0\\deftab720\n\n" 
        "\\deflang1033\\pard\\tx360\\tx720\\tx1080\\tx1440\\tx1800" 
        "\\tx2160\\tx2520\\tx2880\\tx3240\\tx3600\\tx3960\\tx4320" 
        "\\tx4680\\tx5040\\tx5400\\tx5760\\tx6120" 
        "\\tx6480\\plain\\f3\\fs20"; 

    //rtfPostfix = "\n\\par }"; 
    rtfPostfix = "\n\\par }"; 

    CString rtfString = rtfPrefix + "\\b Bold, How are you OK?\\b0" + rtfPostfix; 
    EDITSTREAM es = { (DWORD)&rtfString, 0, EditStreamCallBack2}; 
    GetRichEditCtrl().StreamIn(SF_RTF | SFF_SELECTION, es); 
    //GetRichEditCtrl().SetSel(-1, -1); 
    //GetRichEditCtrl().ReplaceSel(rtfString); 
}

static DWORD CALLBACK EditStreamCallBack2 (DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
    CString* pstr = (CString*)dwCookie; 
    if(pstr->GetLength() < cb)
    {
        *pcb = pstr->GetLength(); 
        memcpy(pbBuff, (LPCSTR)*pstr, *pcb); 
        pstr->Empty(); 
    }
    else 
    {
        *pcb = cb; 
        memcpy(pbBuff, (LPCSTR)*pstr, *pcb); 
        *pstr = pstr->Right(pstr->GetLength() - cb); 
    }

    return 0; 
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView printing

BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CDemoView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

void CDemoView::OnProtected(NMHDR* pNMHDR, LRESULT* pResult)
{
    ENPROTECTED* pENPROTECTED = (ENPROTECTED*)pNMHDR; 
    if(pENPROTECTED->msg == WM_CHAR && pENPROTECTED->wParam == VK_SPACE)
        *pResult = TRUE; 
    else 
        *pResult = FALSE;
}

void CDemoView::SetSelectionProtected()
{
    CHARFORMAT cf; 
    cf.cbSize = sizeof(cf); 
    cf.dwMask = CFM_PROTECTED; 
    cf.dwEffects = CFE_PROTECTED; 
    GetRichEditCtrl().SetSelectionCharFormat(cf); 
}

void CDemoView::OnGetCharFormat(NMHDR* pNMHDR, LRESULT* pRes)
{
    ((CHARNMHDR*)pNMHDR)->cf = GetCharFormatSelection(); 
    *pRes = 1; 
}

void CDemoView::OnSetCharFormat(NMHDR* pNMHDR, LRESULT* pRes)
{
    SetCharFormat(((CHARNMHDR*)pNMHDR)->cf); 
    *pRes = 1; 
}

void CDemoView::OnBarReturn(NMHDR*, LRESULT*)
{
    SetFocus(); 
}

void CDemoView::OnColorPick() 
{
	// TODO: Add your command handler code here
    CColorDialog dlg; 
    if(dlg.DoModal() == IDOK)
        CRichEditView::OnColorPick(dlg.GetColor()); 
}

//void CDemoView::OnCharBold() 
//{
//    // TODO: Add your command handler code here
    
//}

//void CDemoView::OnUpdateCharBold(CCmdUI* pCmdUI) 
//{
//    // TODO: Add your command update UI handler code here
    
//}

//void CDemoView::OnCharItalic() 
//{
//    // TODO: Add your command handler code here
    
//}

//void CDemoView::OnUpdateCharItalic(CCmdUI* pCmdUI) 
//{
//    // TODO: Add your command update UI handler code here
    
//}

//void CDemoView::OnCharUnderline() 
//{
//    // TODO: Add your command handler code here
    
//}

//void CDemoView::OnUpdateCharUnderline(CCmdUI* pCmdUI) 
//{
//    // TODO: Add your command update UI handler code here
    
//}

//void CDemoView::OnParaCenter() 
//{
//    // TODO: Add your command handler code here
    
//}

//void CDemoView::OnUpdateParaCenter(CCmdUI* pCmdUI) 
//{
//    // TODO: Add your command update UI handler code here
    
//}

//void CDemoView::OnParaLeft() 
//{
//    // TODO: Add your command handler code here
    
//}

//void CDemoView::OnUpdateParaLeft(CCmdUI* pCmdUI) 
//{
//    // TODO: Add your command update UI handler code here
    
//}

//void CDemoView::OnParaRight() 
//{
//    // TODO: Add your command handler code here
    
//}

//void CDemoView::OnUpdateParaRight(CCmdUI* pCmdUI) 
//{
//    // TODO: Add your command update UI handler code here
//    CRichEditView::OnUpdateParaAlign(pCmdUI, 0); 
//}

//void CDemoView::OnInsertBullet() 
//{
//    // TODO: Add your command handler code here
    
//}
