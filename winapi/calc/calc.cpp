#include <Windows.h>
#include <tchar.h>
#include <WindowsX.h>
#include "resource.h"

HINSTANCE g_mainHInst;

LRESULT CALLBACK mainWndProc( HWND hwnd, UINT msg, WPARAM w, LPARAM l );

BOOL CALLBACK calcProc( HWND hwnd, UINT msg, WPARAM w, LPARAM l );

int APIENTRY _tWinMain( HINSTANCE hinst, HINSTANCE hprev, 
	TCHAR * tCmdLine, int nCmdShow ){
	g_mainHInst = hinst;

	WNDCLASS wc = {0};

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hinst;
	wc.lpfnWndProc = mainWndProc;
	wc.lpszClassName = _T("calc");
	wc.lpszMenuName = (TCHAR*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(_T("calc"), _T("Tiny Applications"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinst, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL, _T("Failed to create the window"), 
			_T("First"), MB_OK);
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg = {0};
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}

LRESULT CALLBACK mainWndProc(HWND hWnd, UINT message, WPARAM wParam, 
	LPARAM lParam)
{
	switch(message)
	{
	case WM_COMMAND:
		if (HIWORD(wParam) == 0)
		{
			switch(LOWORD(wParam))
			{
			case ID_APPS_CALCULATOR:
				DialogBox(g_mainHInst, (TCHAR*)IDD_DIALOG_CALC, hWnd, calcProc);
			break;
			
			}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK calcProc(HWND hWnd, UINT message, WPARAM w, 
	LPARAM l)
{
	int btnId;
	static int res = 0;
	static int lastNum = 0;
	static int newNum = 0;
	static BOOL SEENOP = FALSE;
	static HWND oldH;
	static HWND newH;
	HWND editor = GetDlgItem( hWnd, IDC_EDITOR );
	static TCHAR LOP; //last op
	TCHAR buf[10];
	int num;
	switch(message)
	{
	case WM_COMMAND:
		if (HIWORD(w) == BN_CLICKED)
		{
			
			switch(LOWORD(w)){//btnid = loword
			case IDOK:
				EndDialog(hWnd, 0);				
			break;
			case IDC_BUTTON_dbg_get_text :
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				GetWindowText( editor, buf, 10 );
				MessageBox( hWnd, buf, _T("debug: value of text"), MB_OK );
			break;
			case IDC_BUTTON_VAL_0:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 0;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 0;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_1:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 1;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 1;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_2:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 2;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 2;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_3:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 3;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 3;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_4:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 4;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 4;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_5:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 5;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 5;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_6:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 6;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 6;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_7:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 7;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 7;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_8:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 8;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 8;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_VAL_9:
				editor = GetDlgItem( hWnd, IDC_EDITOR );
				if( !SEENOP ){
					lastNum = lastNum * 10 + 9;
					num = lastNum;
				}
				else{
					newNum = newNum * 10 + 9;
					num = newNum;
				}
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_OP_SU:
				LOP = '+';
				if ( newNum != 0 )
					lastNum += newNum;
				newNum = 0;
				SEENOP = TRUE;
				num = 0;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_OP_DI:
				LOP = '-';
				if ( newNum != 0 )
					lastNum -= newNum;
				newNum = 0;
				SEENOP = TRUE;
				num = 0;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_OP_PR:
				LOP = '*';
				if ( newNum != 0 )
					lastNum *= newNum;
				newNum = 0;
				SEENOP = TRUE;
				num = 0;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_OP_REM:
				LOP = '%';
				if ( newNum != 0 )
					lastNum %= newNum;
				newNum = 0;
				SEENOP = TRUE;
				num = 0;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_OP_QU:
				LOP = '/';
				if ( newNum != 0 )
					lastNum /= newNum;
				newNum = 0;
				SEENOP = TRUE;
				num = 0;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_OP_EQ:
				if( lastNum == 0 ){
					num = 0;
				}
				else if( newNum == 0 ){
					num = lastNum;
				}
				else {
					switch( LOP ){
					case '+':
						num = lastNum + newNum;
					break;
					case '-':
						num = lastNum - newNum;
					break;
					case '*':
						num = lastNum * newNum;
					break;
					case '%':
						num = lastNum % newNum;
					break;
					case '/':
						num = lastNum / newNum;
					break;
					}
				}
				newNum = 0;
				lastNum = num;
				SEENOP = FALSE;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			case IDC_BUTTON_RESET:
				newNum = lastNum = num = 0;
				_stprintf( buf, _T("%d"), num );
				SetWindowText( editor, buf );
			break;
			}
		return TRUE;
		}
	default:
		return FALSE;
	}
}