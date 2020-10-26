#pragma once

#include "shader.h"

//Defines for vertex processing type. !Should be changed in vertexShader.txt
#define VPROC_DEF	0
#define VPROC_RAW	1
#define VPROC_WND	2

//Vertex Shader class from shader class
class VertexShader: public Shader{
	IDirect3DVertexShader9* _shader = nullptr;	//Our vertex shader

	D3DXHANDLE _viewVecHndl;				//View vector handle
	D3DXHANDLE _viewDistHndl;				//View distance handle
	D3DXHANDLE _vertexProcHndl;					//Type of vertex processing
	D3DXHANDLE _scaleVectHndl;				//Scale vector handle
	D3DXHANDLE _centerVectHndl;				//Center vector handle(for scaling)
public:
	VertexShader(){}

	bool Create(IDirect3DDevice9* device);	//Create vertex shader

	bool SetWindowSize(IDirect3DDevice9* device, int width, int height);		//Set window size for raw drawing
	bool SetVertexProc(IDirect3DDevice9* device, unsigned int val);													//Set type of vertex processing
	bool SetViewPos(IDirect3DDevice9* device, float x, float y);		//Set view position
	bool SetViewDist(IDirect3DDevice9* device, float dist);				//Set view distantion
	bool SetScaleVect(IDirect3DDevice9* device, float x, float y);									//Set scale vector
	bool SetCenterVect(IDirect3DDevice9* device, float x, float y);									//Set center vector

	IDirect3DVertexShader9* GetShader() { return _shader; }		//Get our vertex shader

	void Release();
	~VertexShader();
};