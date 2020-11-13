#include "pixelShader.h"

bool PixelShader::Create(IDirect3DDevice9* device) {
	HRESULT hr = 0;		//Save function's return

	//Shder class should be already compiled
	if (_compShader == nullptr) {
		::MessageBox(0, "Error. Pixel shader is not compiled.", 0, 0);
		return false;
	}

	//
	// Create shader
	//

	hr = device->CreatePixelShader(
		(DWORD*)_compShader->GetBufferPointer(),
		&_shader);

	if (FAILED(hr))
	{
		::MessageBox(0, "CreatePixelShader - FAILED", 0, 0);
		return false;
	}
	//Release the shader's compilation
	_compShader->Release();

	//
	//Get handles
	//
	_textureHndl = _constTable->GetConstantByName(0, "Texture");
	_reversed = _constTable->GetConstantByName(0, "Reverse");
	_leftRightU = _constTable->GetConstantByName(0, "LeftRightU");
	//Set defaults
	_constTable->SetDefaults(device);

	//
	//Get texture descriptions
	//
	_constTable->GetConstantDesc(_textureHndl, &_textureDesc, &_textureCount);

	return true;
}

bool PixelShader::SetInverseDraw(IDirect3DDevice9* device, bool val) {
	HRESULT hr;

	hr = _constTable->SetBool(device, _reversed, val);

	if (FAILED(hr))
		return false;

	return true;
}

bool PixelShader::SetLeftRightU(IDirect3DDevice9* device, Vector leftRightU) {
	HRESULT hr;
	float UV[2] = { leftRightU.x , leftRightU.y };

	hr = _constTable->SetFloatArray(device, _leftRightU, UV, 2);

	if (FAILED(hr))
		return false;

	return true;
}

bool PixelShader::SetTexture(IDirect3DDevice9* device, IDirect3DTexture9* texture) {
	//Set texture to shader

	if (FAILED(device->SetTexture(_textureDesc.RegisterIndex, texture)))
		return false;

	return true;
}

void PixelShader::Release() {
	//Release our shader
	if (_shader != nullptr)
		_shader->Release();
	//Release our constant table
	if (_constTable != nullptr)
		_constTable->Release();
}

PixelShader::~PixelShader() {
	Release();
}