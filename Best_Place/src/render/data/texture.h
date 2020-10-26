//
//File: texture.h
//
//Desc: Class Texture describes a texture
//

#pragma once

#include <d3dx9.h>

#define MISSING_TEXTURE "src/data/missing.png"

//Struct for returning the texture size
struct Texture_Size {
	int width, height;
};

class Texture {
	IDirect3DTexture9* _texture = nullptr;	//The texture
	int _width, _height;			//Texture width and height

	bool Load(const char* src, IDirect3DDevice9* device);	//Load a texture
public:
	Texture(const char* src, IDirect3DDevice9* device);	//Construct a texture
	
	IDirect3DTexture9* GetTexture() { return _texture; }	//Get the actual texture
	Texture_Size GetSize() { return { _width, _height }; }	//Get the texture size

	void Release();				//Release texture
	~Texture();					//Destruct a texture
};