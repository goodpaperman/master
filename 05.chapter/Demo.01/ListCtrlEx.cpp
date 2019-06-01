// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx

CHeaderCtrlEx::CHeaderCtrlEx()
{
    m_pImageList = NULL; 
}

CHeaderCtrlEx::~CHeaderCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx message handlers

CImageList* CHeaderCtrlEx::SetImageList(CImageList* pImageList)
{
    CImageList* pPrevList = m_pImageList; 
    m_pImageList = pImageList; 
    return pPrevList; 
}

int CHeaderCtrlEx::GetItemImage(int nItem)
{
    int imageIndex; 
    if(m_mapImageIndex.Lookup(nItem, imageIndex))
        return imageIndex; 

    return -1; 
}

void CHeaderCtrlEx::SetItemImage(int nItem, int nImage)
{
    m_mapImageIndex[nItem] = nImage; 
    HD_ITEM hdi; 
    hdi.mask = HDI_FORMAT; 
    GetItem(nItem, &hdi); 
    hdi.fmt |= HDF_OWNERDRAW; 
    SetItem(nItem, &hdi); 
    Invalidate(); 
}

void CHeaderCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC dc; 
    dc.Attach(lpDIS->hDC); 
    CRect rect(lpDIS->rcItem); 
    int nSave = dc.SaveDC(); 

    CRgn rgn; 
    rgn.CreateRectRgnIndirect(&rect); 
    dc.SelectObject(&rgn); 
    rgn.DeleteObject(); 

    int nOffset = dc.GetTextExtent(_T(" "), 1).cx * 2; 
    int nIndex; 
    if(m_pImageList && m_mapImageIndex.Lookup(lpDIS->itemID, nIndex))
    {
        if(nIndex != -1)
        {
            m_pImageList->Draw(&dc, nIndex, CPoint(rect.left + nOffset, nOffset/3), ILD_TRANSPARENT); 
            IMAGEINFO ii; 
            if(m_pImageList->GetImageInfo(nIndex, &ii))
                rect.left += nOffset/2 + ii.rcImage.right - ii.rcImage.left; 
        }
    }

    TCHAR buf[256]; 
    HD_ITEM hdi; 
    hdi.mask = HDI_TEXT | HDI_FORMAT; 
    hdi.pszText = buf; 
    hdi.cchTextMax = 255; 
    GetItem(lpDIS->itemID, &hdi); 

    UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS; 
    if(hdi.fmt & HDF_CENTER)
        uFormat |= DT_CENTER; 
    else if(hdi.fmt & HDF_RIGHT)
        uFormat |= DT_RIGHT; 
    else 
        uFormat |= DT_LEFT; 

    if(lpDIS->itemState == ODS_SELECTED)
    {
        rect.left ++; 
        rect.top += 2; 
        rect.right ++; 
    }

    rect.left += nOffset; 
    rect.right -= nOffset; 

    if(rect.left < rect.right)
        dc.DrawText(buf, rect, uFormat); 

    dc.RestoreDC(nSave); 
    dc.Detach(); 
}
/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
    m_nHighlight = HIGHLIGHT_ALLCOLUMNS; 
    m_nHighlight = HIGHLIGHT_NORMAL; 
    m_nHighlight = HIGHLIGHT_ROW; 
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

void CListCtrlEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListCtrl::PreSubclassWindow();
    m_header.SubclassWindow(CListCtrl::GetHeaderCtrl()->GetSafeHwnd()); 
}

CHeaderCtrlEx* CListCtrlEx::GetHeaderCtrl()
{
    return &m_header; 
}

BOOL CListCtrlEx::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY* pHDN = (HD_NOTIFY*)lParam; 
    LPNMHDR pNH = (LPNMHDR)lParam; 
    if(wParam == 0 && pNH->code == NM_RCLICK)
    {
        CPoint pt(GetMessagePos()); 
        CPoint pt2(pt); 
        CHeaderCtrl* pHeader = CListCtrl::GetHeaderCtrl(); 
        pHeader->ScreenToClient(&pt); 

        int nIndex = -1; 
        CRect rect; 
        for(int i=0; pHeader->GetItemRect(i, &rect); i++)
        {
            if(rect.PtInRect(pt))
            {
                nIndex = i; 
                break; 
            }
        }

        if(nIndex >= 0)
        {
            TRACE("Right Hit Col: %d\n", nIndex); 
            CMenu menu; 
            menu.LoadMenu(IDR_MENU_HEADER); 
            CMenu* pSub = menu.GetSubMenu(0); 
            pSub->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt2.x, pt2.y, pHeader); 
            return TRUE; 
        }
    }

    switch(pNH->code)
    {
    case HDN_BEGINTRACKW:
    case HDN_BEGINTRACKA:
        // double click will change the item width to fit.
    case HDN_DIVIDERDBLCLICKW:
    case HDN_DIVIDERDBLCLICKA:
        //if(pHDN->iItem == 0)
        if(pHDN->pitem && pHDN->pitem->cxy > 80) 
        {
            *pResult = TRUE; 
            return TRUE; 
        }
    default:
        TRACE("Notify code = %d\n", pNH->code); 
        break; 
    }

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

int CListCtrlEx::SetItemRange(BOOL bSelect, int nFirstItem, int nLastItem)
{
    if(nFirstItem >= GetItemCount() || nLastItem >= GetItemCount())
        return 0; 

    int nItemsSelected = 0; 
    int nFlags = bSelect ? 0 : LVNI_SELECTED; 
    int nItem = nFirstItem - 1; 
    while((nItem = GetNextItem(nItem, nFlags)) >= 0 && nItem <= nLastItem)
    {
        nItemsSelected++; 
        SetItemState(nItem, bSelect ? LVIS_SELECTED : 0, LVIS_SELECTED); 
    }

    return nItemsSelected; 
}


void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC* pDC = CDC::FromHandle(lpDIS->hDC); 
    CRect rcItem(lpDIS->rcItem); 
    int nItem = lpDIS->itemID; 
    CImageList* pImageList; 
    int nSaveDC = pDC->SaveDC(); 

    LV_ITEM lvi; 
    lvi.mask = LVIF_IMAGE | LVIF_STATE; 
    lvi.iItem = nItem; 
    lvi.iSubItem = 0; 
    lvi.stateMask = 0xFFFF; 
    GetItem(&lvi); 

    BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) || 
        ((lvi.state & LVIS_SELECTED) && 
        ((GetFocus() == this) || (GetStyle() & LVS_SHOWSELALWAYS)))); 

    CRect rcBounds, rcLabel, rcIcon; 
    GetItemRect(nItem, rcBounds, LVIR_BOUNDS); 
    GetItemRect(nItem, rcLabel, LVIR_LABEL); 
    GetItemRect(nItem, rcIcon, LVIR_ICON); 
    CRect rcCol(rcBounds); 
    CString sLabel = GetItemText(nItem, 0); 

    int offset = pDC->GetTextExtent(_T(" "), 1).cx * 2; 
    CRect rcHighlight, rcWnd; 
    int nExt; 

    switch(m_nHighlight)
    {
    case HIGHLIGHT_NORMAL:
        nExt = pDC->GetOutputTextExtent(sLabel).cx + offset; 
        rcHighlight = rcLabel; 
        if(rcLabel.left + nExt < rcLabel.right)
            rcHighlight.right = rcLabel.left + nExt; 
        break; 
    case HIGHLIGHT_ALLCOLUMNS:
        rcHighlight = rcBounds; 
        rcHighlight.left = rcLabel.left; 
        break; 
    case HIGHLIGHT_ROW:
        GetClientRect(&rcWnd); 
        rcHighlight = rcBounds; 
        rcHighlight.left = rcLabel.left; 
        rcHighlight.right = rcWnd.right; 
        break; 
    default:
        rcHighlight = rcLabel; 
        break; 
    }

    if(bHighlight)
    {
        pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
        pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 
        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
    }
    else 
        pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_WINDOW))); 

    rcCol.right = rcCol.left + GetColumnWidth(0); 

    CRgn rgn; 
    rgn.CreateRectRgnIndirect(&rcCol); 
    pDC->SelectClipRgn(&rgn); 
    rgn.DeleteObject(); 

    if(lvi.state & LVIS_STATEIMAGEMASK)
    {
        int nImage = ((lvi.state & LVIS_STATEIMAGEMASK) >> 12) - 1; 
        pImageList = GetImageList(LVSIL_STATE); 
        if(pImageList)
        {
            pImageList->Draw(pDC, nImage, CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT); 
        }
    }

    pImageList = GetImageList(LVSIL_SMALL); 
    if(pImageList)
    {
        UINT nOvlImageMask = lvi.state & LVIS_OVERLAYMASK; 
        pImageList->Draw(pDC, lvi.iImage, CPoint(rcIcon.left, rcIcon.top), 
            (bHighlight ? ILD_BLEND50 : 0) | ILD_TRANSPARENT | nOvlImageMask); 
    }

    rcLabel.left += offset/2; 
    rcLabel.right -= offset; 
    pDC->DrawText(sLabel, -1, rcLabel, DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | 
        DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS); 

    LV_COLUMN lvc; 
    lvc.mask = LVCF_FMT | LVCF_WIDTH; 
    if(m_nHighlight == HIGHLIGHT_NORMAL)
    {
        pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT)); 
        pDC->SetBkColor(::GetSysColor(COLOR_WINDOW)); 
    }

    rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right : rcBounds.right; 
    rgn.CreateRectRgnIndirect(&rcBounds); 
    pDC->SelectClipRgn(&rgn); 

    for(int nCol = 1; GetColumn(nCol, &lvc); nCol++)
    {
        rcCol.left = rcCol.right; 
        rcCol.right += lvc.cx; 
        if(m_nHighlight == HIGHLIGHT_NORMAL)
            pDC->FillRect(rcCol, &CBrush(::GetSysColor(COLOR_WINDOW))); 

        sLabel = GetItemText(nItem, nCol); 
        if(sLabel.GetLength() == 0)
            continue; 

        UINT nJustify = DT_LEFT; 
        switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
        {
        case LVCFMT_RIGHT:
            nJustify = DT_RIGHT; 
            break; 
        case LVCFMT_CENTER:
            nJustify = DT_CENTER; 
            break; 
        default:
            break; 
        }

        rcLabel = rcCol; 
        rcLabel.left += offset; 
        rcLabel.right -= offset; 
        pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE |
            DT_NOPREFIX | DT_CENTER | DT_END_ELLIPSIS); 
    }

    if(lvi.state & LVIS_FOCUSED && (GetFocus() == this))
        pDC->DrawFocusRect(rcHighlight); 

    pDC->RestoreDC(nSaveDC); 
}

void CListCtrlEx::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(m_nHighlight == HIGHLIGHT_ROW && (GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
    {
        CRect rcBounds; 
        GetItemRect(0, rcBounds, LVIR_BOUNDS); 
        CRect rcClient; 
        GetClientRect(&rcClient); 
        if(rcBounds.right < rcClient.right)
        {
            CPaintDC dc(this); 
            CRect rcClip; 
            dc.GetClipBox(rcClip); 
            rcClip.left = min(rcBounds.right-1, rcClip.left); 
            rcClip.right = rcClient.right; 
            InvalidateRect(rcClip, FALSE); 
        }
    }

    CListCtrl::OnPaint(); 
	// Do not call CListCtrl::OnPaint() for painting messages
}

void CListCtrlEx::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	if(pNewWnd != NULL && pNewWnd->GetParent() != this)
        return; 

    if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
        RepaintSelectedItems(); 
}

void CListCtrlEx::OnSetFocus(CWnd* pOldWnd) 
{
	CListCtrl::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	//if(pOldWnd != NULL && pOldWnd->GetParent() == this)
    if(::GetParent(pOldWnd->GetSafeHwnd()) == m_hWnd) 
        return; 

    if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
        RepaintSelectedItems(); 
}

void CListCtrlEx::RepaintSelectedItems()
{
    CRect rcBounds, rcLabel; 
    int nItem = GetNextItem(-1, LVNI_FOCUSED); 
    if(nItem != -1)
    {
        GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
        GetItemRect(nItem, rcLabel, LVIR_LABEL); 
        rcBounds.left = rcLabel.left; 
        InvalidateRect(rcBounds, FALSE); 
    }

    if(!(GetStyle() & LVS_SHOWSELALWAYS))
    {
        for(nItem = GetNextItem(-1, LVNI_SELECTED); 
        nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
        {
            GetItemRect(nItem, rcBounds, LVIR_BOUNDS); 
            GetItemRect(nItem, rcLabel, LVIR_LABEL); 
            rcBounds.left = rcLabel.left; 
            InvalidateRect(rcBounds, FALSE); 
        }
    }

    UpdateWindow(); 
}

int CListCtrlEx::SetHighlightType(EHighlight hilite)
{
    int oldhilite = m_nHighlight; 
    if(hilite <= HIGHLIGHT_ROW)
    {
        m_nHighlight = hilite; 
        Invalidate(); 
    }

    return oldhilite; 
}

int CListCtrlEx::HitTestEx(CPoint& point, int* col) const 
{
    int column = 0; 
    int row = HitTest(point, NULL); 
    if(col)
        *col = 0; 

    if((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
        return row; 

    row = GetTopIndex(); 
    int bottom = row + GetCountPerPage(); 
    if(bottom > GetItemCount())
        bottom = GetItemCount(); 

    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0); //CListCtrl::GetHeaderCtrl(); 
    int nColumnCount = pHeader->GetItemCount(); 
    for(; row <= bottom; row++)
    {
        CRect rect; 
        GetItemRect(row, &rect, LVIR_BOUNDS); 
        if(rect.PtInRect(point))
        {
            for(column=0; column<nColumnCount; column++)
            {
                int colwidth = GetColumnWidth(column); 
                if(point.x >= rect.left && point.x <= (rect.left + colwidth))
                {
                    if(col)
                        *col = column; 
                    return row; 
                }
                rect.left += colwidth; 
            }
        }
    }

    return -1; 
}

CEdit* CListCtrlEx::EditSubLabel(int nItem, int nCol)
{
    if(!EnsureVisible(nItem, TRUE))
        return NULL; 

    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0); 
    int nColumnCount = pHeader->GetItemCount(); 
    if(nCol >= nColumnCount || GetColumnWidth(nCol) < 5)
        return NULL; 

    int offset = 0; 
    for(int i=0; i<nCol; i++)
        offset += GetColumnWidth(i); 

    CRect rect; 
    GetItemRect(nItem, &rect, LVIR_BOUNDS); 

    CRect rcClient; 
    GetClientRect(&rcClient); 
    if(offset + rect.left < 0 || offset + rect.left > rcClient.right)
    {
        CSize size; 
        size.cx = offset + rect.left; 
        size.cy = 0; 
        Scroll(size); 
        rect.left -= size.cx; 
    }

    LV_COLUMN lvcol; 
    lvcol.mask = LVCF_FMT; 
    GetColumn(nCol, &lvcol); 
    DWORD dwStyle; 
    if((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
        dwStyle = ES_LEFT; 
    else if((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
        dwStyle = ES_RIGHT; 
    else 
        dwStyle = ES_CENTER; 

    rect.left += offset + 4; 
    rect.right = rect.left + GetColumnWidth(nCol) - 3; 
    if(rect.right > rcClient.right)
        rect.right = rcClient.right; 

    dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL; 
    CEdit* pEdit = new CInPlaceEdit(nItem, nCol, GetItemText(nItem, nCol)); 
    pEdit->Create(dwStyle, rect, this, IDC_IPEDIT); 
    return pEdit; 
}
/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit

CInPlaceEdit::CInPlaceEdit(int iItem, int iSubItem, CString sInitText) : m_sInitText(sInitText) 
{
    m_iItem = iItem; 
    m_iSubItem = iSubItem; 
    m_bESC = FALSE; 
}

CInPlaceEdit::~CInPlaceEdit()
{
}


BEGIN_MESSAGE_MAP(CInPlaceEdit, CEdit)
	//{{AFX_MSG_MAP(CInPlaceEdit)
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_CHAR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInPlaceEdit message handlers

BOOL CInPlaceEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    if(pMsg->message == WM_KEYDOWN)
    {
    	if(pMsg->wParam == VK_RETURN || 
            pMsg->wParam == VK_DELETE || 
            pMsg->wParam == VK_ESCAPE || 
            GetKeyState(VK_CONTROL))
        {
            ::TranslateMessage(pMsg); 
            ::DispatchMessage(pMsg); 
            return TRUE; 
        }
    }
	return CEdit::PreTranslateMessage(pMsg);
}

void CInPlaceEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	CString str; 
    GetWindowText(str); 

    LV_DISPINFO dispinfo; 
    dispinfo.hdr.hwndFrom = GetParent()->m_hWnd; 
    dispinfo.hdr.idFrom = GetDlgCtrlID(); 
    dispinfo.hdr.code = LVN_ENDLABELEDIT; 
    dispinfo.item.mask = LVIF_TEXT; 
    dispinfo.item.iItem = m_iItem; 
    dispinfo.item.iSubItem = m_iSubItem; 
    dispinfo.item.pszText = m_bESC ? NULL : LPTSTR((LPCTSTR)str); 
    dispinfo.item.cchTextMax = str.GetLength(); 
    GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo); 
    DestroyWindow(); 
}

void CInPlaceEdit::OnNcDestroy() 
{
	CEdit::OnNcDestroy();
	
	// TODO: Add your message handler code here
	delete this; 
}

void CInPlaceEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == VK_ESCAPE || nChar == VK_RETURN)
    {
        if(nChar == VK_ESCAPE)
            m_bESC = TRUE; 

        GetParent()->SetFocus(); 
        return; 
    }

	CEdit::OnChar(nChar, nRepCnt, nFlags);

    CString str; 
    GetWindowText(str); 
    CWindowDC dc(this); 
    CFont* pFont = GetParent()->GetFont(); 
    CFont* pFontDC = dc.SelectObject(pFont); 
    CSize size = dc.GetTextExtent(str); 
    dc.SelectObject(pFontDC); 
    size.cx += 5; 

    CRect rect, parentrect; 
    GetClientRect(&rect); 
    GetParent()->GetClientRect(&parentrect); 

    ClientToScreen(&rect); 
    GetParent()->ScreenToClient(&rect); 

    if(size.cx > rect.Width())
    {
        if(size.cx + rect.left < parentrect.right)
            rect.right = rect.left + size.cx; 
        else 
            rect.right = parentrect.right; 

        MoveWindow(&rect); 
    }
}

int CInPlaceEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    CFont* font = GetParent()->GetFont(); 
    SetFont(font); 

    SetWindowText(m_sInitText); 
    SetFocus(); 
    SetSel(0, -1); 
	return 0;
}

void CListCtrlEx::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetFocus() != this)
        SetFocus(); 

	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CListCtrlEx::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(GetFocus() != this)
        SetFocus(); 

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CListCtrlEx::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	LV_ITEM* pItem = &pDispInfo->item; 
    
    if(pItem->pszText != NULL)
    {
        SetItemText(pItem->iItem, pItem->iSubItem, pItem->pszText); 
    }

	*pResult = 0;
}

void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int index;     
	CListCtrl::OnLButtonDown(nFlags, point);

    int column; 
    if((index = HitTestEx(point, &column)) != -1)
    {
        UINT flag = LVIS_FOCUSED; 
        if((GetItemState(index, flag) & flag) == flag && column > 0)
        {
            if(GetWindowLong(m_hWnd, GWL_STYLE) & LVS_EDITLABELS)
                EditSubLabel(index, column); 
        }
        else 
            SetItemState(index, LVIS_SELECTED | LVIS_FOCUSED, 
                        LVIS_SELECTED | LVIS_FOCUSED); 
    }
}
