#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <stack>

// Give each button a unique ID
#define MATH_BUTTON 100
#define THERMO_BUTTON 101
#define BACK_BUTTON 102
#define NEWTON_BUTTON 103
#define ROOT_BUTTON 104
#define ANAL_ROOT_BUTTON 105
#define LINEAR_CHECK 106
#define LIN_ROOT_CHECK 107

// A vector of all the handles to windows can represent each screen
typedef std::vector<HWND> screen;

// Screens to be used
screen home;
screen math;
screen roots;
screen analyticalRoots;

// Keep track of the current screen and all the previous screen
std::stack<screen*> prev;
screen* curr;

void goBack();
void goTo(screen*);
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
	curr = &home; // Start at the home screen

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
	TCHAR greeting[] = _T("Choose an application!");

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case MATH_BUTTON: // Each menu button will simply change the screen
			goTo(&math);
			break;
		case ROOT_BUTTON:
			goTo(&roots);
			break;
		case BACK_BUTTON:
			goBack();
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	
	return 0;
}

// Will go back one screen
void goBack()
{
	// If at home screen, do nothing
	if (prev.empty())
		return;

	for (int i = 0; i < curr->size(); i++) // Hide every window on the current screen
		ShowWindow(curr->at(i), SW_HIDE);
	for (int i = 0; i < prev.top()->size(); i++) // Show every window on the previous screen
		ShowWindow(prev.top()->at(i), SW_SHOW);
	curr = prev.top();							// Update the current screen
	prev.pop();									// Update the stack
}

// Will change the screen to the chosen screen
void goTo(screen* next)
{
	// If somehow the current screen was chosen, ignore
	if (next == curr)
		return;

	prev.push(curr); // Add the current screen to the stack
	for (int i = 0; i < curr->size(); i++) // Hide every window in the current screen
		ShowWindow(curr->at(i), SW_HIDE);
	for (int i = 0; i < next->size(); i++) // Show every window in the next screen
		ShowWindow(next->at(i), SW_SHOW);
	curr = next;						   // Update current screen
}