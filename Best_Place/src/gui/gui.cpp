#include "gui.h"

namespace GUI {

	std::queue<std::string > String_Queue;	//Queue of strings to render

	void Init(const char* fontName, DWORD fHeight, IDirect3DDevice9* device, Camera* camptr) {
		if (GUISystem._textFont != nullptr) {
			//If there is already a text font release it
			delete GUISystem._textFont;
		}

		GUISystem._textFont = new Text(fontName, fHeight, device);

		//Init Debug Menus
		DebugMenu::InitMenu(device, camptr);
	}

	void SetWindowSize(Vector size) {
		DebugMenu::SetWindowSize(size);
	}

	void TextDraw(std::string text) {
		String_Queue.push(text);
	}

	void DrawAllText() {
		int row = 0;	//String row
		float y;		//Y position of string

		while (!String_Queue.empty()) {
			//Calculate Y position of actual string
			y = GUISystem._textFont->GetHeight() * row;
			row++;
			//Draw string
			const char* string = String_Queue.front().c_str();		//Get string
			GUISystem._textFont->Draw(TEXT_X, y, string);
			String_Queue.pop();									//Pop this string
		}
	}

	void DrawFPS() {
		std::string fpsText = "FPS: ";
		fpsText = fpsText + std::to_string(FPSTimer::GetFPS());
		
		TextDraw(fpsText);
	}

	void Update() {
		//Update debug menus
		DebugMenu::Update();

		//Draw all text
		DrawAllText();
	}

	void Release() {
		if (GUISystem._textFont != nullptr) {
			//If it is not emty release it
			delete GUISystem._textFont;
			GUISystem._textFont = nullptr;
		}
		
		//Release DebugMenus
		DebugMenu::Release();
	}
}