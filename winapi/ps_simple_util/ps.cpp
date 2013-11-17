// ls.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/* main
 * return values
 * 0  : success
 * -1 : snapshot not created : invalid handle value
 * -2 : can't get hold of first process in snapshot
 */
int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwFlags = TH32CS_SNAPPROCESS, th32ProcessId = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot( dwFlags, th32ProcessId /* will be ignored */);
	if( snapshot == INVALID_HANDLE_VALUE ){
		int errorno = GetLastError();
		_tprintf(_T("Error: snapshot not created. Error # %d i.e. invalid handle value.\n"), errorno );
		return -1;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	BOOL firstProcess = Process32First( snapshot, &pe32 );
	if( !firstProcess ){
		int errorno = GetLastError();
		_tprintf( _T("Error: can't get hold of first process in snapshot. Error # %d.\n"), errorno );
		CloseHandle( snapshot ); //kill the snapshot handle
		return -2;
	}
	_tprintf(_T("PID\tCMD\n"));
	do{
		_tprintf( _T("%d\t%s\n"), pe32.th32ProcessID, pe32.szExeFile );
	}while( Process32Next( snapshot, &pe32 ) );
	CloseHandle( snapshot );

	return 0;
}

