#pragma once

#include <d3dx9.h>

#define SetConsoleTitle SetConsoleTitleA

#define SHADER_FLAG D3DXSHADER_DEBUG	//Flag for shader compiling
#define SHADER_TYPE_VERTEX	0			//Compile vertex shader
#define SHADER_TYPE_PIXEL	1			//Compile pixel shader

#define VERTEX_SHADER_VERSION "vs_2_0"			//Version for vertex shader compiling
#define PIXEL_SHADER_VERSION  "ps_2_0"			//Version for pixel shader compiling

class Shader {
protected:
	ID3DXBuffer* _compShader = nullptr;		//Compiled shader
	ID3DXConstantTable* _constTable = nullptr;	
public:
	Shader(){}

	bool Compile(const char* dir, bool type);

	ID3DXConstantTable* GetTable() { return _constTable; }

	void Release();

	~Shader();
};