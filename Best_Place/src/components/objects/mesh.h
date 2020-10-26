#pragma once

#include "../../math/vector.h"

#define ABS(x)		(x >= 0 ? x : -(x))	//Absolute value


namespace Collision {
	//Defines for collision
#define COLLISION_NO	0	//No collision
#define COLLISION_LB	1	//Left-bottom collision
#define COLLISION_LT	2	//Left-top collision
#define COLLISION_RB	3	//Right-bottom collision
#define COLLISION_RT	4	//Right-top collision
#define COLLISION_L		5	//Left collision
#define COLLISION_R		6	//Right collision
#define COLLISION_B		7	//Bottom collision
#define COLLISION_T		8	//Top collision

}

class Mesh {
protected:
	Vector _position;		//Mesh position(0,0)
	float _width, _height;	//Mesh size(0,0)
public:
	Mesh();	//Empty constructor
	Mesh(Vector position, float width, float height) :	//Constructor with positions
		_position(position), _width(width), _height(height) {}

	char IsCollided(Mesh* mesh, Vector padding = {0.0f, 0.0f});	//Check if this mesh collide with other mesh and return side
	bool DotColide(Vector pos);		//Check if a dot is inside mesh

	//Set functions
	void SetPosition(Vector position) { _position = position; }	//Change position

	//Get functions 
	float GetX() const { return _position.x; }
	float GetY() const { return _position.y; }

	float GetWidth() const { return _width; }
	float GetHeight() const { return _height; }
};