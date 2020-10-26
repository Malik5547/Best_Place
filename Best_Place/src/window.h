#pragma once


#define WIND_NAME "Best Place"


#include <Windows.h>

class Window {
	WNDPROC _WndProc;		//Window procedure
	HINSTANCE _hInstance;	//Instance handle
	HWND _whndl;			//Window handle
	int _width, _height;	//Width and height
	bool _windowed;			//Windowed mode
public:
	Window(int width, int height, bool windowed = true);

	bool Init(HINSTANCE hInst, int show, WNDPROC WndProc);

	HWND GetHndl() { return _whndl; }
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }

	bool IsWindowed() {	return _windowed;}
};