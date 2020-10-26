#include "text.h"

Text::Text(const char* fontName, DWORD fHeight, IDirect3DDevice9* device) {
	//Create font
	_font = new CD3DFont(fontName, fHeight, 0);
	_height = (float)fHeight;

	//Initialize font
	_font->InitDeviceObjects(device);
	_font->RestoreDeviceObjects();
}

void Text::Draw(float x, float y, const char* string) {
	_font->DrawText(x, y, TEXT_COLOR, string);
}

void Text::Release() {
	//Clean font
	_font->InvalidateDeviceObjects();
	_font->DeleteDeviceObjects();
}

Text::~Text() {
	if (_font != nullptr) {
		//If there is a font, release it
		Release();
		delete _font;

		_font = nullptr;
	}
}