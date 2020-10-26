#include "vertex.h"

//Set FVF
const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

Vertex::Vertex() {
	//Initialize a vertex in position 0,0,0
	Vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(float x, float y, float z, float u, float v){
	//Initialize a vertex with position 
	_x = x;
	_y = y;
	_z = z;
	_u = u;
	_v = v;
}

void Vertex::SetPos(float x, float y, float z) {
	//Change position
	_x = x;
	_y = y;
	_z = z;
}

Vector3 Vertex::GetPos() {
	//Get the position
	return Vector3{ _x, _y, _z };
}