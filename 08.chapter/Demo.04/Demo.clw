; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLargePage
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Demo.h"
LastPage=0

ClassCount=9
Class1=CDemoApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class2=CChildView
Resource3=IDD_ABOUTBOX (English (U.S.))
Class5=CWizPropertySheet
Class6=CWizPropertyPage
Resource4=IDR_MAINFRAME (English (U.S.))
Class7=CSmallPage
Resource5=IDD_PROPPAGE_SMALL (English (U.S.))
Class8=CMediumPage
Resource6=IDD_PROPPAGE_MEDIUM (English (U.S.))
Class9=CLargePage
Resource7=IDD_PROPPAGE_LARGE (English (U.S.))

[CLS:CDemoApp]
Type=0
HeaderFile=Demo.h
ImplementationFile=Demo.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_VIEW_WIZARD




[CLS:CAboutDlg]
Type=0
HeaderFile=Demo.cpp
ImplementationFile=Demo.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_APP_ABOUT
CommandCount=13
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_VIEW_WIZARD
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CWizPropertySheet]
Type=0
HeaderFile=WizPropertySheet.h
ImplementationFile=WizPropertySheet.cpp
BaseClass=CPropertySheet
Filter=W

[CLS:CWizPropertyPage]
Type=0
HeaderFile=WizPropertyPage.h
ImplementationFile=WizPropertyPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CWizPropertyPage

[DLG:IDD_PROPPAGE_SMALL (English (U.S.))]
Type=1
Class=CSmallPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CSmallPage]
Type=0
HeaderFile=SmallPage.h
ImplementationFile=SmallPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CSmallPage

[DLG:IDD_PROPPAGE_MEDIUM (English (U.S.))]
Type=1
Class=CMediumPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CMediumPage]
Type=0
HeaderFile=MediumPage.h
ImplementationFile=MediumPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CMediumPage

[DLG:IDD_PROPPAGE_LARGE (English (U.S.))]
Type=1
Class=CLargePage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CLargePage]
Type=0
HeaderFile=LargePage.h
ImplementationFile=LargePage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CLargePage

