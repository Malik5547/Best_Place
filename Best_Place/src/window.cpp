#include "window.h"

Window::Window(int width, int height, bool windowed) {
	_width = width;
	_height = height;
	_windowed = windowed;
}

bool Window::Init(HINSTANCE hInst, int show, WNDPROC WndProc) {
	_hInstance = hInst;
	_WndProc = WndProc;

	// The first task to creating a window is to describe
	// its characteristics by filling out a WNDCLASS 
	// structure.
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = _WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInstance;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground =
		static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = 0;
	wc.lpszClassName = WIND_NAME;

	// Then we register this window class description 
	// with Windows so that we can create a window based
	// on that description.
	if (!::RegisterClass(&wc))
	{
		::MessageBox(0, "RegisterClass - Failed", 0, 0);
		return false;
	}

	// With our window class description registered, we
	// can create a window with the CreateWindow function.
	// Note, this function returns a HWND to the created
	// window, which we save in MainWindowHandle.  Through
	// MainWindowHandle we can reference this particular
	// window we are creating.

	//Calculating window size
	RECT rc = { 0, 0, _width, _height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	int windowWidth = rc.right - rc.left;
	int windowHeight = rc.bottom - rc.top;

	_whndl = ::CreateWindow(
		WIND_NAME,
		WIND_NAME,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		windowWidth,
		windowHeight,
		0,
		0,
		_hInstance,
		0);

	if (_whndl == 0)
	{
		::MessageBox(0, "CreateWindow - Failed", 0, 0);
		return false;
	}

	// Finally we show and update the window we just created.
	// Observe we pass MainWindowHandle to these functions so
	// that these functions know what particular window to 
	// show and update.
	::ShowWindow(_whndl, show);
	::UpdateWindow(_whndl);

	return true;
}