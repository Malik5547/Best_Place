//
//File: gui.h
//
//Desc: Class gui is used to draw all gui elements
//

#pragma once

#include <string>
#include "menus/debugMenus.h"
#include "text/text.h"
#include "fpsCount.h"
#include <queue>

namespace GUI {

#define TEXT_X	10	//X position for text

	class {
	//	int _row = 1;				//Row for text drawing
		Text* _textFont = nullptr;	//Text Render for text drawing

		friend void Init(const char* fontName, DWORD fHeight, IDirect3DDevice9* device, Camera* camptr);
		friend void DrawAllText();
		friend void Update();
		friend void Release();
	}GUISystem;

	void Init(const char* fontName, DWORD fHeight, IDirect3DDevice9* device, Camera* camptr);	//Init text font

	void SetWindowSize(Vector size);

	void TextDraw(std::string text);	//Send string to queue for drawing
	void DrawAllText();					//Draw all strings from the queue

	void DrawFPS();	//Draw FPS

	void Update();	//Update gui and draw it

	void Release();	//Release resources
}