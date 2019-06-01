; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTWScriptEdit
LastTemplate=CRichEditCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"

ClassCount=3
Class1=CDemoApp
Class2=CDemoDlg

ResourceCount=3
Resource2=IDD_DEMO_DIALOG
Resource1=IDR_MAINFRAME
Class3=CTWScriptEdit
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
ControlCount=3
Control1=IDC_RICHEDIT_CODE,RICHEDIT,1353781380
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:CTWScriptEdit]
Type=0
HeaderFile=TWScriptEdit.h
ImplementationFile=TWScriptEdit.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=CTWScriptEdit

