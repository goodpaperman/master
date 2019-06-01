; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSheet
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"

ClassCount=3
Class1=CDemoApp
Class2=CDemoDlg

ResourceCount=7
Resource2=IDD_DEMO_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDD_PROPPAGE_MEDIUM (English (U.S.))
Class3=CSheet
Resource4=IDD_PROPPAGE_SMALL (English (U.S.))
Resource5=IDD_DEMO_DIALOG (English (U.S.))
Resource6=IDD_PROPPAGE_LARGE (English (U.S.))
Resource7=IDR_MENU

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
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:CSheet]
Type=0
HeaderFile=Sheet.h
ImplementationFile=Sheet.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC
LastObject=ID_PAGE1

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_PAGE1
Command2=ID_PAGE2
Command3=ID_PAGE3
Command4=ID_PAGE4
CommandCount=4

[DLG:IDD_PROPPAGE_LARGE (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_MEDIUM (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_SMALL (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

