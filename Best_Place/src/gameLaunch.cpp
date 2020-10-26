#include "game.h"

Window gameWindow(800, 500);
Game myGame;


// Wraps the message loop code.
int  Run();

// The window procedure, handles events our window
// receives.
LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

// Windows equivalant to main()
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR      pCmdLine,
	int       nShowCmd)
{
	
	//Initialize or window
	gameWindow.Init(hInstance, nShowCmd, WndProc);

	//Initialize our game whit window
	myGame.Init(&gameWindow);

	// Once our application has been created and 
	// initialized we enter the message loop.  We
	// stay in the message loop until a WM_QUIT
	// mesage is received, indicating the application
	// should be terminated.
	return Run(); // enter message loop
}

int Run()
{
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	//Last time stamp
	static float lastTime = (float)timeGetTime();

	// Loop until we get a WM_QUIT message.  The
	// function GetMessage will only return 0 (false)
	// when a WM_QUIT message is received, which
	// effectively exits the loop.
	while (true)
	{
		if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				myGame.Release();
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else {
			float currTime = (float)timeGetTime();	//Current time stamp
			//Time delta
			float timeDelta = (currTime - lastTime) * 0.001f;

			myGame.Run(timeDelta);

			//Set last time
			lastTime = currTime;
		}
			// run game code
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND   windowHandle,
	UINT   msg,
	WPARAM wParam,
	LPARAM lParam)
{
	//First check if the key is for game input
	Input::KeyHandle(msg, wParam);

	//Mouse position
	Vector mPos;

	// Handle some specific messages:
	switch (msg)
	{
		// In the case the left mouse button was pressed,
		// then display a message box.
	case WM_LBUTTONDOWN:
		//GetCursorPos(&point);
		//ScreenToClient(windowHandle, &point);
		//point = MAKEPOINTS(wParam);
		mPos = { (float)LOWORD(lParam), (float)HIWORD(lParam) };
		//mPos = { (float)point.x, (float)point.y };

		DebugMenu::MouseClick(mPos, CLICK_LEFT);
		
		return 0;

		// In the case the escape key was pressed, then
		// destroy the main application window, which is
		// identified by MainWindowHandle.
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(windowHandle);
		return 0;

		// In the case of a destroy message, then
		// send a quit message, which will terminate
		// the message loop.
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	// Forward any other messages we didn't handle
	// above to the default window procedure.
	return ::DefWindowProc(windowHandle,
		msg,
		wParam,
		lParam);
}
