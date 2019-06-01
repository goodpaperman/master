; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoDlg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"

ClassCount=6
Class1=CDemoApp
Class2=CDemoDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DEMO_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Class5=CCounterThread
Class4=CExampleThread
Class6=CDisplayThread
Resource5=IDD_DEMO_DIALOG (English (U.S.))

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
LastObject=IDC_PAUSE

[CLS:CAboutDlg]
Type=0
HeaderFile=DemoDlg.h
ImplementationFile=DemoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


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
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PRIORITYCLASS,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DSPYTHRDPRIORITY,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CNTRTHRDPRIORITY,combobox,1344339971
Control7=IDC_DATABOX,listbox,1352728835
Control8=IDC_SYNCHRONIZE,button,1342242819
Control9=IDC_SHOWCNTRTHRD,button,1342242819
Control10=IDC_PAUSE,button,1342242819

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CExampleThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp
BaseClass=CWinThread
Filter=N
LastObject=CExampleThread

[CLS:CCounterThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp
BaseClass=CExampleThread
Filter=N
VirtualFilter=TC
LastObject=CCounterThread

[CLS:CDisplayThread]
Type=0
HeaderFile=threads.h
ImplementationFile=threads.cpp
BaseClass=CExampleThread
Filter=N
VirtualFilter=TC
LastObject=CDisplayThread

