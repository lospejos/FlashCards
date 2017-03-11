#ifndef UNICODE
#define UNICODE
#endif 

// Description for a function or a variable (will be shown when hovering over function/variable)
/// General code description (won't be shown when hovering)

#include <windows.h>

// Holds information about the current state of the window
struct StateInfo {
	// members
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
inline StateInfo* GetApplicationState(HWND hwnd);

// hInstance: handle for the .exe, hPrevInstance: no meaning, pCmdLine: unicode command line arguments, nCmdShow: flag for minimalizes, maximalized or normal
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	/// Register the window class.
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	// Data structure used internally by the operating system that defines a set of behaviors that several windows might have in common (each window must have a window class)
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;	/// Pointer to the window proceidure function
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;	/// Identifies the window class, make sure it has no conflict with control class names like "Button"

	RegisterClass(&wc);		//registers the window class with the operating system

	StateInfo* pStateInfo = new StateInfo;	/// Create a StateInfo object that contains the current state information
	if (pStateInfo == NULL)
		return 0;

	// Unique window handle identifier
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles like transparency
		CLASS_NAME,                     // Window class name, defines the type of window to create
		L"Learn to Program Windows",    // Window text, usually displayed in title bar
		WS_OVERLAPPEDWINDOW,            // Window style, combined set of bit flags that define the look and feel of the window
		CW_USEDEFAULT,					// Position X
		CW_USEDEFAULT,					// Position Y
		CW_USEDEFAULT,					// Size X
		CW_USEDEFAULT,					// Size Y
		NULL,							// Parent/owner window
		NULL,							// Menu
		hInstance,						// Instance handle
		pStateInfo						// Additional application data of type void* that can be extracted in WM_NCCREATE or WM_CREATE through the lParam (CREATESTRUCT structure)
	);

	/// Exit when the window creation failed
	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);		// Show the window

	/// Run the message loop until the user exits the application
	MSG msg = {};	// Message struct that contains a message
	while (GetMessage(&msg, NULL, 0, 0))	/// Remove message from the head of the message queue (possible to filter messages)
	{
		TranslateMessage(&msg);	/// Translates keystrokes into characters
		DispatchMessage(&msg);	/// Invokes the WindowProc function once for each message
	}

	return 0;
}

// Window Procedure: Defines the behavior of the window: appearance, user events and operating system events, ...
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	StateInfo* pStateInfo;
	if (uMsg == WM_CREATE)
	{
		/// Get the pointer to the StateInfo structure form the void* added in CreateWindowEx(...)
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pStateInfo = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pStateInfo);	/// Store the StateInfo pointer in the instance data for the window
	}
	else
	{
		pStateInfo = GetApplicationState(hwnd);
	}

	switch (uMsg)
	{
		case WM_CLOSE:
		{
			if (MessageBox(hwnd, L"Do you really want to quit this awesome application? >_<", L"Awesome application", MB_OKCANCEL) == IDOK)
				DestroyWindow(hwnd);
			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);		/// Post a WM_QUIT message on the message queue, GetMessage returns 0 and the program ends
			return 0;
		}

		/// Repaint the client area of the window
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);	/// Fill the structure with information about the repaint request, update region
			/// Paint either only the update region rcPaint or the whole client area
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));		/// Paint the update region with a single color
			EndPaint(hwnd, &ps);	/// Clear the update region
		}

		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	/// Handles all unhandled messages with a default action
}

// Get the stored StateInfo pointer back from the window
inline StateInfo* GetApplicationState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);	/// Get the stored StateInfo pointer back from the window
	StateInfo* pStateInfo = reinterpret_cast<StateInfo*>(ptr);
	return pStateInfo;
}