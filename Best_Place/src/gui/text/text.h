//
//File: text.h
//
//Desc: Class used for text rendering
//

#pragma once

#include "res/d3dfont.h"

#define TEXT_COLOR   0xffffffff

class Text {
	float _height = 0;			//Text height

	CD3DFont* _font = nullptr;	//Text font
public:
	Text(const char* fontName, DWORD fHeight, IDirect3DDevice9* device);	//Construct and initialize text class

	float GetHeight() { return _height; }	//Get text height

	void Draw(float x, float y, const char* string);	//Draw text

	void Release();	//Release Text class
	~Text();	//Destruct class text
};