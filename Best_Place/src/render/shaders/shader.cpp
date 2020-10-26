#include "shader.h"

bool Shader::Compile(const char* dir, bool type) {
	HRESULT hr = 0;		//Save function's return

	//
	// Compile shader
	//

	ID3DXBuffer* errorBuffer = 0;

	if (type == SHADER_TYPE_VERTEX) {
		//Compile vertex shader
		hr = D3DXCompileShaderFromFile(
			dir,
			0,
			0,
			"Main", // entry point function name
			VERTEX_SHADER_VERSION,
			SHADER_FLAG,
			&_compShader,
			&errorBuffer,
			&_constTable);
	}
	else {
		//Compile pixel shader
		hr = D3DXCompileShaderFromFile(
			dir,
			0,
			0,
			"Main", // entry point function name
			PIXEL_SHADER_VERSION,
			SHADER_FLAG,
			&_compShader,
			&errorBuffer,
			&_constTable);
	}

	// output any error messages
	if (errorBuffer)
	{
		::MessageBox(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		errorBuffer->Release();
	}
	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXCompileShaderFromFile() - FAILED", 0, 0);
		return false;
	}

	return true;
}

void Shader::Release() {
	//Release const table
	if (_constTable != nullptr)
		_constTable->Release();
}

Shader::~Shader() {
	Release();
}