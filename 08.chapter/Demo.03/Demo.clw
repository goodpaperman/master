; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySheet
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"

ClassCount=4
Class1=CDemoApp
Class2=CDemoDlg

ResourceCount=4
Resource2=IDD_DEMO_DIALOG
Resource3=IDD_DEMO_DIALOG (English (U.S.))
Resource1=IDR_MAINFRAME
Class3=CMyPage
Class4=CMySheet
Resource4=IDD_PROPPAGE_1 (English (U.S.))

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
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PLACEHOLDER,static,1342177287
Control5=IDC_LIST1,listbox,1352728835

[DLG:IDD_PROPPAGE_1 (English (U.S.))]
Type=1
Class=CMyPage
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552

[CLS:CMyPage]
Type=0
HeaderFile=MyPage.h
ImplementationFile=MyPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CMyPage

[CLS:CMySheet]
Type=0
HeaderFile=MySheet.h
ImplementationFile=MySheet.cpp
BaseClass=CPropertySheet
Filter=W
VirtualFilter=hWC
LastObject=CMySheet

