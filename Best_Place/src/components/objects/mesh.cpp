#include "mesh.h"

Mesh::Mesh() {
	Mesh({0.0f, 0.0f}, 0.0f, 0.0f);
}

char Mesh::IsCollided(Mesh* mesh, Vector padding) {
	char xCollision = COLLISION_NO;	//Are objects collided on X
	char yCollision = COLLISION_NO;	//Are objects collided on Y

	float dist;	//Distance

	dist = ABS(mesh->_position.x - _position.x);	//X distance

	if (_position.x < mesh->_position.x) {
		//Second object is on right
		if (dist < _width + padding.x) {
			//Meshes are collided on x
			xCollision = COLLISION_R;
		}
	}else{
		//Second object is on left
		if (dist < mesh->_width + padding.x) {
			//Meshes are collided on x
			xCollision = COLLISION_L;
		}
	}

	if (xCollision) {
		//If objects are collided on X, check collision on Y
		dist = ABS(_position.y - mesh->_position.y);	//Distantion on Y

		if (_position.y > mesh->_position.y) {
			//Second object is under
			if (dist < mesh->_height + padding.y) {
				//Meshes are collided on Y
				yCollision = COLLISION_B;
			}
		}
		else {
			//Second object is above
			if (dist < _height + padding.y) {
				//Meshes are collided on Y
				yCollision = COLLISION_T;
			}
		}
	}
	
	if (xCollision == COLLISION_L) {
		if (yCollision == COLLISION_B) 
			return COLLISION_LB;		
		else if (yCollision == COLLISION_T)
			return COLLISION_LT;
	}
	else if (xCollision == COLLISION_R) {
		if (yCollision == COLLISION_B)
			return COLLISION_RB;
		else if (yCollision == COLLISION_T)
			return COLLISION_RT;
	}

	return COLLISION_NO;
}

bool Mesh::DotColide(Vector pos) {
	if (pos.x > _position.x && pos.x < _position.x + _width) {
		//If Y positoin is colided check Y
		if (pos.y > _position.y && pos.y < _position.y + _height)
			return true;
	}

	return false;
}