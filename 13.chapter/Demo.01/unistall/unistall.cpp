
#include <windows.h>
#include <iostream.h>

void ErrorHandler(char* s, DWORD err)
{
	cout << s << endl; 
	cout << "Error Number: " << err << endl; 
	ExitProcess(err); 
}

void main(int argc, char* argv[])
{
	SC_HANDLE service, scm; 
	SERVICE_STATUS status; 
	if(argc != 2)
	{
		cout << "Usage: " << endl; 
		cout << "	remove service_name\n"; 
		return; 
	}

	// open a connection to the SCM 
	scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE); 
	if(!scm)
		ErrorHandler("In OpenScManager", GetLastError()); 

	// Get the service's handle
	service = OpenService(scm, argv[1], SERVICE_ALL_ACCESS | DELETE); 
	if(!service)
		ErrorHandler("In OpenService", GetLastError()); 

	// Stop the service if necessary 
	if(!QueryServiceStatus(service, &status))
		ErrorHandler("In QueryServiceStatus", GetLastError()); 

	if(status.dwCurrentState != SERVICE_STOPPED)
	{
		cout << "Stopping service...\n"; 
		if(!ControlService(service, SERVICE_CONTROL_STOP, &status)) 
			ErrorHandler("In ControlService", GetLastError()); 
	}

	// remove the service 
	if(DeleteService(service))
		cout << "Service removed\n"; 
	else 
		ErrorHandler("In DeleteService", GetLastError()); 

	// clean up 
	CloseServiceHandle(service); 
	CloseServiceHandle(scm); 
}