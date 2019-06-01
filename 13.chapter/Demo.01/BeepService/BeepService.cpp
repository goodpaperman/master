
#include <iostream.h>
#include <windows.h> 
#include <stdio.h>
#include <stdlib.h> 

#define DEFAULT_BEEP_DELAY 2000 

// the name of the service 
char* SERVICE_NAME = "BeepService"; 
// event used to hold ServiceMain from completing 
HANDLE terminateEvent = NULL; 
// handle used to communicate status info with the SCM. 
// created by RegisterServiceCtrlHandler 
SERVICE_STATUS_HANDLE serviceStatusHandle; 
// the beep interval in ms.
int beepDelay = DEFAULT_BEEP_DELAY; 
// flags holding current state of service 
BOOL pauseService = FALSE; 
BOOL runningService = FALSE; 
// thread for the actual work 
HANDLE threadHandle = 0; 

void ErrorHandler(char* s, DWORD err)
{
	cout << s << endl; 
	cout << "Error Number: " << err << endl; 
	ExitProcess(err); 
}

// this function consolidates the activities of updating the service status with SetServiceStatus
BOOL SendStatusToSCM(DWORD dwCurrentState, DWORD dwWin32ExitCode, 
					 DWORD dwServiceSpecificExitCode, DWORD dwCheckPoint, 
					 DWORD dwWaitHint) 
{
	SERVICE_STATUS serviceStatus; 
	serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; 
	serviceStatus.dwCurrentState = dwCurrentState; 

	// if in the process of doing something, 
	// then accept no control events, 
	// else accept anything 
	if(dwCurrentState == SERVICE_START_PENDING)
		serviceStatus.dwControlsAccepted = 0; 
	else 
		serviceStatus.dwControlsAccepted = 
			SERVICE_ACCEPT_STOP | 
			SERVICE_ACCEPT_PAUSE_CONTINUE | 
			SERVICE_ACCEPT_SHUTDOWN; 

	// if a specific exit code is defined, 
	// set up the win32 exit code properly 
	if(dwServiceSpecificExitCode == 0)
		serviceStatus.dwWin32ExitCode = dwWin32ExitCode; 
	else 
		serviceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR; 

	serviceStatus.dwServiceSpecificExitCode = dwServiceSpecificExitCode; 
	serviceStatus.dwCheckPoint = dwCheckPoint; 
	serviceStatus.dwWaitHint = dwWaitHint; 

	// Pass the status record to the SCM 
	return SetServiceStatus(serviceStatusHandle, &serviceStatus); 
}

DWORD ServiceThread(LPDWORD lpParam)
{
	while(1)
	{
		Beep(200, 200); 
		Sleep(beepDelay); 
	}

	return 0; 
}

BOOL InitService()
{
	DWORD id; 
	// Start the service's thread 
	threadHandle = CreateThread(0, 0, 
		(LPTHREAD_START_ROUTINE)ServiceThread, 0, 0, &id); 

	if(threadHandle == 0)
		return FALSE; 
	else 
	{
		runningService = TRUE; 
		return TRUE; 
	}
}

void Handler(DWORD controlCode)
{
	DWORD currentState = 0; 
	switch(controlCode)
	{
		// there is no START option because ServiceMain gets called on a start 
		// Stop the service 
	case SERVICE_CONTROL_STOP:
		// Tell the SCM what's happening 
		SendStatusToSCM(SERVICE_STOP_PENDING, NO_ERROR, 0, 1, 5000); 
		runningService = FALSE; 
		SetEvent(terminateEvent); 
		return; 
		// Pause the service 
	case SERVICE_CONTROL_PAUSE:
		if(runningService && !pauseService)
		{
			// Tell the SCM what's happening 
			SendStatusToSCM(SERVICE_PAUSE_PENDING, NO_ERROR, 0, 1, 1000); 
			pauseService = TRUE; 
			SuspendThread(threadHandle); 
			currentState = SERVICE_PAUSED; 
		}
		break; 
		// Resume from a pause
	case SERVICE_CONTROL_CONTINUE:
		if(runningService && pauseService)
		{
			// Tell the SCM what's happening
			SendStatusToSCM(SERVICE_CONTINUE_PENDING, NO_ERROR, 0, 1, 1000); 
			pauseService = FALSE; 
			ResumeThread(threadHandle); 
			currentState = SERVICE_RUNNING; 
		}
		break; 
		// Update current state 
	case SERVICE_CONTROL_INTERROGATE:
		// it will fall to bottom and send status 
		break; 
	case SERVICE_CONTROL_SHUTDOWN:
		return; 
	default:
		break; 
	}

	SendStatusToSCM(currentState, NO_ERROR, 0, 0, 0); 
}

// Handle an error from ServiceMain by cleaning up and telling SCM that the service didn't start.
void terminate(DWORD error)
{
	// if terminateEvent has been created, close it.
	if(terminateEvent)
		CloseHandle(terminateEvent); 

	// send a message to the SCM to tell about stopage
	if(serviceStatusHandle)
		SendStatusToSCM(SERVICE_STOPPED, error, 0, 0, 0); 

	// if the thread has started, kill it off
	if(threadHandle)
		CloseHandle(threadHandle); 

	// Do not need to close serviceStatusHandle
}


// ServiceMain is called when the SCM wants to start the service. 
// When it returns, the service has stopped. It therefore waits 
// on an event just before the end of the function, and that event
// gets set when it is time to stop. It also returns on any error
// because the service cannot start if there is an error. 
void ServiceMain(DWORD argc, LPTSTR* argv)
{
	// immediately call Registration function
	serviceStatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, (LPHANDLER_FUNCTION)Handler); 
	if(!serviceStatusHandle)
	{
		terminate(GetLastError()); 
		return; 
	}

	// notify SCM of progress
	if(!SendStatusToSCM(SERVICE_START_PENDING, NO_ERROR, 0, 1, 5000))
	{
		terminate(GetLastError()); 
		return; 
	}

	terminateEvent = CreateEvent(0, TRUE, FALSE, 0); 
	if(!terminateEvent)
	{
		terminate(GetLastError()); 
		return; 
	}

	// notify SCM of progress
	if(!SendStatusToSCM(SERVICE_START_PENDING, NO_ERROR, 0, 2, 1000))
	{
		terminate(GetLastError()); 
		return; 
	}

	if(argc == 2)
	{
		int temp = atoi(argv[1]); 
		if(temp < 1000)
			beepDelay = DEFAULT_BEEP_DELAY; 
		else 
			beepDelay = temp; 
	}

	// notify SCM of progress 
	if(!SendStatusToSCM(SERVICE_START_PENDING, NO_ERROR, 0, 3, 5000))
	{
		terminate(GetLastError()); 
		return; 
	}

	if(!InitService())
	{
		terminate(GetLastError()); 
		return; 
	}

	if(!SendStatusToSCM(SERVICE_RUNNING, NO_ERROR, 0, 0, 0))
	{
		terminate(GetLastError()); 
		return; 
	}

	WaitForSingleObject(terminateEvent, INFINITE); 
	terminate(0); 
}



void main()
{
	SERVICE_TABLE_ENTRY serviceTable[] = 
	{
		{SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain}, 
		{NULL, NULL} 
	}; 

	if(!StartServiceCtrlDispatcher(serviceTable))
		ErrorHandler("In StartServiceCtrlDispatcher", GetLastError()); 
}
