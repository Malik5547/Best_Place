//
//File: debugMenus.h
//
//Desc: This are debug menus
//

#pragma once

#include "../text/text.h"
#include "comand.h"
#include "comands.h"
#include "../../components/objects/mesh.h"
#include "../../render/camera/camera.h"
#include <vector>


#ifndef NDEBUG 

namespace DebugMenu {

	//Mouse click codes
#define CLICK_LEFT		1
#define CLICK_RIGHT		2

	//Option size
#define OPTION_WIDTH	200.0f
#define OPTION_HEIGHT	30.0f

#define COMAND(x)	Menu._comands[x]

	class {
		std::vector<Comand*> _comands;			//Menu's options
		Vector _winSize;						//Windows size
		Vector _pos;							//Menu position
		Mesh*	_mesh;							//Menu's mesh
		float _width, _height;					//Menu size

		bool _active = false;					//Is menu active
	public:
		friend void InitMenu(IDirect3DDevice9* device, Camera* camptr);	//Init comands
		friend void SetWindowSize(Vector size);

		friend void CreateMenu(Vector mPos);			//Create menu on mouse position
		friend void Update();
		friend void Draw();	 //Draw menu

		friend void ExecuteCom(Vector pos, Comand* com);

		friend void MouseClick(Vector pos, char event);
		friend void Release();
	} Menu;

	void InitMenu(IDirect3DDevice9* device, Camera* camptr);		//Init comands
	void SetWindowSize(Vector size);

	void CreateMenu(Vector mPos);			//Create menu on mouse position

	void Update();	//Update menu. Used in render
	static void Draw();	 //Draw menu

	void ExecuteCom(Vector pos, Comand* com);
	
	void MouseClick(Vector pos, char event);		//Process mouse clicks
	
	void Release();	//Release data

}

#endif	//NDEBUG