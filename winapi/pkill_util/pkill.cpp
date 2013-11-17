// pkill.cpp : Defines the entry point for the console application.
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
	if(argc < 2){
		printf("This program is not going to execute further.\n");
		printf("Usage: pkill.exe process-name (without .exe).\n\n");
		return -1; //wrong usage
	}
	if( _tcsstr(argv[1], _T(".exe")) ){
		printf("This program is not going to execute further.\n");
		printf("Usage: pkill.exe process-name (without .exe).\n\n");
		return -1; //wrong usage
	}
	TCHAR * name  = (TCHAR *) calloc( 25, sizeof(char) );
	DWORD dwFlags = TH32CS_SNAPPROCESS, th32ProcessId = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot( dwFlags, th32ProcessId /* will be ignored */);
	if( snapshot == INVALID_HANDLE_VALUE ){
		int errorno = GetLastError();
		_tprintf(_T("Error: snapshot not created. Error # %d i.e. invalid handle value.\n"), errorno );
		return -2;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	BOOL firstProcess = Process32First( snapshot, &pe32 );
	if( !firstProcess ){
		int errorno = GetLastError();
		_tprintf( _T("Error: can't get hold of first process in snapshot. Error # %d.\n"), errorno );
		CloseHandle( snapshot ); //kill the snapshot handle
		return -3;
	}
	for( int i = 1; i < argc; i++){
		_tcscat( name, argv[i] );
		_tcscat( name, _T(".exe") );
		//_tprintf( name );
		do{
			if( _tcscmp( name, pe32.szExeFile ) == 0 ){
				/* kill code */
				HANDLE ToKillProcessHandle = OpenProcess( PROCESS_TERMINATE, FALSE,  pe32.th32ProcessID);
				if( ToKillProcessHandle == NULL ){
					int errorno = GetLastError();
					printf("Handle not obtained. Error # %d\n", errorno );
					if( errorno == ERROR_ACCESS_DENIED ){
						printf( "Error: Access denied to open process (pid = %d).\n", pe32.th32ProcessID );
						return 5; //access denied
					}
					return -4; //handle not obtained
				}
				_tprintf(_T("killed: %d\n"), pe32.th32ProcessID ) ;
				TerminateProcess ( ToKillProcessHandle, 0 );
				CloseHandle( ToKillProcessHandle );
			}
		}while( Process32Next( snapshot, &pe32 ) );
	}
	CloseHandle( snapshot );
}

