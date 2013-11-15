#include<Windows.h>
#include<tchar.h>
#include<WindowsX.h>
#define TEXTMATRIX(x, y) *(pTextMatrix + (y * nWindowCharsX) + x) 

LRESULT CALLBACK CrudeType_MessageHandler( HWND hwnd, UINT msg, WPARAM w, LPARAM l );

int APIENTRY _tWinMain( HINSTANCE hinst, HINSTANCE might_also_be_null, TCHAR * pCmdLine, int nCmdShow ){
	WNDCLASS wc = {0};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hinst;
	wc.lpfnWndProc = CrudeType_MessageHandler;
	wc.lpszClassName = _T("CrudeTypeClass");
	wc.lpszMenuName = NULL;//(TCHAR*)IDR_MENU1;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &wc );

	HWND hwnd = CreateWindow( _T("CrudeTypeClass"), _T("Crude type"), WS_OVERLAPPEDWINDOW,
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

LRESULT CALLBACK CrudeType_MessageHandler( HWND hwnd, UINT msg, WPARAM w, LPARAM l ){
	TCHAR buf[10], ch; 
	HINSTANCE hinst = GetModuleHandle( NULL );
	HDC hdc;
	HBITMAP hCaret;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	static int nCharX, nCharY, nWindowX, nWindowY, nWindowCharsX, nWindowCharsY, nCaretPosX, nCaretPosY, tmX, tmY;
	static UINT uOldBlink;
	static TCHAR * pTextMatrix = NULL; 
	static int x = 0, y = 0;

	switch( msg ){
	case WM_CREATE:
		hdc = GetDC( hwnd );
		SelectObject( hdc, GetStockObject( SYSTEM_FIXED_FONT ) );
		GetTextMetrics( hdc, &tm );
		nCharX = tm.tmAveCharWidth;
		nCharY = tm.tmHeight;
		ReleaseDC( hwnd, hdc );
	break;

	case WM_SIZE:
		nWindowX = LOWORD( l );
		nWindowCharsX = max( 1, nWindowX / nCharX ); //how many characters that can fit
		nWindowY = HIWORD( l );
		nWindowCharsY = max( 1, nWindowY / nCharY ); //how many chars can fit
		if(pTextMatrix != NULL ) free( pTextMatrix );
		pTextMatrix = (TCHAR *)malloc( nWindowCharsX * nWindowCharsY );
		for( tmX = 0; tmX < nWindowCharsX; tmX++ )
			for( tmY = 0; tmY < nWindowCharsY; tmY++ )
				TEXTMATRIX(tmX, tmY) = ' ';
		SetCaretPos(0, 0);
	break;
	case WM_KEYDOWN:
		switch( w ){
		case VK_DELETE:
			for( tmX = nCaretPosX; tmX < nWindowCharsX; tmX++ )
				TEXTMATRIX( tmX, nCaretPosY) = TEXTMATRIX(tmX+1, nCaretPosY );
			TEXTMATRIX( nWindowCharsX - 1, nCaretPosY ) = ' ';
			HideCaret( hwnd );
			hdc = GetDC( hwnd );
			SelectObject( hdc, GetStockObject( SYSTEM_FIXED_FONT ) );
			TextOut( hdc, nCaretPosX * nCharX, nCaretPosY * nCharY, 
				&TEXTMATRIX( nCaretPosX, nCaretPosY ), nWindowCharsX - nCaretPosX );
			ReleaseDC( hwnd, hdc );
			ShowCaret( hwnd );
		break;
		}
	break;
	case WM_CHAR: 
		switch( w ){
		case 0x08:
			if( nCaretPosX > 0 ){
				nCaretPosX -- ;
				SendMessage( hwnd, WM_KEYDOWN, VK_DELETE, 1L );
			}
			if( nCaretPosX == 0 && nCaretPosY > 0 ){
				nCaretPosY--;
				nCaretPosX = nWindowCharsX;
			}
		break;
		
		case 0x0D: // CR
			//y+=(nCharY+2);
			//x = 0; //this makes it LF
			nCaretPosX = 0;
			if ( ++nCaretPosY == nWindowCharsY )
				nCaretPosY = 0;
		break;
		default:
			TEXTMATRIX( nCaretPosX, nCaretPosY ) = (TCHAR) w;
			HideCaret( hwnd );
			hdc = GetDC( hwnd );
			SelectObject( hdc, GetStockObject( SYSTEM_FIXED_FONT ) );

			TextOut( hdc, nCaretPosX*nCharX, nCaretPosY*nCharY, &TEXTMATRIX(nCaretPosX, nCaretPosY), 1 );
			ReleaseDC( hwnd, hdc );

			ShowCaret( hwnd );

			if( ++nCaretPosX == nWindowCharsX ){
				nCaretPosX = 0;
				if( ++nCaretPosY == nWindowCharsY ){
					nCaretPosY = 0;
				}
			}
			break;
		}
		SetCaretPos( nCaretPosX * nCharX, nCaretPosY * nCharY );
	break;
	case WM_PAINT: 
        // Draw all the characters in the buffer, line by line. 
 
        hdc = BeginPaint(hwnd, &ps); 
 
        SelectObject(hdc, 
            GetStockObject(SYSTEM_FIXED_FONT)); 
 
        for (y = 0; y < nWindowCharsY; y++) 
            TextOut(hdc, 0, y * nCharY, &TEXTMATRIX(0, y), 
                nWindowCharsX); 
		
        EndPaint(hwnd, &ps); 
		ReleaseDC( hwnd, hdc );
	break; //what the difference if we remove it all together
		
	case WM_SETFOCUS: 
        hCaret = LoadBitmap(hinst, MAKEINTRESOURCE(120)); 
        CreateCaret(hwnd, hCaret, 0, 0); 
        SetCaretPos(nCaretPosX * nCharX, nCaretPosY * nCharY); 
        ShowCaret(hwnd); 
    break; 
 
    case WM_KILLFOCUS: 
        DestroyCaret(); 
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