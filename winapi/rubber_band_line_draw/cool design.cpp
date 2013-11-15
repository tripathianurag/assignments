#include<Windows.h>
#include<tchar.h>
#include<WindowsX.h>

LRESULT CALLBACK ElasticLines_MessageHandler( HWND hwnd, UINT msg, WPARAM w, LPARAM l );

int APIENTRY _tWinMain( HINSTANCE hinst, HINSTANCE might_also_be_null, TCHAR * pCmdLine, int nCmdShow ){
	WNDCLASS wc = {0};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hinst;
	wc.lpfnWndProc = ElasticLines_MessageHandler;
	wc.lpszClassName = _T("ElasticLinesClass");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &wc );

	HWND hwnd = CreateWindow( _T("ElasticLinesClass"), _T("Elastic Lines"), WS_OVERLAPPEDWINDOW,
		                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
							  NULL, NULL, hinst, NULL);
	if( hwnd == NULL ){
		MessageBox(NULL, _T("Failed to create a window. :( "), _T("No. No dough for you."), MB_OK);
		return -1;
	}
	ShowWindow(hwnd, nCmdShow);
	MSG msg = {0};
	while( GetMessage(&msg, NULL, 0,0) ){
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	return 0;
}

LRESULT CALLBACK ElasticLines_MessageHandler( HWND hwnd, UINT msg, WPARAM w, LPARAM l ){
	HDC hdc;
	static POINTS ptsBegin, ptsPrevEnd, ptsEnd;
	COLORREF bgcolor = 0x00ffffff;

	switch( msg ){
	case WM_LBUTTONDOWN:
		SetCapture( hwnd );
		ptsBegin = MAKEPOINTS( l );
		ptsPrevEnd = ptsBegin;

	break;
	case WM_MOUSEMOVE:
		if ( w & MK_LBUTTON ){
			hdc = GetDC( hwnd );
			HPEN hpen = CreatePen( PS_DASHDOTDOT, 1, 0x000000ff );
			HPEN hOldPen =(HPEN) SelectObject( hdc, hpen );

			MoveToEx( hdc, ptsBegin.x, ptsBegin.y, NULL );
			LineTo	( hdc, ptsPrevEnd.x, ptsPrevEnd.y );
			
			ptsEnd = MAKEPOINTS( l );
			SelectObject( hdc, hOldPen );
			MoveToEx( hdc, ptsBegin.x, ptsBegin.y, NULL );
			LineTo( hdc, ptsEnd.x, ptsEnd.y);

			ptsPrevEnd = ptsEnd;
			
			ReleaseDC( hwnd, hdc );
		}
		if ( w & MK_RBUTTON ){
			hdc = GetDC( hwnd );
			HPEN hpen = CreatePen( PS_DASHDOTDOT, 1, 0x000000ff );
			SelectObject( hdc, hpen );

			MoveToEx( hdc, ptsBegin.x, ptsBegin.y, NULL );
			LineTo	( hdc, ptsPrevEnd.x, ptsPrevEnd.y );
			
			
			ReleaseDC( hwnd, hdc );
		}
	break;
	case WM_LBUTTONUP:
		
		ReleaseCapture();

	break;
	case WM_CLOSE:
		DestroyWindow( hwnd );
	break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
	break;
	default:
		return DefWindowProc( hwnd, msg, w, l );
	}

	return 0;
}