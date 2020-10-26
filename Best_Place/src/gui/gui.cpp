#include "gui.h"

namespace GUI {

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

	void GUIText(const char* string) {
		//Get y position of actual row
		float y = GUISystem._textFont->GetHeight() * GUISystem._row;
		//Render text
		GUISystem._textFont->Draw(TEXT_X, y, string);
		//Update row
		GUISystem._row++;
	}

	void DrawFPS() {
		std::string fpsText = "FPS: ";
		fpsText = fpsText + std::to_string(FPSTimer::GetFPS());
		
		GUIText(fpsText.c_str());
	}

	void Update() {
		//Update debug menus
		DebugMenu::Update();

		GUISystem._row = 1; 
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