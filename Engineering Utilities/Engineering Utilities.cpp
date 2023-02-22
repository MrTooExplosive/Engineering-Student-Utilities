#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include "screen.h"

auto count = 0;

// Give each button a unique ID
#define MATH_BUTTON 100
#define THERMO_BUTTON 101
#define BACK_BUTTON 102
#define NEWTON_BUTTON 103
#define ROOT_BUTTON 104
#define ANAL_ROOT_BUTTON 105
#define LINEAR_FUNC_CHECK 108
#define QUADRATIC_FUNC_CHECK 109
#define CUBIC_FUNC_CHECK 110
#define QUARTIC_FUNC_CHECK 111

// Screens to be used
screen home(L"Choose an application.");
screen math(L"Choose an application.");
screen roots(L"Choose an application.");
screen analyticalRoots(L"Choose a type of function.");

LRESULT CALLBACK WndProc(_In_ HWND, _In_ UINT, _In_ WPARAM, _In_ LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Define window
	static TCHAR szWindowClass[] = _T("DesktopApp");
	static TCHAR szTitle[] = _T("Engineering Utilities");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Engineering Utilities"), NULL);
		return 1;
	}

	// Create window handler
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		700, 700,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("Engineering Utilities"), NULL);
		return 1;
	}

	// Make all the buttons
	// Math functionality
	HWND mathButton = CreateWindow(
		L"BUTTON",
		L"Mathematics",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT,
		1, 25,
		125, 125,
		hWnd,
		(HMENU)MATH_BUTTON,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);
	// Thermodynamics functionality
	HWND thermoButton = CreateWindow(
		L"BUTTON",
		L"Thermodynamics",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT,
		131, 25,
		125, 125,
		hWnd,
		(HMENU)THERMO_BUTTON,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);
	// Simple Newtonian Physics button
	HWND introPhysButton = CreateWindow(
		L"BUTTON",
		L"Basic Newtonian\nMechanics",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT | BS_MULTILINE,
		261, 25,
		125, 125,
		hWnd,
		(HMENU)NEWTON_BUTTON,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	// Add all the main buttons to the home screen
	home.push_back(introPhysButton);
	home.push_back(thermoButton);
	home.push_back(mathButton);
	screen::setStart(&home);

	// Button for finding the roots of functions
	HWND findRootsButton = CreateWindow(
		L"BUTTON",
		L"Root Finder",
		WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT,
		1, 25,
		125, 125,
		hWnd,
		(HMENU)ROOT_BUTTON,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	math.push_back(findRootsButton);

	// Analytical solutions to equations with certain forms
	HWND analyticalRootButton = CreateWindow(
		L"BUTTON",
		L"Analytically",
		WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT,
		1, 25,
		125, 125,
		hWnd,
		(HMENU)ANAL_ROOT_BUTTON,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	roots.push_back(analyticalRootButton);

	// Radio buttons to get the type of polynomial
	HWND linearCheck = CreateWindow(
		L"BUTTON",
		L"Linear",
		WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP | BS_TEXT,
		1, 25,
		100, 25,
		hWnd,
		(HMENU)LINEAR_FUNC_CHECK,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	HWND quadraticCheck = CreateWindow(
		L"BUTTON",
		L"Quadratic",
		WS_CHILD | BS_AUTORADIOBUTTON | BS_TEXT,
		1, 55,
		100, 25,
		hWnd,
		(HMENU)QUADRATIC_FUNC_CHECK,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	HWND cubicCheck = CreateWindow(
		L"BUTTON",
		L"Cubic",
		WS_CHILD | BS_AUTORADIOBUTTON | BS_TEXT,
		1, 85,
		100, 25,
		hWnd,
		(HMENU)CUBIC_FUNC_CHECK,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	HWND quarticCheck = CreateWindow(
		L"BUTTON",
		L"Quartic",
		WS_CHILD | BS_AUTORADIOBUTTON | BS_TEXT,
		1, 115,
		100, 25,
		hWnd,
		(HMENU)QUARTIC_FUNC_CHECK,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	analyticalRoots.push_back(quarticCheck);
	analyticalRoots.push_back(cubicCheck);
	analyticalRoots.push_back(linearCheck);
	analyticalRoots.push_back(quadraticCheck);
	CheckRadioButton(hWnd, LINEAR_FUNC_CHECK, QUARTIC_FUNC_CHECK, QUARTIC_FUNC_CHECK);


	// A back button that will always show no matter the current screen
	HWND backButton = CreateWindow(
		L"BUTTON",
		L"<-",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_TEXT,
		650, 5,
		20, 20,
		hWnd,
		(HMENU)BACK_BUTTON,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	// Display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Deal with messages
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MATH_BUTTON: // Each menu button will simply change the screen
			screen::goTo(&math, hWnd);
			break;
		case ROOT_BUTTON:
			screen::goTo(&roots, hWnd);
			break;
		case ANAL_ROOT_BUTTON:
			screen::goTo(&analyticalRoots, hWnd);
			break;
		case BACK_BUTTON:
			screen::goBack(hWnd);
			break;
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, (LPCWSTR)(screen::getCurr()->getText().c_str()), screen::getCurr()->getText().length());
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	
	return 0;
}