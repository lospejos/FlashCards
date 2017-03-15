#ifndef UNICODE
#define UNICODE
#endif 

// Description for a function or a variable (will be shown when hovering over function/variable)
/// General code description (won't be shown when hovering)

#pragma comment (lib, "d2d1")
#include <windows.h>
#include <d2d1.h>

/// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CalculateLayout();
HRESULT CreateGraphicsResources();
void DiscardGraphicsResources();
void OnPaint();
void Resize();


// Holds information about the current state of the window
struct StateInfo {
	// members
};

// Get the stored StateInfo pointer back from the window
inline StateInfo* GetApplicationState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);	/// Get the stored StateInfo pointer back from the window
	StateInfo* pStateInfo = reinterpret_cast<StateInfo*>(ptr);
	return pStateInfo;
}

// SafeRelease to call Release on D2D1 resource pointers
template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

/// Global variables
HWND hwnd;
ID2D1Factory *pFactory = NULL;		// Used to create other objects (render targets, stroke styles, geometries)
ID2D1HwndRenderTarget *pRenderTarget = NULL;	/// COM object that typically targets the client area of the window; Creates brushes, bitmaps and meshes
ID2D1SolidColorBrush *pBrush = NULL;	/// COM object that controls how lines and regions are painted (solid-color brushes / gradiant brushes)
D2D1_ELLIPSE ellipse;

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
	hwnd = CreateWindowEx(
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

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);	/// Initialize the COM (Component Object Model) library e.g. for Open Dialog Box, single-threaded
	if (FAILED(hr))
		return 0;

	ShowWindow(hwnd, nCmdShow);		// Show the window

	/// Run the message loop until the user exits the application
	MSG msg = {};	// Message struct that contains a message
	while (GetMessage(&msg, NULL, 0, 0))	/// Remove message from the head of the message queue (possible to filter messages)
	{
		TranslateMessage(&msg);	/// Translates keystrokes into characters
		DispatchMessage(&msg);	/// Invokes the WindowProc function once for each message
	}

	CoUninitialize();	/// Uninitialize the COM Library
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

		/// Create the Direct2D factory object, must be done before first WM_PAINT message
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
			return -1;	/// Fail CreateWindowEx
		return 0;
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
			DiscardGraphicsResources();
			SafeRelease(&pFactory);
			PostQuitMessage(0);		/// Post a WM_QUIT message on the message queue, GetMessage returns 0 and the program ends
			return 0;
		}

		/// Repaint the client area of the window
		case WM_PAINT:
		{
			OnPaint();
			return 0;
		}

		case WM_SIZE:
		{
			Resize();
			return 0;
		}

		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);	/// Handles all unhandled messages with a default action
}

void CalculateLayout ()
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

HRESULT CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		/// Creates the render target for a window; Implicitly created the device for drawing the pixels, too; Returns S_OK if the target already exists
		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),					// Default options for the type of render target
			D2D1::HwndRenderTargetProperties(hwnd, size),	// Window handle
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);		// Create a solid-color brush

			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}
	}
	return hr;
}

void DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}

void OnPaint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
		pRenderTarget->FillEllipse(ellipse, pBrush);

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(hwnd, &ps);
	}
}

void Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(hwnd, NULL, FALSE);
	}
}