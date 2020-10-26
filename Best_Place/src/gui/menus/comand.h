//
//File: option.h
//
//Desc: Class of menu option
//

#pragma once

#include "../../render/data/sprite.h"
#include "../../math/vector.h"

#ifndef NDEBUG

namespace DebugMenu {

	class Comand{
		Vector _pos;			//Position
		float _width, _height;	//Size
		Sprite* _sprite;		//Optiob sprite
		Texture* _texture;		//Option texture

		void (*_comand)(Vector);	//Comand for execution
	public:
		Comand(Vector size, void (*comand)(Vector), const char* tex_src, IDirect3DDevice9* device);		//Constructor

		void SetPos(Vector pos);	//Change position

		void Draw();	//Draw option

		void Execute(Vector pos);			//Execute option

		Vector GetPos() { return _pos; }	//Get position

		~Comand();				//Destructor
	};
}

#endif // !NDEBUG
