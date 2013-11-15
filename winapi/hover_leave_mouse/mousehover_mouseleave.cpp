#include <Windows.h>
#include <tchar.h>
#include <WindowsX.h>

#define BTN_CLICK 1
#define ID_BTN 100

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, 
	LPARAM lParam);

LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, 
	LPARAM lParam);

HWND g_hWndChild;
HINSTANCE g_hInst;

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
						TCHAR* tCmdLine, int nCmdShow)
{
	g_hInst = hInst;
	WNDCLASS wc = {0};

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = _T("MYCLASS");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	// WNDCLASS for child window
	WNDCLASS wc2 = {0};
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc2.hInstance = hInst;
	wc2.lpfnWndProc = WndProcChild;
	wc2.lpszClassName = _T("MYCLASSCHILD");
	wc2.lpszMenuName = NULL;
	wc2.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc2);

	HWND hWnd = CreateWindow(_T("MYCLASS"), _T("My Third Window"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL, _T("Failed to create the window"), 
			_T("First"), MB_OK);
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);

	//Message Pump
	MSG msg = {0};
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, 
	LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		g_hWndChild = CreateWindow(_T("MYCLASSCHILD"), _T("Click"),
			WS_BORDER | WS_CHILD, 10, 10, 100, 100, hWnd , (HMENU)100, g_hInst, 0);
		ShowWindow(g_hWndChild, SW_SHOW);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		ShowWindow(g_hWndChild, SW_HIDE);
		DestroyWindow(g_hWndChild);
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BTN)
		{
			if (HIWORD(wParam) == BTN_CLICK)
			{
				//MessageBox(hWnd, _T("Clicked on Child"), 
				//	_T("Third"), MB_OK);
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcChild(HWND hWnd, UINT message, WPARAM wParam, 
	LPARAM lParam)
{
	HDC hDC;
	static RECT rect = {0};
	PAINTSTRUCT ps = {0};
	TCHAR str[100];
	WPARAM wp = 0;
	LPARAM lp = 0;TRACKMOUSEEVENT tme = {0};
	HBRUSH hbr;
	switch(message)
	{
	case WM_MOUSEHOVER:
		//MessageBox( hWnd, _T("done"), _T("what"), MB_OK );
		hDC = GetDC( hWnd );
		GetClientRect( hWnd, &rect );
		hbr = CreateSolidBrush( 0x00ffaaAA );
		FillRect( hDC, &rect, hbr );
		ReleaseDC( hWnd, hDC );
	break;
	case WM_MOUSELEAVE:
		hDC = GetDC( hWnd );
		GetClientRect( hWnd, &rect );
		FillRect( hDC, &rect, (HBRUSH)GetStockBrush(WHITE_BRUSH) );
		ReleaseDC( hWnd, hDC );
		//MessageBox( hWnd, _T("done"), _T("leaving soon"), MB_OK );
	break;
	case WM_CREATE:
		GetClientRect(hWnd, &rect);
		
		
	break;
	case WM_MOUSEMOVE:
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 100;
		tme.hwndTrack = hWnd;
		TrackMouseEvent( &tme );
	break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetWindowText(hWnd, str, 100);
		FillRect(hDC, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
		TextOut(hDC, 10, 10, str, _tcslen(str));
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONUP:
		wp = BTN_CLICK << 16 | ID_BTN;
		lp = (LPARAM)hWnd;
		hDC = GetDC( hWnd );
		GetClientRect( hWnd, &rect );
		FillRect( hDC, &rect, (HBRUSH) GetStockBrush( BLACK_BRUSH ));
		ReleaseDC( hWnd, hDC );
		SendMessage(GetParent(hWnd), WM_COMMAND, wp, lp);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}