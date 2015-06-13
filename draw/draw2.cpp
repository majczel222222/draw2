// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <fstream>
#include <string>
#include <math.h>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
INT skalay = 10;
INT skalax = 3;

bool rysujx = false, rysujy = false, rysujz = false, rysujg = false;

// buttons
HWND hwndButton;

std::vector<int> data_x;
std::vector<int> data_y;
std::vector<int> data_z;
std::vector<int> data_g;

RECT drawArea1 = { 0, 0, 1400, 900 };
RECT drawArea2;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);




void inputData()
{
	std::ifstream source_file;

	double a_x, a_y, a_z, g;

	std::string file_name = "outputRobotForwardB02.log";
	std::string useless_data;

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

		source_file >> a_x >> a_y >> a_z;

		a_x = a_x * 1000;
		a_y = a_y * 1000;
		a_z = a_z * 1000;
		g = sqrt(((a_x)*(a_x)) + (a_y)*(a_y)) + ((a_z)*(a_z));

		getline(source_file, useless_data);

		useless_data.clear();

		data_x.push_back(a_x);
		data_y.push_back(a_y);
		data_z.push_back(a_z);
		data_g.push_back(g);

	}	


	source_file.close();

}

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);

	Pen pen(Color(255, 0, 0, 0), 1);
	Pen pen_1(Color(255, 255, 0, 0), 1);
	Pen pen_2(Color(255, 0, 255, 0), 1);
	Pen pen_3(Color(255, 0, 0, 255), 1);
	Pen pen_4(Color(255, 255, 0, 255), 1);

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

	graphics.DrawLine(&pen, 0, 280, 2304, 280);
	graphics.DrawLine(&pen, 0, 380, 2304, 380);
	graphics.DrawLine(&pen, 0, 480, 2304, 480);
	graphics.DrawLine(&pen, 0, 580, 2304, 580);

	for (int i = 1; i < 2304; i++)
	{

		if (rysujx) graphics.DrawLine(&pen_1, (i - 1) / skalax, 280 - (data_x[i - 1] / skalay), i / skalax, 280 - (data_x[i] / skalay));
		if (rysujy) graphics.DrawLine(&pen_2, (i - 1) / skalax, 316 - (data_y[i - 1] / skalay), i / skalax, 316 - (data_y[i] / skalay));
		if (rysujz) graphics.DrawLine(&pen_3, (i - 1) / skalax, 404 - (data_z[i - 1] / skalay), i / skalax, 404 - (data_z[i] / skalay));
		if (rysujg) graphics.DrawLine(&pen_4, (i - 1) / skalax, 504 - (data_g[i - 1] / skalay), i / skalax, 504 - (data_g[i] / skalay));
	}


	//	for (int i = 1; i < wykres; i++)
	//	{
	//		graphics.DrawLine(&pen2, data[i - 1].X, data[i - 1].Y, data[i].X, data[i].Y);
	//	};

	graphics.DrawString(L"Podzialka czasowa: ", -1, &text, PointF(900, 60), &text2);

	graphics.DrawString(L"Amplituda : ", -1, &text, PointF(900, 160), &text2);

	graphics.DrawString(L"Sygnal z osi X: ", -1, &text, PointF(900, 260), &text2);

	graphics.DrawString(L"Sygnal z osi Y: ", -1, &text, PointF(900, 360), &text2);

	graphics.DrawString(L"Sygnal z osi Z: ", -1, &text, PointF(900, 460), &text2);

	graphics.DrawString(L"G: ", -1, &text, PointF(900, 560), &text2);


	//graphics.DrawLine(&pen, 0, 150, 401, 150);

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

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 40, 70, 40, hWnd, (HMENU)ID_BUTTON_Podzialka_plus, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 80, 70, 40, hWnd, (HMENU)ID_BUTTON_Podzialka_minus, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1070, 140, 70, 40, hWnd, (HMENU)ID_BUTTON_Amplituda_plus , hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1070, 180, 70, 40, hWnd, (HMENU)ID_BUTTON_Amplituda_minus , hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 240, 70, 40, hWnd, (HMENU)ID_BUTTON_Os_x_wlacz, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 280, 70, 40, hWnd, (HMENU)ID_BUTTON_Os_x_wylacz, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 340, 70, 40, hWnd, (HMENU)ID_BUTTON_Os_y_wlacz, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 380, 70, 40, hWnd, (HMENU)ID_BUTTON_Os_y_wylacz, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 440, 70, 40, hWnd, (HMENU)ID_BUTTON_Os_z_wlacz, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 480, 70, 40, hWnd, (HMENU)ID_BUTTON_Os_z_wylacz, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Wlacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 540, 70, 40, hWnd, (HMENU)ID_BUTTON_G_wlacz, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Wylacz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1100, 580, 70, 40, hWnd, (HMENU)ID_BUTTON_G_wylacz, hInstance, NULL);

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
		case ID_BUTTON_Podzialka_plus:
			skalax--; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Podzialka_minus:
			skalax++; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Amplituda_plus:
			skalay--;  repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Amplituda_minus:
			skalay++; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Os_x_wlacz:
			rysujx = true; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Os_x_wylacz:
			rysujx = false; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Os_y_wlacz:
			rysujy = true; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Os_y_wylacz:
			rysujy = false; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Os_z_wlacz:
			rysujz = true; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Os_z_wylacz:
			rysujz = false; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_G_wlacz:
			rysujg = true; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_G_wylacz:
			rysujg = false; repaintWindow(hWnd, hdc, ps, &drawArea1);
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
