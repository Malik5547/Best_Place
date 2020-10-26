#include "debugMenus.h"

#ifndef NDEBUG

namespace DebugMenu {
	
	//Camera for position transformation
	Camera* GameCam = nullptr;

	void InitMenu(IDirect3DDevice9* device, Camera* camptr) {

		//
		//Comands initialization
		//
		Comand* platform = new Comand({ OPTION_WIDTH, OPTION_HEIGHT }, &Comands::SpawnPlatform , SPAWNPL_TEX, device);
		Comand* icePlatform = new Comand({ OPTION_WIDTH, OPTION_HEIGHT }, &Comands::SpawnIcePlatform, SPAWNIPL_TEX, device);
		Comand* dummyPlatform = new Comand({ OPTION_WIDTH, OPTION_HEIGHT }, &Comands::SpawnDummyPlatform, SPAWNDPL_TEX, device);
		Comand* jumpPlatform = new Comand({ OPTION_WIDTH, OPTION_HEIGHT }, &Comands::SpawnJumpPlatform, SPAWNJPL_TEX, device);

		//Add comands to menu
		Menu._comands.push_back(platform);
		Menu._comands.push_back(icePlatform);
		Menu._comands.push_back(dummyPlatform);
		Menu._comands.push_back(jumpPlatform);

		//
		//Menu initialization
		//
		Menu._width = OPTION_WIDTH;
		Menu._height = OPTION_HEIGHT * Menu._comands.size();

		//Create menu mesh
		Menu._mesh = new Mesh({ 0.0f, 0.0f }, Menu._width, Menu._height);

		//Set camera ptr
		GameCam = camptr;
	}

	void SetWindowSize(Vector size) {
		Menu._winSize = size;
	}

	void CreateMenu(Vector mPos) {
		Menu._pos = { mPos.x, mPos.y - Menu._height };

		for (unsigned int i = 0; i < Menu._comands.size(); i++) {
			//Set position for every comand
			COMAND(i)->SetPos({ Menu._pos.x, Menu._pos.y + Menu._height - ((i + 1) * OPTION_HEIGHT) });
		}

		Menu._mesh->SetPosition(Menu._pos);

		Menu._active = true;
	}

	void Update() {
		if (Menu._active == true) {
			//If the menu is active draw it
			Draw();
		}
	}

	void Draw() {
		for (unsigned int i = 0; i < Menu._comands.size(); i++) {
			//Draw eatch comand
			COMAND(i)->Draw();
		}
	}

	void ExecuteCom(Vector pos, Comand* com) {
		if (GameCam != nullptr) {
			//Transform mouse position into screen position
			pos.x = pos.x * 2 / Menu._winSize.x - 1.0f;
			pos.y = pos.y * 2 / Menu._winSize.y - 1.0f;
			//Transform screen position to world position
			pos *= GameCam->GetDist();
			pos.x += GameCam->GetX();
			pos.y += GameCam->GetY();
			
			com->Execute(pos);
		}
		else {
			::MessageBox(0, "Not set camera in debugMenu.", 0, 0);
		}
	}

	void MouseClick(Vector pos, char event) {
		//Invert mouse Y position
		pos.y = Menu._winSize.y - pos.y  + 1.0f;

		//Normalize position
		//pos.x = pos.x * 2 / Menu._winSize.x - 1.0f;
		//pos.y = pos.y * 2 / Menu._winSize.y - 1.0f;

		if (Menu._active != true) {
			//If there is no menu, create it 
			CreateMenu(pos);
		}
		else {
			if (Menu._mesh->DotColide(pos)) {
				//Check if the mouse click on a comand

				//Get the index of clicked comand
				int i = (int)((pos.y - Menu._pos.y) / OPTION_HEIGHT);
				i = Menu._comands.size() - i - 1;

				ExecuteCom({Menu._pos.x, Menu._pos.y + Menu._height}, COMAND(i));
				//const char* text = Menu._comands[i]->GetDesc();
				//::MessageBox(0, text, 0, 0);
			}
			else {
				//Close menu
				Menu._active = false;
			}

			Menu._active = false;
		}
	}

	void Release() {
		//Delete comands
		for (unsigned int i = 0; i < Menu._comands.size(); i++) {
			delete COMAND(i);
		}
		Menu._comands.clear();
		delete Menu._mesh;
	}
}

#endif	//NDEBUG Not debug