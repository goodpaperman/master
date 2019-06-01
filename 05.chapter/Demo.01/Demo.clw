; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInPlaceEdit
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"

ClassCount=5
Class1=CDemoApp
Class2=CDemoDlg

ResourceCount=4
Resource2=IDD_DEMO_DIALOG
Resource1=IDR_MAINFRAME
Class3=CHeaderCtrlEx
Class4=CListCtrlEx
Resource3=IDD_DEMO_DIALOG (English (U.S.))
Class5=CInPlaceEdit
Resource4=IDR_MENU_HEADER

[CLS:CDemoApp]
Type=0
HeaderFile=Demo.h
ImplementationFile=Demo.cpp
Filter=N

[CLS:CDemoDlg]
Type=0
HeaderFile=DemoDlg.h
ImplementationFile=DemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CDemoDlg



[DLG:IDD_DEMO_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CDemoDlg

[DLG:IDD_DEMO_DIALOG (English (U.S.))]
Type=1
Class=CDemoDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LIST_DEMO,SysListView32,1350632969
Control5=ID_CLEAR,button,1342242816

[CLS:CHeaderCtrlEx]
Type=0
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp
BaseClass=CHeaderCtrl
Filter=W
VirtualFilter=JWC

[CLS:CListCtrlEx]
Type=0
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC

[MNU:IDR_MENU_HEADER]
Type=1
Class=?
Command1=ID_DO
Command2=ID_YOUR
Command3=ID_OWN
Command4=ID_WORK
CommandCount=4

[CLS:CInPlaceEdit]
Type=0
HeaderFile=ListCtrlEx.h
ImplementationFile=ListCtrlEx.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC

