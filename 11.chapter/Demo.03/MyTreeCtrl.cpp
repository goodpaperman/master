// MyTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "MyTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

CMyTreeCtrl::CMyTreeCtrl()
{
	m_pFtpConnection = NULL; 
}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers

void CMyTreeCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMTreeView->hdr.code == TVN_ITEMEXPANDING)
	{
		HTREEITEM hIT = pNMTreeView->itemNew.hItem; 
		CString cstr, strPath; 
		strPath = GetItemText(hIT); 
		while(hIT != GetRootItem())
		{
			hIT = GetParentItem(hIT); 
			if(hIT == GetRootItem())
				cstr.Format(_T("/%s"), (LPCTSTR)strPath); 
			else 
				cstr.Format(_T("%s/%s"), (LPCTSTR)GetItemText(hIT), (LPCTSTR)strPath); 

			strPath = cstr; 
		}

		ExploreDir(strPath, pNMTreeView->itemNew.hItem); 
	}

	*pResult = 0;
}

void CMyTreeCtrl::OnDestroy() 
{
	// TODO: Add your message handler code here
	CImageList* pimagelist = GetImageList(TVSIL_NORMAL); 
	if(pimagelist)
	{
		pimagelist->DeleteImageList(); 
		delete pimagelist; 
	}

	CTreeCtrl::OnDestroy();	
}

void CMyTreeCtrl::PopulateTree(CFtpConnection* pConnection /* = NULL */, const CString& strDir /* = CString */)
{
	CWaitCursor cursor; 
	DeleteAllItems(); 

	if(!pConnection)
	{
		ModifyStyle(TVS_LINESATROOT, 0); 
		TV_INSERTSTRUCT tvstruct; 
		tvstruct.hParent = NULL; 
		tvstruct.item.iImage = 0; 
		tvstruct.item.iSelectedImage = 0; 
		tvstruct.item.pszText = _T("An FTP connection has not been established."); 
		tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT; 
		HTREEITEM hThisItem = InsertItem(&tvstruct); 
		m_pFtpConnection = NULL; 
	}
	else 
	{
		m_pFtpConnection = pConnection; 
		CString cstr = _T("/"); 
		TV_INSERTSTRUCT tv; 
		tv.hParent = NULL; 
		tv.hInsertAfter = TVI_LAST; 
		tv.item.iImage = 1; 
		tv.item.iSelectedImage = 1; 
		tv.item.pszText = _T("/"); 
		tv.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT; 
		HTREEITEM hThisItem = InsertItem(&tv); 

		tv.hParent = hThisItem; 
		InsertItem(&tv); 
		Expand(GetRootItem(), TVE_EXPAND); 


		if(!ItemHasChildren(GetRootItem()))
		{
			ModifyStyle(TVS_LINESATROOT, 0); 
			return; 
		}

		ModifyStyle(0, TVS_LINESATROOT); 
		if(!strDir)
			return; 

		 int nIndex; 
		 CString strTemp; 
		 CString strSrc = strDir; 
		 HTREEITEM hTI = GetRootItem(); 
		 while(!strSrc.IsEmpty())
		 {
			 nIndex = strSrc.Find(_T("/")); 
			 if(nIndex < 0)
			 {
				 cstr = strSrc; 
				 strSrc.Empty(); 
			 }
			 else if(nIndex > 0)
			 {
				 cstr = strSrc.Left(nIndex); 
				 strTemp = strSrc.Right(strSrc.GetLength() - (nIndex+1)); 
				 strSrc = strTemp; 
			 }

			 if(!cstr.IsEmpty() && nIndex != 0)
			 {
				 hTI = GetChildItem(hTI); 
				 while((hTI != NULL) && (cstr != GetItemText(hTI)))
				 {
					 hTI = GetNextItem(hTI, TVGN_NEXT); 
				 }

				 if((hTI != NULL) && (cstr == GetItemText(hTI)))
				 {
					 if(ItemHasChildren(hTI))
						 Expand(hTI, TVE_EXPAND); 
					 else 
					 {
						 SelectItem(hTI); 
						 TV_ITEM tv; 
						 tv.hItem = hTI; 
						 tv.mask = TVIF_HANDLE | TVIF_STATE; 
						 tv.stateMask = TVIS_BOLD; 
						 if(GetItem(&tv))
						 {
							 tv.mask = TVIF_HANDLE | TVIF_STATE; 
							 tv.stateMask = TVIS_BOLD; 
							 tv.state = TVIS_BOLD; 
							 SetItem(&tv); 
						 }

						 strSrc.Empty(); 
					 }
				 }
				 else 
					 strSrc.Empty(); 
			 }
			 else 
			 {
				 strTemp = strSrc.Right(strSrc.GetLength() - 1); 
				 strSrc = strTemp; 
			 }
		 }
	}
}

void CMyTreeCtrl::ExploreDir(const CString& strDir, HTREEITEM hParent)
{
	TV_INSERTSTRUCT tvs; 
	CString strSearchDir; 
	HTREEITEM hIT = GetChildItem(hParent); 
	HTREEITEM hTemp; 
	while(hIT != NULL)
	{
		hTemp = GetNextSiblingItem(hIT); 
		DeleteItem(hIT); 
		hIT = hTemp; 
	}

	if(hParent != GetRootItem())
		strSearchDir = strDir + _T("/*"); 
	else 
		strSearchDir = _T("/*");
	
	CFtpFileFind fff(m_pFtpConnection); 
	BOOL bContinue = fff.FindFile(strSearchDir); 
	if(!bContinue)
	{
		fff.Close(); 
		return; 
	}

	BOOL bDir = FALSE; 
	HTREEITEM hThisItem; 
	CString strFileName; 
	while(bContinue)
	{
		bContinue = fff.FindNextFile(); 
		strFileName = fff.GetFileName(); 
		if(fff.IsDirectory())
		{
			bDir = TRUE; 
			tvs.item.iImage = 1; 
			tvs.item.iSelectedImage = 1; 
		}
		else 
		{
			tvs.item.iImage = 2; 
			tvs.item.iSelectedImage = 2; 
		}

		tvs.hParent = hParent; 
		tvs.hInsertAfter = TVI_LAST; 
		tvs.item.pszText = (LPTSTR)(LPCTSTR)strFileName; 
		tvs.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT; 
		hThisItem = InsertItem(&tvs); 
	}

	fff.Close(); 
	if(bDir)
	{
		CFtpFileFind* pfff = NULL; 
		CString strFullSearchPath; 
		int nImage, nSelectedImage; 
		hThisItem = GetChildItem(hParent); 
		while(hThisItem != NULL)
		{
			GetItemImage(hThisItem, nImage, nSelectedImage); 
			if(nImage == 1)
			{
				strFileName = GetItemText(hThisItem); 
				strFullSearchPath = strDir + strFileName + _T("/*"); 
				pfff = new CFtpFileFind(m_pFtpConnection); 
				if(pfff->FindFile(strFullSearchPath))
				{
					tvs.hParent = hThisItem; 
					tvs.hInsertAfter = TVI_LAST; 
					tvs.item.iImage = 1; 
					tvs.item.iSelectedImage = 1; 
					tvs.item.pszText = _T("1"); 
					tvs.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT; 
					InsertItem(&tvs); 
				}

				pfff->Close(); 
				delete pfff; 
			}

			hThisItem = GetNextSiblingItem(hThisItem); 
		}
	}
}
