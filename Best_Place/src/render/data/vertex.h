#pragma once

//
//File: vertex.h
//Desc: Here are described methods and fields of Vertex class, wich is a dot in 3D space.
//

#include <d3d9.h>
#include ".././../math/vector.h"
#include "..\..\math\vector3.h"

class Vertex {
	float _x, _y, _z;	//Vertex coordoate
	float _u, _v;		//Texture coordinates

public:
	static const DWORD FVF;	//Vertex format
	
	Vertex();	//Initialize a vertex in position 0,0,0
	Vertex(float x, float y, float z, float u, float v);	//Initialize a vertex with position

	void SetPos(float x, float y, float z = 0.0f);	//Change position
	void SetUV(float u, float v) { _u = u; _v = v; }				//Change texture coordinates

	Vector3 GetPos();	//Get position
	Vector GetUV() { return Vector{ _u, _v }; }	//Get UV

	~Vertex() {} //It does nothing. Yet
};
