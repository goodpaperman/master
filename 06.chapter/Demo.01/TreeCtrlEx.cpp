// TreeCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "TreeCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

CTreeCtrlEx::CTreeCtrlEx()
{
    //m_imageState.m_hImageList = NULL; 
    m_bLDragging = FALSE; 
    m_pDragImage = NULL; 
    m_hitemDrag = m_hitemDrop = NULL; 
    m_nTimerID = 0; 
    m_timerticks = 0; 
    m_bRDragging = FALSE; 
    m_bRDragCanceled = FALSE; 

    m_hItemFirstSel = NULL; 
}

CTreeCtrlEx::~CTreeCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlEx, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeCtrlEx)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(TVN_BEGINRDRAG, OnBeginRDrag)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
    ON_COMMAND(ID_MOVEASCHILD, OnMoveAsChild) 
    ON_COMMAND(ID_MOVEASSIBLING, OnMoveAsSibling) 
    ON_COMMAND(ID_COPYASCHILD, OnCopyAsChild)
    ON_COMMAND(ID_COPYASSIBLING, OnCopyAsSibling) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx message handlers

void CTreeCtrlEx::ExpandBranchCompletely(HTREEITEM hti, UINT nFlag)
{
    if(ItemHasChildren(hti))
    {
        Expand(hti, nFlag); 
        hti = GetChildItem(hti); 
        do
        {
            ExpandBranchCompletely(hti, nFlag); 
        }while((hti = GetNextSiblingItem(hti)) != NULL); 
    }

    if(nFlag == TVE_EXPAND) 
        EnsureVisible(GetSelectedItem()); 
}

void CTreeCtrlEx::ExpandAll(UINT nFlag)
{
    HTREEITEM hti = GetRootItem(); 
    do
    {
        ExpandBranchCompletely(hti, nFlag); 
    }while((hti = GetNextSiblingItem(hti)) != NULL); 

    if(nFlag == TVE_EXPAND)
        EnsureVisible(GetRootItem()); 
}

HTREEITEM CTreeCtrlEx::GetLastItem(HTREEITEM hItem)
{
    HTREEITEM htiNext; 
    if(hItem == NULL)
    {
        htiNext = GetRootItem(); 
        while(htiNext)
        {
            hItem = htiNext; 
            htiNext = GetNextSiblingItem(htiNext); 
        }
    }

    while(ItemHasChildren(hItem))
    {
        htiNext = GetChildItem(hItem); 
        while(htiNext)
        {
            hItem = htiNext; 
            htiNext = GetNextSiblingItem(htiNext); 
        }
    }

    return hItem; 
}

HTREEITEM CTreeCtrlEx::GetNextItem(HTREEITEM hItem)
{
    HTREEITEM hti; 
    if(ItemHasChildren(hItem))
        return GetChildItem(hItem); 
    else 
    {
        while((hti = GetNextSiblingItem(hItem)) == NULL)
        {
            if((hItem = GetParentItem(hItem)) == NULL)
                return NULL; 
        }
    }

    return hti; 
}

HTREEITEM CTreeCtrlEx::GetPrevItem(HTREEITEM hItem)
{
    HTREEITEM hti; 
    hti = GetPrevSiblingItem(hItem); 
    if(hti == NULL)
        hti = GetParentItem(hItem); 
    else 
        hti = GetLastItem(hti); 

    return hti; 
}

HTREEITEM CTreeCtrlEx::FindItem(CString& str, BOOL bCaseSensitive/*=FALSE*/, 
                                BOOL bDownDir/*=TRUE*/, BOOL bWholeWord/*=FALSE*/, HTREEITEM hItem/*=NULL*/)
{
    int nLen = str.GetLength(); 
    if(nLen == 0)
        return NULL; 

    HTREEITEM htiSel = hItem ? hItem : GetSelectedItem(); 
    HTREEITEM htiCur = bDownDir ? GetNextItem(htiSel) : GetPrevItem(htiSel); 
    CString sSearch = str; 
    if(htiCur == NULL)
    {
        if(bDownDir)
            htiCur = GetRootItem(); 
        else 
            htiCur = GetLastItem(NULL); 
    }

    if(!bCaseSensitive)
        sSearch.MakeLower(); 

    while(htiCur && htiCur != htiSel)
    {
        CString sItemText = GetItemText(htiCur); 
        if(!bCaseSensitive)
            sItemText.MakeLower(); 

        int n; 
        while((n = sItemText.Find(sSearch)) != -1)
        {
            if(bWholeWord)
            {
                if(n != 0)
                {
                    if(isalpha(sItemText[n-1]) || sItemText[n-1] == '_')
                    {
                        sItemText = sItemText.Right(sItemText.GetLength()-n-nLen); 
                        continue; 
                    }
                }

                if(sItemText.GetLength() > n+nLen && (isalpha(sItemText[n+nLen]) || sItemText[n+nLen] == '_'))
                {
                    sItemText = sItemText.Right(sItemText.GetLength()-n-sSearch.GetLength()); 
                    continue; 
                }
            }

            if(IsFindValid(htiCur))
                return htiCur; 
            else 
                break; 
        }

        htiCur = bDownDir ? GetNextItem(htiCur) : GetPrevItem(htiCur); 
        if(htiCur == NULL)
        {
            if(bDownDir)
                htiCur = GetRootItem(); 
            else 
                htiCur = GetLastItem(NULL); 
        }
    }

    return NULL; 
}

BOOL CTreeCtrlEx::IsFindValid(HTREEITEM)
{
    return TRUE; 
}

HTREEITEM CTreeCtrlEx::FindItemData(DWORD lparam, BOOL bDownDir/*=TRUE*/, HTREEITEM hItem/*=NULL*/)
{
    HTREEITEM htiSel = hItem ? hItem : GetSelectedItem(); 
    HTREEITEM htiCur = bDownDir ? GetNextItem(htiSel) : GetPrevItem(htiSel); 
    if(htiCur == NULL)
    {
        if(bDownDir)
            htiCur = GetRootItem(); 
        else 
            htiCur = GetLastItem(NULL); 
    }

    while(htiCur && htiCur != htiSel)
    {
        DWORD sItemData = GetItemData(htiCur); 
        if(sItemData == lparam)
            return htiCur; 

        htiCur = bDownDir ? GetNextItem(htiCur) : GetPrevItem(htiCur); 
        if(htiCur == NULL)
        {
            if(bDownDir)
                htiCur = GetRootItem(); 
            else 
                htiCur = GetLastItem(NULL); 
        }
    }

    return NULL; 
}

HTREEITEM CTreeCtrlEx::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter/*=TVI_LAST*/)
{
    TV_INSERTSTRUCT tvstruct; 
    HTREEITEM hNewItem; 
    CString sText; 

    tvstruct.item.hItem = hItem; 
    tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
    GetItem(&tvstruct.item); 
    sText = GetItemText(hItem); 
    tvstruct.item.cchTextMax = sText.GetLength(); 
    tvstruct.item.pszText = sText.LockBuffer(); 
    tvstruct.hParent = htiNewParent; 
    tvstruct.hInsertAfter = htiAfter; 
    tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT; 
    hNewItem = InsertItem(&tvstruct); 
    sText.ReleaseBuffer(); 

    SetItemData(hNewItem, GetItemData(hItem)); 
    SetItemState(hNewItem, GetItemState(hItem, TVIS_STATEIMAGEMASK), TVIS_STATEIMAGEMASK); 
    OnItemCopied(hItem, hNewItem); 
    return hNewItem; 
}

void CTreeCtrlEx::OnItemCopied(HTREEITEM hItem, HTREEITEM hNewItem)
{
}

HTREEITEM CTreeCtrlEx::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter/*=TVI_LAST*/)
{
    HTREEITEM hChild; 
    HTREEITEM hNewItem = CopyItem(htiBranch, htiNewParent, htiAfter); 
    hChild = GetChildItem(htiBranch); 
    while(hChild != NULL)
    {
        CopyBranch(hChild, hNewItem); 
        hChild = GetNextSiblingItem(hChild); 
    }

    return hNewItem; 
}


void CTreeCtrlEx::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here    	
	*pResult = 0;

    m_hitemDrag = pNMTreeView->itemNew.hItem; 
    m_hitemDrop = NULL; 
    m_pDragImage = CreateDragImage(m_hitemDrag); 
    if(m_pDragImage == NULL)
        return; 

    m_bLDragging = TRUE; 
    m_pDragImage->BeginDrag(0, CPoint(-15, -15)); 
    POINT pt = pNMTreeView->ptDrag; 
    ClientToScreen(&pt); 
    m_pDragImage->DragEnter(NULL, pt); 
    SetCapture(); 

    m_nTimerID = SetTimer(1, 75, NULL);
}

void CTreeCtrlEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	HTREEITEM hitem; 
    UINT flags; 
    if(m_bLDragging)
    {
        POINT pt = point; 
        ClientToScreen(&pt); 
        CImageList::DragMove(pt); 
        if((hitem = HitTest(point, &flags)) != NULL)
        {
            CImageList::DragShowNolock(FALSE); 
            SelectDropTarget(hitem); 
            m_hitemDrop = hitem; 
            CImageList::DragShowNolock(TRUE); 
        }
    }
    else if(m_bRDragging)
    {
        POINT pt = point; 
        ClientToScreen(&pt); 
        CImageList::DragMove(pt); 
        if((hitem = HitTest(point, &flags)) != NULL)
        {
            CImageList::DragShowNolock(FALSE); 
            SelectDropTarget(hitem); 
            m_hitemDrop = hitem; 
            CImageList::DragShowNolock(TRUE); 
        }
    }

	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CTreeCtrlEx::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CTreeCtrl::OnLButtonUp(nFlags, point);

    if(m_bLDragging)
    {
        m_bLDragging = FALSE; 
        CImageList::DragLeave(this); 
        CImageList::EndDrag(); 
        ReleaseCapture(); 
        delete m_pDragImage; 
        KillTimer(m_nTimerID); 

        SelectDropTarget(NULL); 
        if(m_hitemDrag == m_hitemDrop)
            return; 

        HTREEITEM htiParent = m_hitemDrop; 
        while((htiParent = GetParentItem(htiParent)) != NULL)
        {
            if(htiParent == m_hitemDrag)
                return; 
        }

        Expand(m_hitemDrop, TVE_EXPAND); 
        HTREEITEM htiNew = CopyBranch(m_hitemDrag, m_hitemDrop, TVI_LAST); 
        DeleteItem(m_hitemDrag); 
        SelectItem(htiNew); 
    }
}

void CTreeCtrlEx::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent != m_nTimerID || !m_bLDragging)
    {
        CTreeCtrl::OnTimer(nIDEvent);
        return; 
    }

    m_timerticks++; 
    POINT pt; 
    GetCursorPos(&pt); 

    RECT rect; 
    GetClientRect(&rect); 
    ClientToScreen(&rect); 
    CImageList::DragMove(pt); 
    HTREEITEM hitem = GetFirstVisibleItem(); 
    if(pt.y < rect.top + 10)
    {
        int slowscroll = 6 - (rect.top + 10 - pt.y) / 20; 
        if((m_timerticks % (slowscroll > 0 ? slowscroll : 1) == 0))
        {
            CImageList::DragShowNolock(FALSE); 
            SendMessage(WM_VSCROLL, SB_LINEUP); 
            SelectDropTarget(hitem); 
            m_hitemDrop = hitem; 
            CImageList::DragShowNolock(TRUE); 
        }
    }
    else if(pt.y > rect.bottom - 10)
    {
        int slowscroll = 6 - (pt.y - rect.bottom + 10) / 20; 
        if((m_timerticks % (slowscroll > 0 ? slowscroll : 1)) == 0)
        {
            CImageList::DragShowNolock(FALSE); 
            SendMessage(WM_VSCROLL, SB_LINEDOWN); 
            int nCount = GetVisibleCount(); 
            for(int i=0; i<nCount-1; i++)
                hitem = GetNextVisibleItem(hitem); 

            if(hitem)
                SelectDropTarget(hitem); 

            m_hitemDrop = hitem; 
            CImageList::DragShowNolock(TRUE); 
        }
    }
}

void CTreeCtrlEx::OnBeginRDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here	
	*pResult = 0;

    CPoint ptAction; 
    GetCursorPos(&ptAction); 
    ScreenToClient(&ptAction); 
    m_bRDragging = TRUE; 
    m_bRDragCanceled = FALSE; 
    m_hitemDrag = pNMTreeView->itemNew.hItem; 
    m_hitemDrop = NULL; 
    m_pDragImage = CreateDragImage(m_hitemDrag); 
    m_pDragImage->BeginDrag(0, CPoint(10, -15)); 
    SelectDropTarget(NULL); 
    m_pDragImage->DragEnter(NULL, ptAction); 
    SetCapture(); 
}

HMENU CTreeCtrlEx::GetRDragMenu()
{
    CMenu menu; 
    menu.CreatePopupMenu(); 
    menu.AppendMenu(MF_STRING, ID_MOVEASCHILD, _T("Move As Child")); 
    menu.AppendMenu(MF_STRING, ID_MOVEASSIBLING, _T("Move As Sibling")); 
    menu.AppendMenu(MF_STRING, ID_COPYASCHILD, _T("Copy As Child")); 
    menu.AppendMenu(MF_STRING, ID_COPYASSIBLING, _T("Copy As Sibling")); 
    return menu.Detach(); 
}

void CTreeCtrlEx::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bRDragging)
    {
        m_bRDragging = FALSE; 
        CImageList::DragLeave(this); 
        CImageList::EndDrag(); 
        ReleaseCapture(); 
        delete m_pDragImage; 
        if(m_hitemDrag == m_hitemDrop)
            return; 

        CMenu menu; 
        menu.Attach(GetRDragMenu()); 
        if(menu.GetSafeHmenu() == NULL)
            return; 

        ClientToScreen(&point); 
        menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this); 
        SelectDropTarget(NULL); 
    }
    else 
        CTreeCtrl::OnRButtonUp(nFlags, point);
}

void CTreeCtrlEx::OnMoveAsChild()
{
    HTREEITEM htiParent = m_hitemDrop; 
    while((htiParent = GetParentItem(htiParent)) != NULL)
        if(htiParent == m_hitemDrag)
            return; 

    Expand(m_hitemDrop, TVE_EXPAND); 
    HTREEITEM htiNew = CopyBranch(m_hitemDrag, m_hitemDrop, TVI_LAST); 
    DeleteItem(m_hitemDrag); 
    SelectItem(htiNew); 
}

void CTreeCtrlEx::OnMoveAsSibling()
{
    HTREEITEM htiParent = m_hitemDrop; 
    while((htiParent = GetParentItem(htiParent)) != NULL)
        if(htiParent == m_hitemDrag)
            return; 

    HTREEITEM htiNew = CopyBranch(m_hitemDrag, GetParentItem(m_hitemDrop), m_hitemDrop); 
    DeleteItem(m_hitemDrag); 
    SelectItem(htiNew); 
}

void CTreeCtrlEx::OnCopyAsChild()
{
    HTREEITEM htiParent = m_hitemDrop; 
    while((htiParent = GetParentItem(htiParent)) != NULL)
        if(htiParent == m_hitemDrag)
            return; 

    HTREEITEM htiNew = CopyBranch(m_hitemDrag, m_hitemDrop, TVI_LAST); 
}

void CTreeCtrlEx::OnCopyAsSibling()
{
    HTREEITEM htiParent = m_hitemDrop; 
    while((htiParent = GetParentItem(htiParent)) != NULL)
        if(htiParent == m_hitemDrag)
            return; 

    HTREEITEM htiNew = CopyBranch(m_hitemDrag, GetParentItem(m_hitemDrop), m_hitemDrop); 
}

void CTreeCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    if(nFlags & MK_CONTROL)
    {
        UINT flag; 
        HTREEITEM hItem = HitTest(point, &flag); 
        if(hItem)
        {
            UINT uNewSelState = GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED ? 0 : TVIS_SELECTED; 
            HTREEITEM hItemOld = GetSelectedItem(); 
            UINT uOldSelState = hItemOld ? GetItemState(hItemOld, TVIS_SELECTED) : 0 ; 
            if(GetSelectedItem() == hItem)
                SelectItem(NULL); 

            CTreeCtrl::OnLButtonDown(nFlags, point); 
            SetItemState(hItem, uNewSelState, TVIS_SELECTED); 
            if(hItemOld && hItemOld != hItem)
                SetItemState(hItemOld, uOldSelState, TVIS_SELECTED); 

            m_hItemFirstSel = NULL; 
            return; 
        }
    }
    else if(nFlags & MK_SHIFT)
    {
        UINT flag; 
        HTREEITEM hItem = HitTest(point, &flag); 
        if(!m_hItemFirstSel)
            m_hItemFirstSel = GetSelectedItem(); 

        if(GetSelectedItem() == hItem)
            SelectItem(NULL); 

        CTreeCtrl::OnLButtonDown(nFlags, point); 
        if(m_hItemFirstSel)
        {
            SelectItems(m_hItemFirstSel, hItem); 
            return; 
        }
    }
    else 
    {
        ClearSelection(); 
        m_hItemFirstSel = NULL; 
    }

    UINT flags; 
    HTREEITEM hti = HitTest(point, &flags); 
    if(flags & TVHT_ONITEMSTATEICON)
    {
        //int iImage = GetItemState(hti, TVIS_STATEIMAGEMASK) >> 12; 
        //SetItemState(hti, INDEXTOSTATEIMAGEMASK(iImage == 1 ? 2 : 1), TVIS_STATEIMAGEMASK); 
        SetCheck(hti, TOGGLE); 
    }

	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CTreeCtrlEx::ClearSelection()
{
    for(HTREEITEM hItem = GetRootItem(); hItem != NULL; hItem = GetNextItem(hItem))
        if(GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED)
            SetItemState(hItem, 0, TVIS_SELECTED); 
}

BOOL CTreeCtrlEx::SelectItems(HTREEITEM hItemFrom, HTREEITEM hItemTo)
{
    HTREEITEM hItem = GetRootItem(); 
    while(hItem && hItem != hItemFrom && hItem != hItemTo)
    {
        hItem = GetNextVisibleItem(hItem); 
        SetItemState(hItem, 0, TVIS_SELECTED); 
    }

    if(!hItem)
        return FALSE; 

    SelectItem(hItemTo); 
    if(hItem == hItemTo)
    {
        hItemTo = hItemFrom; 
        hItemFrom = hItem; 
    }

    BOOL bSelect = TRUE; 
    while(hItem)
    {
        SetItemState(hItem, bSelect ? TVIS_SELECTED : 0, TVIS_SELECTED); 
        if(hItem == hItemTo)
            bSelect = FALSE; 

        hItem = GetNextVisibleItem(hItem); 
    }

    return TRUE; 
}

void CTreeCtrlEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if((nChar == VK_UP || nChar == VK_DOWN) && GetKeyState(VK_SHIFT) & 0x8000)
    {
        if(!m_hItemFirstSel)
        {
            m_hItemFirstSel = GetSelectedItem(); 
            ClearSelection(); 
        }

        HTREEITEM hItemPrevSel = GetSelectedItem(); 
        HTREEITEM hItemNext; 
        if(nChar == VK_UP)
            hItemNext = GetPrevVisibleItem(hItemPrevSel); 
        else 
            hItemNext = GetNextVisibleItem(hItemPrevSel); 

        if(hItemNext)
        {
            BOOL bReselect = !(GetItemState(hItemNext, TVIS_SELECTED) & TVIS_SELECTED); 
            SelectItem(hItemNext); 
            if(bReselect)
                SetItemState(hItemPrevSel, TVIS_SELECTED, TVIS_SELECTED);
        }

        return; 
    }
    else if(nChar >= VK_SPACE)
    {
        m_hItemFirstSel = NULL; 
        ClearSelection(); 

        if(nChar == VK_SPACE)
        {
            HTREEITEM hti = GetSelectedItem(); 
            //int iImage = GetItemState(hti, TVIS_STATEIMAGEMASK) >> 12; 
            //SetItemState(hti, INDEXTOSTATEIMAGEMASK(iImage == 1 ? 2 : 1), TVIS_STATEIMAGEMASK); 
            SetCheck(hti, TOGGLE);
        }
    }

	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

HTREEITEM CTreeCtrlEx::GetFirstSelectedItem()
{
    for(HTREEITEM hItem = GetRootItem(); hItem != NULL; hItem = GetNextItem(hItem))
        if(GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED)
            return hItem; 

    return NULL; 
}

HTREEITEM CTreeCtrlEx::GetNextSelectedItem(HTREEITEM hItem)
{
    for(hItem = GetNextItem(hItem); hItem != NULL; hItem = GetNextItem(hItem))
        if(GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED)
            return hItem; 

    return NULL; 
}

HTREEITEM CTreeCtrlEx::GetPrevSelectedItem(HTREEITEM hItem)
{
    for(hItem = GetPrevItem(hItem); hItem != NULL; hItem = GetPrevItem(hItem))
        if(GetItemState(hItem, TVIS_SELECTED) & TVIS_SELECTED)
            return hItem; 

    return NULL; 
}

BOOL CTreeCtrlEx::IsItemChecked(HTREEITEM hItem)
{
    //return GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12 == 2; 
    int iImage = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12; 
    return iImage == CHECKED || iImage == FULL_CHECKED; 
}

HTREEITEM CTreeCtrlEx::GetFirstCheckedItem()
{
    //for(HTREEITEM hItem = GetRootItem(); hItem != NULL; hItem = GetNextItem(hItem))
    //    if(IsItemChecked(hItem))
    //        return hItem; 

    //return NULL; 

    for(HTREEITEM hItem = GetRootItem(); hItem != NULL; )
    {
        int iImage = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12; 
        if(iImage == CHECKED || iImage == FULL_CHECKED)
            return hItem; 

        if(iImage != CHILD_CHECKED)
        {
            HTREEITEM hti = CTreeCtrl::GetNextItem(hItem, TVGN_NEXT); 
            if(hti == NULL)
                hItem = GetNextItem(hItem); 
            else 
                hItem = hti; 
        }
        else 
            hItem = GetNextItem(hItem); 
    }

    return NULL; 
}

HTREEITEM CTreeCtrlEx::GetNextCheckedItem(HTREEITEM hItem)
{
    //for(hItem = GetNextItem(hItem); hItem != NULL; hItem = GetNextItem(hItem))
    //    if(IsItemChecked(hItem))
    //        return hItem; 

    //return NULL; 

    hItem = GetNextItem(hItem); 
    while(hItem != NULL)
    {
        int iImage = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12; 
        if(iImage == CHECKED || iImage == FULL_CHECKED)
            return hItem; 

        if(iImage != CHILD_CHECKED)
        {
            HTREEITEM hti = CTreeCtrl::GetNextItem(hItem, TVGN_NEXT); 
            if(hti == NULL)
                hItem = GetNextItem(hItem); 
            else 
                hItem = hti; 
        }
        else 
            hItem = GetNextItem(hItem); 
    }

    return NULL; 
}

HTREEITEM CTreeCtrlEx::GetPrevCheckedItem(HTREEITEM hItem)
{
    for(hItem = GetPrevItem(hItem); hItem != NULL; hItem = GetPrevItem(hItem))
        if(IsItemChecked(hItem))
            return hItem; 

    return NULL; 
}

BOOL CTreeCtrlEx::SetCheck(HTREEITEM hItem, CheckType nCheck)
{
    if(hItem == NULL)
        return FALSE; 

    UINT nState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12; 
    if(nCheck == CHECK)
    {
        if(nState == CHECKED || nState == FULL_CHECKED)
            return TRUE; 

        switch(nState)
        {
        case UNCHECKED:
            nState = CHECKED; 
            break; 
        case CHILD_CHECKED:
            nState = FULL_CHECKED; 
            break; 
        }
    }
    else if(nCheck == UNCHECK)
    {
        if(nState == UNCHECKED || nState == CHILD_CHECKED)
            return TRUE; 

        switch(nState)
        {
        case CHECKED:
            nState = UNCHECKED; 
            break; 
        case FULL_CHECKED:
            nState = CHILD_CHECKED; 
            break; 
        }
    }
    else if(nCheck == TOGGLE)
    {
        switch(nState)
        {
        case UNCHECKED:
            nState = CHECKED; 
            break; 
        case CHECKED:
            nState = UNCHECKED; 
            break; 
        case CHILD_CHECKED:
            nState = FULL_CHECKED; 
            break; 
        case FULL_CHECKED:
            nState = CHILD_CHECKED; 
            break; 
        }
    }
    else if(nCheck == REFRESH)
    {
        BOOL bChildSelected = FALSE;
        HTREEITEM htiChild = GetChildItem(hItem); 
        while(htiChild)
        {
            UINT nChildState = GetItemState(htiChild, TVIS_STATEIMAGEMASK) >> 12; 
            if(nChildState != UNCHECKED && nChildState != NOSTATE)
            {
                bChildSelected = TRUE; 
                break; 
            }

            htiChild = CTreeCtrl::GetNextItem(htiChild, TVGN_NEXT); 
        }

        if(bChildSelected)
        {
            if(nState == CHECKED)
                nState = FULL_CHECKED; 
            else if(nState == UNCHECKED)
                nState = CHILD_CHECKED; 
        }
        else 
        {
            if(nState == FULL_CHECKED)
                nState = CHECKED; 
            else if(nState == CHILD_CHECKED)
                nState = UNCHECKED; 
        }
    }

    SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK); 
    if(nState == CHECKED || (nCheck == REFRESH && (nState == FULL_CHECKED || nState == CHILD_CHECKED)))
    {
        while((hItem = GetParentItem(hItem)) != NULL)
        {
            nState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12; 
            if(nState == UNCHECKED)
                SetItemState(hItem, INDEXTOSTATEIMAGEMASK(CHILD_CHECKED), TVIS_STATEIMAGEMASK); 
            else if(nState == CHECKED)
                SetItemState(hItem, INDEXTOSTATEIMAGEMASK(FULL_CHECKED), TVIS_STATEIMAGEMASK); 
        }
    }
    else if(nState == UNCHECKED)
    {
        while((hItem = GetParentItem(hItem)) != NULL)
        {
            BOOL bChildSelected = FALSE; 
            HTREEITEM htiChild = GetChildItem(hItem); 
            while(htiChild)
            {
                UINT nChildState = GetItemState(htiChild, TVIS_STATEIMAGEMASK) >> 12; 
                if(nChildState != UNCHECKED && nChildState != NOSTATE)
                {
                    bChildSelected = TRUE; 
                    break; 
                }

                htiChild = CTreeCtrl::GetNextItem(htiChild, TVGN_NEXT); 
            }

            if(bChildSelected)
                break; 
            else 
            {
                UINT nParentState = GetItemState(hItem, TVIS_STATEIMAGEMASK) >> 12; 
                if(nParentState == CHILD_CHECKED)
                    SetItemState(hItem, INDEXTOSTATEIMAGEMASK(UNCHECKED), TVIS_STATEIMAGEMASK); 
                else if(nParentState == FULL_CHECKED)
                    SetItemState(hItem, INDEXTOSTATEIMAGEMASK(CHECKED), TVIS_STATEIMAGEMASK); 
            }
        }
    }

    return TRUE; 
}



void CTreeCtrlEx::SetItemFont(HTREEITEM hItem, LOGFONT& logfont)
{
    Color_Font cf; 
    if(!m_mapColorFont.Lookup(hItem, cf))
        cf.color = (COLORREF)-1; 
    cf.logfont = logfont; 
    m_mapColorFont[hItem] = cf; 
}

void CTreeCtrlEx::SetItemBold(HTREEITEM hItem, BOOL bBold)
{
    SetItemState(hItem, bBold ? TVIS_BOLD : 0, TVIS_BOLD); 
}

void CTreeCtrlEx::SetItemColor(HTREEITEM hItem, COLORREF color)
{
    Color_Font cf; 
    if(!m_mapColorFont.Lookup(hItem, cf))
        cf.logfont.lfFaceName[0] = '\0'; 
    cf.color = color; 
    m_mapColorFont[hItem] = cf; 
}

BOOL CTreeCtrlEx::GetItemFont(HTREEITEM hItem, LOGFONT* plogfont)
{
    Color_Font cf; 
    if(!m_mapColorFont.Lookup(hItem, cf))
        return FALSE; 

    if(cf.logfont.lfFaceName[0] == '\0')
        return FALSE; 

    *plogfont = cf.logfont; 
    return TRUE; 
}

BOOL CTreeCtrlEx::GetItemBold(HTREEITEM hItem)
{
    return GetItemState(hItem, TVIS_BOLD) & TVIS_BOLD; 
}

COLORREF CTreeCtrlEx::GetItemColor(HTREEITEM hItem)
{
    Color_Font cf; 
    if(!m_mapColorFont.Lookup(hItem, cf))
        return (COLORREF)-1; 

    return cf.color; 
}


void CTreeCtrlEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    CDC memDC; 
    memDC.CreateCompatibleDC(&dc); 
    CRect rcClip, rcClient; 
    dc.GetClipBox(&rcClip); 
    GetClientRect(&rcClient); 

    CBitmap bitmap; 
    bitmap.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height()); 
    memDC.SelectObject(&bitmap); 

    CRgn rgn;
    rgn.CreateRectRgnIndirect(&rcClip); 
    memDC.SelectClipRgn(&rgn); 
    rgn.DeleteObject(); 
    // following statement is added by me, yunhai.
    rcClip = rcClient; 

    CWnd::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0); 
    HTREEITEM hItem = GetFirstVisibleItem(); 
    int n = GetVisibleCount() + 1; 
    while(hItem && n--)
    {
        CRect rect; 
        UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED; 
        Color_Font cf; 
        if(!(GetItemState(hItem, selflag) & selflag) && m_mapColorFont.Lookup(hItem, cf))
        {
            CFont* pFontDC; 
            CFont fontDC; 
            LOGFONT logfont; 
            if(cf.logfont.lfFaceName[0] != '\0')
                logfont = cf.logfont; 
            else 
            {
                CFont* pFont = GetFont(); 
                pFont->GetLogFont(&logfont); 
            }

            if(GetItemBold(hItem))
                logfont.lfWeight = 700; 

            fontDC.CreateFontIndirect(&logfont); 
            pFontDC = memDC.SelectObject(&fontDC); 
            if(cf.color != (COLORREF)-1)
                memDC.SetTextColor(cf.color); 

            CString sItem = GetItemText(hItem); 
            GetItemRect(hItem, &rect, TRUE);
            memDC.SetBkColor(GetSysColor(COLOR_WINDOW)); 
            memDC.TextOut(rect.left + 2, rect.top + 1, sItem); 
            memDC.SelectObject(pFontDC);             
        }

        hItem = GetNextVisibleItem(hItem); 
    }
    
    if(m_bitmap.m_hObject != NULL)
    {
        CDC maskDC; 
        maskDC.CreateCompatibleDC(&dc); 
        CBitmap maskBitmap; 
        maskBitmap.CreateBitmap(rcClip.Width(), rcClip.Height(), 1, 1, NULL); 
        maskDC.SelectObject(&maskBitmap);
        memDC.SetBkColor(::GetSysColor(COLOR_WINDOW)); 
        
        maskDC.BitBlt(0, 0, rcClip.Width(), rcClip.Height(), &memDC, rcClient.left, rcClient.top, SRCCOPY); 
#ifdef _DEBUG
        //dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
        //    &maskDC, rcClient.left, rcClient.top, SRCCOPY); 
#endif

        CDC tempDC; 
        tempDC.CreateCompatibleDC(&dc); 
        tempDC.SelectObject(&m_bitmap); 

        CDC imageDC; 
        CBitmap bmpImage; 
        imageDC.CreateCompatibleDC(&dc); 
        bmpImage.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height()); 
        imageDC.SelectObject(&bmpImage); 

        if(dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
        {
            dc.SelectPalette(&m_pal, FALSE); 
            dc.RealizePalette(); 
            imageDC.SelectPalette(&m_pal, FALSE); 
        }

        CRect rcRoot; 
        GetItemRect(GetRootItem(), rcRoot, FALSE); 
        rcRoot.left = -GetScrollPos(SB_HORZ); 
        for(int i=rcRoot.left; i<rcClient.right; i+=m_cxBitmap)
            for(int j=rcRoot.top; j<rcClient.bottom; j+=m_cyBitmap)
                imageDC.BitBlt(i, j, m_cxBitmap, m_cyBitmap, &tempDC, 0, 0, SRCCOPY); 

        //dc.FillRect(rcClient, &CBrush(RGB(255, 255, 192))); 
        memDC.SetBkColor(RGB(0, 0, 0)); 
        memDC.SetTextColor(RGB(255, 255, 255)); 
        memDC.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
            &maskDC, rcClient.left, rcClient.top, SRCAND); 
#ifdef _DEBUG
        //dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
        //    &memDC, rcClient.left, rcClient.top, SRCCOPY); 
#endif

        imageDC.SetBkColor(RGB(255, 255, 255)); 
        imageDC.SetTextColor(RGB(0, 0, 0));
        imageDC.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
            &maskDC, rcClient.left, rcClient.top, SRCAND); 

        imageDC.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
            &memDC, rcClient.left, rcClient.top, SRCPAINT); 

        dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
            &imageDC, rcClient.left, rcClient.top, SRCCOPY); 
    }
    else 
        dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
            &memDC, rcClient.left, rcClient.top, SRCCOPY); 

    //dc.SetBkColor(RGB(255, 255, 255)); 
    //dc.SetTextColor(RGB(0, 0, 0)); 
    //dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
    //    &maskDC, rcClient.left, rcClient.top, SRCAND); 
    //dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), 
    //    &memDC, rcClient.left, rcClient.top, SRCPAINT); 

	// Do not call CTreeCtrl::OnPaint() for painting messages
}

//HBRUSH CTreeCtrlEx::CtlColor(CDC* pDC, UINT nCtlColor) 
//{
//    // TODO: Change any attributes of the DC here
//    pDC->SetTextColor(RGB(0, 0, 255));     
//    pDC->SetBkColor(RGB(0, 255, 0)); 
//    // TODO: Return a non-NULL brush if the parent's handler should not be called
//    return ::CreateSolidBrush(RGB(255, 255, 192));
//    //return NULL; 
//}

BOOL CTreeCtrlEx::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE; 
	//return CTreeCtrl::OnEraseBkgnd(pDC);
}


BOOL CTreeCtrlEx::SetBkImage(UINT nIDResource)
{
    return SetBkImage((LPCTSTR)nIDResource); 
}

BOOL CTreeCtrlEx::SetBkImage(LPCTSTR lpszResourceName)
{
    if(m_bitmap.m_hObject != NULL)
        m_bitmap.DeleteObject(); 

    if(m_pal.m_hObject != NULL)
        m_pal.DeleteObject(); 

    HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), lpszResourceName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION); 
    if(hBmp == NULL)
        return FALSE; 

    m_bitmap.Attach(hBmp); 
    BITMAP bm; 
    m_bitmap.GetBitmap(&bm); 
    m_cxBitmap = bm.bmWidth; 
    m_cyBitmap = bm.bmHeight; 

    DIBSECTION ds; 
    BITMAPINFOHEADER& bmInfo = ds.dsBmih; 
    m_bitmap.GetObject(sizeof(ds), &ds); 
    int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount; 

    CClientDC dc(NULL); 
    if(nColors > 256)
        m_pal.CreateHalftonePalette(&dc); 
    else 
    {
        RGBQUAD* pRGB = new RGBQUAD[nColors]; 
        CDC memDC; 
        memDC.CreateCompatibleDC(&dc); 
        memDC.SelectObject(&m_bitmap); 
        ::GetDIBColorTable(memDC, 0, nColors, pRGB); 
        UINT nSize = sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * nColors; 
        LOGPALETTE* pLP = (LOGPALETTE*)new BYTE[nSize]; 
        pLP->palVersion = 0x300; 
        pLP->palNumEntries = nColors; 
        for(int i=0; i<nColors; i++)
        {
            pLP->palPalEntry[i].peRed = pRGB[i].rgbRed; 
            pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen; 
            pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue; 
            pLP->palPalEntry[i].peFlags = 0; 
        }

        m_pal.CreatePalette(pLP); 
        delete[] pLP; 
        delete[] pRGB;  
    }

    Invalidate(); 
    return TRUE; 
}

BOOL CTreeCtrlEx::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this); 
    if(dc.GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_pal.m_hObject != NULL)
    {
        dc.SelectPalette(&m_pal, FALSE); 
        BOOL result = dc.RealizePalette(); 
        if(result)
            Invalidate(); 
        return result; 
    }

	return CTreeCtrl::OnQueryNewPalette();
}

void CTreeCtrlEx::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CTreeCtrl::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	if(pFocusWnd == this)
        return; 

    OnQueryNewPalette(); 
}

void CTreeCtrlEx::Serialize(CArchive& ar)
{
    if(ar.IsStoring())
    {
        HTREEITEM hti = GetRootItem(); 
        while(hti)
        {
            int indent = GetIndentLevel(hti); 
            while(indent--)
                ar.WriteString("\t"); 
            ar.WriteString(GetItemText(hti) + "\r\n");
            hti = GetNextItem(hti); 
        }
    }
    else 
    {
        CString strLine; 
        if(!ar.ReadString(strLine))
            return; 

        HTREEITEM hti = NULL; 
        int indent, baseindent = 0; 
        while(strLine[baseindent] == '\t')
            baseindent++; 

        do
        {
            if(strLine.GetLength() == 0)
                continue; 

            for(indent=0; strLine[indent] == '\t'; indent++)
                ; 

            strLine = strLine.Right(strLine.GetLength()-indent); 
            indent -= baseindent; 

            HTREEITEM parent; 
            int previndent = GetIndentLevel(hti); 
            if(indent == previndent)
                parent = GetParentItem(hti); 
            else if(indent > previndent)
                parent = hti; 
            else 
            {
                int nLevelsUp = previndent - indent; 
                parent = GetParentItem(hti); 
                while(nLevelsUp--)
                    parent = GetParentItem(parent);
            }

            hti = InsertItem(strLine, parent ? parent : TVI_ROOT, TVI_LAST); 
        }while(ar.ReadString(strLine)); 
    }
}

int CTreeCtrlEx::GetIndentLevel(HTREEITEM hItem)
{
    int iIndent = 0; 
    while((hItem = GetParentItem(hItem)) != NULL)
        iIndent ++; 

    return iIndent; 
}