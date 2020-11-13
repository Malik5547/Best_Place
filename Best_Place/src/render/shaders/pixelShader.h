#pragma once

#include "shader.h"

//Vertex Shader class from shader class
class PixelShader : public Shader {
	D3DXHANDLE _textureHndl;					//Texture handle
	D3DXCONSTANT_DESC _textureDesc;				//Texture description
	UINT _textureCount;							//Texture count

	D3DXHANDLE _reversed;				//Is texture reversed
	D3DXHANDLE _leftRightU;				//Left and right U coord handle for texture inverse
	
	IDirect3DPixelShader9* _shader = nullptr;	//Our vertex shader
public:
	PixelShader() {}

	bool Create(IDirect3DDevice9* device);	//Create vertex shader

	bool SetInverseDraw(IDirect3DDevice9* device, bool value);		//Set inverse draw(inverse texture)
	bool SetLeftRightU(IDirect3DDevice9* device, Vector leftRightU);	//Set left and right U coord

	bool SetTexture(IDirect3DDevice9* device, IDirect3DTexture9* texture);	//Set texture

	IDirect3DPixelShader9* GetShader() { return _shader; }		//Get our vertex shader

	void Release();
	~PixelShader();
};