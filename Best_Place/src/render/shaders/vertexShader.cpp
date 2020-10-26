#include "vertexShader.h"

bool VertexShader::Create(IDirect3DDevice9* device) {
	HRESULT hr = 0;		//Save function's return

	//Shder class should be already compiled
	if (_compShader == nullptr) {
		::MessageBox(0, "Error. Vertex shader is not compiled.", 0, 0);
		return false;
	}

	//
	// Create shader
	//

	hr = device->CreateVertexShader(
		(DWORD*)_compShader->GetBufferPointer(),
		&_shader);

	if (FAILED(hr))
	{
		::MessageBox(0, "CreateVertexShader - FAILED", 0, 0);
		return false;
	}
	//Release the shader's compilation
	_compShader->Release();

	//
	//Get handles
	//

	_viewVecHndl = _constTable->GetConstantByName(0, "ViewVect");
	_viewDistHndl = _constTable->GetConstantByName(0, "ViewDist");
	_vertexProcHndl = _constTable->GetConstantByName(0, "VertexProcces");
	_scaleVectHndl = _constTable->GetConstantByName(0, "ScaleVect");
	_centerVectHndl = _constTable->GetConstantByName(0, "SpriteCenter");
	//Set defaults
	_constTable->SetDefaults(device);

	return true;
}

bool VertexShader::SetWindowSize(IDirect3DDevice9* device, int width, int height) {
	HRESULT hr;		//Result

	//Get handles
	D3DXHANDLE winWidth = _constTable->GetConstantByName(0, "WinWidth");
	D3DXHANDLE winHeight = _constTable->GetConstantByName(0, "WinHeight");
	//Set window size
	hr = _constTable->SetInt(device, winWidth, width);
	if (FAILED(hr)) {
		::MessageBox(0, "Error. Couldn't set window width int vertex shader.", 0, 0);
		return false;
	}

	hr = _constTable->SetInt(device, winHeight, height);
	if (FAILED(hr)) {
		::MessageBox(0, "Error. Couldn't set window height int vertex shader.", 0, 0);
		return false;
	}

	return true;
}

bool VertexShader::SetVertexProc(IDirect3DDevice9* device, unsigned int val) {
	HRESULT hr;

	hr = _constTable->SetInt(device, _vertexProcHndl, val);
	if (FAILED(hr)) {
		::MessageBox(0, "Error. Couldn't set vertex process to vertex shader.", 0, 0);
		return false;
	}

	return true;
}

bool VertexShader::SetViewPos(IDirect3DDevice9* device, float x, float y) {
	HRESULT hr;
	float pos[2] = { x, y };

	//Set vector
	hr = _constTable->SetFloatArray(device, _viewVecHndl, pos, 2);
	
	if (FAILED(hr))
		return false;

	return true;
}

bool VertexShader::SetViewDist(IDirect3DDevice9* device, float dist) {
	HRESULT hr;

	//Set distance
	hr = _constTable->SetFloat(device, _viewDistHndl, dist);

	if (FAILED(hr))
		return false;

	return true;
}

bool VertexShader::SetScaleVect(IDirect3DDevice9* device, float x, float y) {
	HRESULT hr;
	float size[2] = { x, y };

	//Set size vector
	hr = _constTable->SetFloatArray(device, _scaleVectHndl, size, 2);

	if (FAILED(hr))
		return false;

	return true;
}

bool VertexShader::SetCenterVect(IDirect3DDevice9* device, float x, float y) {
	HRESULT hr;
	float center[2] = { x, y };

	//Set center vector
	hr = _constTable->SetFloatArray(device, _centerVectHndl, center, 2);

	if (FAILED(hr))
		return false;

	return true;
}

void VertexShader::Release() {
	//Release our shader
	if(_shader != nullptr)
		_shader->Release();
	//Release our constant table
	if(_constTable != nullptr)
		_constTable->Release();
}

VertexShader::~VertexShader() {
	Release();
}