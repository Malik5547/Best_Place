#pragma once

#include "shader.h"

//Vertex Shader class from shader class
class PixelShader : public Shader {
	D3DXHANDLE _textureHndl;					//Texture handle
	D3DXCONSTANT_DESC _textureDesc;				//Texture description
	UINT _textureCount;							//Texture count
	
	IDirect3DPixelShader9* _shader = nullptr;	//Our vertex shader
public:
	PixelShader() {}

	bool Create(IDirect3DDevice9* device);	//Create vertex shader

	bool SetTexture(IDirect3DDevice9* device, IDirect3DTexture9* texture);	//Set texture

	IDirect3DPixelShader9* GetShader() { return _shader; }		//Get our vertex shader

	void Release();
	~PixelShader();
};