// Win32Project2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project2.h"
enum EMarker {keBlank, keX, keO};

#define MAX_LOADSTRING 100
bool bDrawLine = false;							//initializing X's
bool bDrawEllipse = false;						//initializing O's
int iPosX=0;
int iPosY=0;
int iPosX2 = 0;
int iPosY2 = 0;
int count = 0;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
EMarker gePlayerTurn = keX;
EMarker geaaBoard[3][3] = { {keBlank,keBlank,keBlank},{keBlank,keBlank,keBlank},{keBlank,keBlank,keBlank} };
const int gkiSqrSz = 150;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void ResetGame() {
	for (int iX = 0; iX < 3; ++iX) {
		for (int iY = 0; iY < 3; ++iY) {
			geaaBoard[iY][iX] = keBlank;
		}
	}
	gePlayerTurn = keX;
}

void drawX(HDC hdc, int *iX, int *iY) {
	HPEN hPenOld;
	HPEN hLinePen;											//line object to be used										
	COLORREF qLineColor;									//line color
	qLineColor = RGB(255, 0, 0);							//making it red
	hLinePen = CreatePen(PS_SOLID, 7, qLineColor);			//design of the pen, thickness,implementing the designated colour into line object
	hPenOld = (HPEN)SelectObject(hdc, hLinePen);			//pen object calls upon line object
	int iSqX = (*iX / gkiSqrSz);		//Divides X point by pixels to locate which part of the board it is on
	int iSqY = (*iY / gkiSqrSz);		//Divides Y point by pixels to locate which part of the board it is on
	int iPosX = iSqX*gkiSqrSz + gkiSqrSz / 2;
	int iPosY = iSqY*gkiSqrSz + gkiSqrSz / 2;
	const int highX = iPosX + 50;
	const int lowX = iPosX - 50;
	const int highY = iPosY + 50;
	const int lowY = iPosY - 50;
	MoveToEx(hdc, lowX, lowY, NULL);							//marks first corner
	LineTo(hdc, highX, highY);									//marks the corner to make the line
	SelectObject(hdc, hPenOld);								//selects pen object for this line design
	DeleteObject(hLinePen);									//delete so we can move on

	hPenOld = (HPEN)SelectObject(hdc, hLinePen);			//pen object calls upon line object

	MoveToEx(hdc, lowX, highY, NULL);							//marks first corner
	LineTo(hdc, highX, lowY);									//marks the corner to make the line
	SelectObject(hdc, hPenOld);								//selects pen object for this line design
	DeleteObject(hLinePen);									//delete so we can move on
}
void drawO(HDC hdc, int *iX2, int *iY2) {
	HPEN hPenOld;
	HPEN hEllipsePen;
	COLORREF qEllipseColor;
	qEllipseColor = RGB(0, 0, 255);
	hEllipsePen = CreatePen(PS_SOLID, 3, qEllipseColor);
	hPenOld = (HPEN)SelectObject(hdc, hEllipsePen);
	int iSqX = (*iX2 / gkiSqrSz);		//Divides X point by pixels to locate which part of the board it is on
	int iSqY = (*iY2 / gkiSqrSz);		//Divides Y point by pixels to locate which part of the board it is on
	int iPosX = iSqX*gkiSqrSz + gkiSqrSz / 2;
	int iPosY = iSqY*gkiSqrSz + gkiSqrSz / 2;
	const int highX = iPosX + 50;
	const int lowX = iPosX - 50;
	const int highY = iPosY + 50;
	const int lowY = iPosY - 50;
	Arc(hdc, lowX, lowY, highX, highY, 0, 0, 0, 0);
	SelectObject(hdc, hPenOld);
	DeleteObject(hEllipsePen);
}
/*
void drawRect(HDC hdc, int nLeftRight, int nTopRect, int nRightRect, int nBottomRect) {
	HPEN hPenOld;
	HPEN hRectPen;
	COLORREF qRectColor;
	qRectColor = RGB(0, 255, 0);
	hRectPen = CreatePen(PS_SOLID, 8, qRectColor);
	hPenOld = (HPEN)SelectObject(hdc, hRectPen);
	Rectangle(hdc, nLeftRight, nTopRect, nRightRect, nBottomRect);
	SelectObject(hdc, hPenOld);
	DeleteObject(hRectPen);
}
*/
bool PlaceX(HWND hWnd, LPARAM lParam, int *iPosX, int *iPosY) {
	int iSqX = (*iPosX / gkiSqrSz);		//Divides X point by pixels to locate which part of the board it is on
	int iSqY = (*iPosY / gkiSqrSz);		//Divides Y point by pixels to locate which part of the board it is on
	if (geaaBoard[iSqY][iSqX] == keBlank && gePlayerTurn==keX) {
		geaaBoard[iSqY][iSqX] = keX;
		wchar_t waCoord[40];
		wsprintf(waCoord, _T("iPosX: %i\niPosY: %i\niSqX: %i\niSqY: %i"), *iPosX, *iPosY, iSqX, iSqY);
		::MessageBox(hWnd, waCoord, _T("LMB Click"), MB_OK);
		return true;
	}
	else {
		return false;
	}

}
bool PlaceO(HWND hWnd, LPARAM lParam, int *iPosX, int *iPosY) {
	int iSqX = (*iPosX / gkiSqrSz);		//Divides X point by pixels to locate which part of the board it is on
	int iSqY = (*iPosY / gkiSqrSz);		//Divides Y point by pixels to locate which part of the board it is on
	if (geaaBoard[iSqY][iSqX] == keBlank && gePlayerTurn == keO) {
		geaaBoard[iSqY][iSqX] = keO;
		wchar_t waCoord[40];
		wsprintf(waCoord, _T("iPosX: %i\niPosY: %i\niSqX: %i\niSqY: %i"), *iPosX, *iPosY, iSqX, iSqY);
		::MessageBox(hWnd, waCoord, _T("RMB Click"), MB_OK);
		return true;
	}
	else {
		return false;
	}
}
void drawBoard(HDC hdc) {
	HPEN hPenOld;
	HPEN hBoardPen;
	COLORREF qBoardColor;
	qBoardColor = RGB(0, 0, 0);
	hBoardPen = CreatePen(PS_SOLID, 5, qBoardColor);
	hPenOld = (HPEN)SelectObject(hdc, hBoardPen);
	//vertical lines
	for (int iX = gkiSqrSz; iX <= 2 * gkiSqrSz; iX += gkiSqrSz) {
		MoveToEx(hdc, iX, 0, NULL);
		LineTo(hdc, iX, 3 * gkiSqrSz);
	}
	//horizontal lines
	for (int iY = gkiSqrSz; iY <= 2 * gkiSqrSz; iY += gkiSqrSz) {
		MoveToEx(hdc, 0, iY, NULL);
		LineTo(hdc, 3 * gkiSqrSz, iY);
	}
	SelectObject(hdc, hPenOld);
	DeleteObject(hBoardPen);
}
bool checkWin(HWND hWnd, HDC hdc) {
	if (geaaBoard[0][0] != keBlank) {
		if (geaaBoard[0][1] == geaaBoard[0][0] && geaaBoard[0][2] == geaaBoard[0][0]){
			//drawRect(hdc, 0, 0, 3 * gkiSqrSz, gkiSqrSz);
			//InvalidateRect(hWnd, 0, false);
			return true;
		}
		if (geaaBoard[1][0] == geaaBoard[0][0] && geaaBoard[2][0] == geaaBoard[0][0]) {
			return true;
		}
	}
	if (geaaBoard[1][1] != keBlank) {
		if (geaaBoard[0][0] == geaaBoard[1][1] && geaaBoard[2][2] == geaaBoard[1][1]) {
			return true;
		}
		if (geaaBoard[2][0] == geaaBoard[1][1] && geaaBoard[0][2] == geaaBoard[1][1]) {
			return true;
		}
		if (geaaBoard[1][0] == geaaBoard[1][1] && geaaBoard[1][2] == geaaBoard[1][1]) {
			return true;
		}
		if (geaaBoard[0][1] == geaaBoard[1][1] && geaaBoard[2][1] == geaaBoard[1][1]) {
			return true;
		}
	}
	if (geaaBoard[2][2] != keBlank) {
		if (geaaBoard[2][0] == geaaBoard[2][2] && geaaBoard[2][1] == geaaBoard[2][2]) {
			return true;
		}
		if (geaaBoard[0][2] == geaaBoard[2][2] && geaaBoard[1][2] == geaaBoard[2][2]) {
			return true;
		}
	}
	return false;
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   500, 500, 500, 500, nullptr, nullptr, hInstance, nullptr);
   /*HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	  */
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_LBUTTONDOWN:
	{
		iPosX = LOWORD(lParam);
		iPosY = HIWORD(lParam);
		bool bValidMove=PlaceX(hWnd, lParam, &iPosX, &iPosY);
		if (bValidMove) {
			gePlayerTurn = keO;
			InvalidateRect(hWnd, 0, false);
		}
		else {
			::MessageBox(hWnd, _T("Invalid Move"), _T("Invalid Move"), MB_OK);
		}
		
		break;
	}
	case WM_RBUTTONDOWN:
	{
		iPosX2 = LOWORD(lParam);
		iPosY2 = HIWORD(lParam);
		bool bValidMove=PlaceO(hWnd, lParam, &iPosX2, &iPosY2);
		if (bValidMove) {
			gePlayerTurn = keX;
			InvalidateRect(hWnd, 0, false);
		}
		else {
			::MessageBox(hWnd, _T("Invalid Move"), _T("Invalid Move"), MB_OK);
		}
		
		break;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case IDM_NEW_GAME:
				ResetGame();
				InvalidateRect(hWnd, 0, TRUE);
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			drawBoard(hdc);											//draws board
			for (int iX = 0; iX < 3; iX++) {
				for (int iY = 0; iY < 3; iY++) {
					if (geaaBoard[iY][iX] == keX) {
						drawX(hdc, &iPosX, &iPosY);
					}
					else if (geaaBoard[iY][iX] == keO) {
						drawO(hdc, &iPosX2, &iPosY2);
					}
				}
			}
	
			if (checkWin(hWnd, hdc)) {
				if (gePlayerTurn == keO) {
					::MessageBox(hWnd, _T("Player 1 Won"), _T("New Game"), MB_OK);
				}
				else {
					::MessageBox(hWnd, _T("Player 2 Won"), _T("New Game"), MB_OK);
				}
				DestroyWindow(hWnd);
			}
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


