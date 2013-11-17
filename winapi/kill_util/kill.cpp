// kill.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* main
 * return values:
 * 0  : success
 * -1 : wrong usage
 * -2 : handle not obtained
 * 5  : access denied
 */
int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2){
		printf("This program is not going to execute further.\n");
		printf("Usage: kill.exe pid\npid is integer.\n\n");
		return -1; //wrong usage
	}
	for( int i = 1; i < argc; i++){
		DWORD dwPID = _tstoi(argv[i]);
		//printf("pid = %d\n", dwPID );
		HANDLE ToKillProcessHandle = OpenProcess( PROCESS_TERMINATE, FALSE,  dwPID);
		if( ToKillProcessHandle == NULL ){
			int errorno = GetLastError();
			printf("Handle not obtained. Error # %d\n", errorno );
			if( errorno == ERROR_ACCESS_DENIED ){
				printf( "Error: Access denied to open process (pid = %d).\n", dwPID );
				return 5; //access denied
			}
			return -2; //handle not obtained
		}
		TerminateProcess ( ToKillProcessHandle, 0 );
		CloseHandle( ToKillProcessHandle );
		printf("\nProcess # %d is no more.\tGo Check!\n", dwPID );
	}
	return 0;
}


/* main function 
 * return values:
 * 0  - success value
 * -1 - error while creating a process
 */
//const TCHAR * ApplicationName= NULL;//	= _T("C:\\Windows\\System32\\notepad.exe");
	///*TCHAR  CommandLine [] = _T("notepad untitled.txt");*/
	//TCHAR  CommandLine [] = _T("notepad");
	//LPSECURITY_ATTRIBUTES ProcessAttributes = NULL;
	//LPSECURITY_ATTRIBUTES ThreadAttributes = NULL;
	//BOOL InheritedHandles = FALSE;
	//DWORD CreationFlags = NULL;//CREATE_NEW_CONSOLE;
	//LPVOID Environment = NULL;
	//const TCHAR * CurrentDir = NULL;
	//STARTUPINFO  StartupInfo = {0};
	//StartupInfo.cb = sizeof( STARTUPINFO );
	//PROCESS_INFORMATION ProcessInformation;
	//
	///*BOOL processCreationResult = CreateProcess( ApplicationName, CommandLine, ProcessAttributes,
	//	ThreadAttributes, InheritedHandles, CreationFlags, Environment, CurrentDir, &StartupInfo,
	//	&ProcessInformation);*/
	//
	///*BOOL processCreationResult = CreateProcess( 0, CommandLine, 0,
	//	0, FALSE, 0, 0, 0, &StartupInfo, &ProcessInformation);
	//	*/
	////if( processCreationResult == 0 ){
	////	printf("Error while creating a process with error # : %d", GetLastError() );
	////	return -1; //Error while creating a process
	////}
	//
	//CloseHandle( ProcessInformation.hThread );
	//CloseHandle( ProcessInformation.hProcess );