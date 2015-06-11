// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <fstream>
#include <string>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value = 1;
INT diag = 1;

// buttons
HWND hwndButton;

std::vector<Point> data_X;
std::vector<Point> data_Y;
std::vector<Point> data_Z;

RECT drawArea1 = { 0, 151, 800, 300 };
RECT drawArea2;
RECT drawArea3;
RECT drawArea4;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);




void inputData()
{
	std::ifstream source_file;

	double number;

	std::string file_name = "outputRobotForwardB02.log";
	std::string useless_data_X;
	std::string useless_data_Y;
	std::string useless_data_Z;

	source_file.open(file_name.c_str());

	if (source_file.fail())
	{
		MessageBox(NULL, L"Nie mozna otworzyc pliku.", L"ERR", MB_ICONEXCLAMATION);
	};

	for (int j = 0; j < 2304; j++)
	{
		if (j == 0)
		{
			source_file.seekg(+22, std::ios_base::cur);
		}
		else
		{
			source_file.seekg(+21, std::ios_base::cur);
		}

		source_file >> number;

		number = number * 500;

		number = 150 - number;

		getline(source_file, useless_data_X);

		useless_data_X.clear();

		data_X.push_back(Point(0, number));
	}	


	for (int j = 0; j < 2304; j++)
	{
		if (j == 0)
		{
			source_file.seekg(+29, std::ios_base::cur);
		}
		else
		{
			source_file.seekg(+28, std::ios_base::cur);
		}

		source_file >> number;

		number = number * 500;

		number = 150 - number;

		getline(source_file, useless_data_Y);

		useless_data_Y.clear();

		data_Y.push_back(Point(0, number));
	}

	for (int j = 0; j < 2304; j++)
	{
		if (j == 0)
		{
			source_file.seekg(+36, std::ios_base::cur);
		}
		else
		{
			source_file.seekg(+35, std::ios_base::cur);
		}

		source_file >> number;

		number = number * 500;

		number = 150 - number;

		getline(source_file, useless_data_Z);

		useless_data_Z.clear();

		data_Z.push_back(Point(0, number));
	}

	source_file.close();

}

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);

	Pen pen(Color(255, 0, 0, 0));
	Pen pen2(Color(255, 0, 255, 0));

	Font text(&FontFamily(L"Arial"), 20);

	SolidBrush text2(Color(255, 0, 0, 255));
	//graphics.DrawRectangle(&pen, 50 + value, 400, 10, 20);


	//for (int i = 1, j = value; i < wykres; i++, j++)
	//{
	//	k = 2 * (value - wykres);
	//
	//	graphics.DrawLine(&pen2, data[i - 1].X - k, data[j - 1].Y, data[i].X - k , data[j].Y);
	//};
	//	graphics.DrawLine(&pen2, data[wykres - 1].X, data[value - 1].Y, data[wykres].X, data[value].Y);



	graphics.DrawLine(&pen2, data_X[value - 1].X + 2 * diag, data_X[value - 1].Y, data_X[value].X + 2 + 2 * diag, data_X[value].Y);

	drawArea2 = { 2 * diag + 2, 0, 4 + 2 * diag, 300 };

	graphics.DrawLine(&pen2, data_Y[value - 1].X + 2 * diag, data_Y[value - 1].Y, data_Y[value].X + 2 + 2 * diag, data_Y[value].Y);

	drawArea3 = { 2 * diag + 2, 0, 4 + 2 * diag, 300 };

	graphics.DrawLine(&pen2, data_Z[value - 1].X + 2 * diag, data_Z[value - 1].Y, data_X[value].X + 2 + 2 * diag, data_Z[value].Y);

	drawArea4 = { 2 * diag + 2, 0, 4 + 2 * diag, 300 };


	//	for (int i = 1; i < wykres; i++)
	//	{
	//		graphics.DrawLine(&pen2, data[i - 1].X, data[i - 1].Y, data[i].X, data[i].Y);
	//	};

	graphics.DrawString(L"Podzialka czasowa: ", -1, &text, PointF(900, 60), &text2);

	graphics.DrawString(L"Amplituda : ", -1, &text, PointF(900, 160), &text2);

	graphics.DrawString(L"Sygnal z osi X: ", -1, &text, PointF(900, 260), &text2);

	graphics.DrawString(L"Sygnal z osi Y: ", -1, &text, PointF(900, 360), &text2);

	graphics.DrawString(L"Sygnal z osi Z: ", -1, &text, PointF(900, 460), &text2);


	//graphics.DrawLine(&pen, 0, 150, 401, 150);

	value++;

	if (value == 2304)
	{
		value = 1;
	}

	diag++;

	if (diag == 201)
	{
		diag = 1;
	}
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}	

int OnCreate(HWND window)
{
	SetTimer(window, TMR_1, 25, 0);
	inputData();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 40, 70, 40, hWnd, (HMENU)ID_BUTTON_TIMEUP, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 80, 70, 40, hWnd, (HMENU)ID_BUTTON_TIMEDOWN, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1070, 140, 70, 40, hWnd, (HMENU)ID_BUTTON_SCALEUP, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1070, 180, 70, 40, hWnd, (HMENU)ID_BUTTON_SCALEDOWN, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 240, 70, 40, hWnd, (HMENU)ID_BUTTON_VON, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 280, 70, 40, hWnd, (HMENU)ID_BUTTON_VOFF, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 340, 70, 40, hWnd, (HMENU)ID_BUTTON_AON, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 380, 70, 40, hWnd, (HMENU)ID_BUTTON_AOFF, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 440, 70, 40, hWnd, (HMENU)ID_BUTTON_SON, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 480, 70, 40, hWnd, (HMENU)ID_BUTTON_SOFF, hInstance, NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON_TIMEUP:
			break;
		case ID_BUTTON_TIMEDOWN:
			break;
		case ID_BUTTON_SCALEUP:
			break;
		case ID_BUTTON_SCALEDOWN:
			break;
		case ID_BUTTON_VON:
			break;
		case ID_BUTTON_VOFF:
			break;
		case ID_BUTTON_AON:
			break;
		case ID_BUTTON_AOFF:
			break;
		case ID_BUTTON_SON:
			break;
		case ID_BUTTON_SOFF:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			break;
		}

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
