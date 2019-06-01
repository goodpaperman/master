; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoDlg
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"

ClassCount=3
Class1=CDemoApp
Class2=CDemoDlg

ResourceCount=3
Resource2=IDD_DEMO_DIALOG
Resource1=IDR_MAINFRAME
Class3=CTreeCtrlEx
Resource3=IDD_DEMO_DIALOG (English (U.S.))

[CLS:CDemoApp]
Type=0
HeaderFile=Demo.h
ImplementationFile=Demo.cpp
Filter=N

[CLS:CDemoDlg]
Type=0
HeaderFile=DemoDlg.h
ImplementationFile=DemoDlg.cpp
Filter=T
LastObject=CDemoDlg
BaseClass=CDialog
VirtualFilter=dWC



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
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TREE_DEMO,SysTreeView32,1350631431
Control5=ID_EXPAND,button,1342242816
Control6=ID_COLLAPSE,button,1342242816
Control7=ID_SAVE,button,1342242816
Control8=ID_LOAD,button,1342242816

[CLS:CTreeCtrlEx]
Type=0
HeaderFile=TreeCtrlEx.h
ImplementationFile=TreeCtrlEx.cpp
BaseClass=CTreeCtrl
Filter=W
LastObject=CTreeCtrlEx
VirtualFilter=GWC

