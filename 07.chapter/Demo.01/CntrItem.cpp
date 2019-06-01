// CntrItem.cpp : implementation of the CDemoCntrItem class
//

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "DemoView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoCntrItem implementation

IMPLEMENT_SERIAL(CDemoCntrItem, CRichEditCntrItem, 0)

CDemoCntrItem::CDemoCntrItem(REOBJECT* preo, CDemoDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CDemoCntrItem::~CDemoCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CDemoCntrItem diagnostics

#ifdef _DEBUG
void CDemoCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CDemoCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
