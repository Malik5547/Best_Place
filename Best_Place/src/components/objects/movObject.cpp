#include "movObject.h"
#include "../phisics/collision/collisionSys.h"	//Collision system

MobileObject::MobileObject():
	Object(){}

MobileObject::MobileObject(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type, char collRegister)
{
	Init(x, y, width, height, texture, device, type, collRegister);
}

void MobileObject::Init(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type, char collRegister)
{
	Object::Init(x, y, width, height, texture, device, type, collRegister);

	//Register as a mobile mesh
	if (collRegister == MOBILE_COLL_REG)
		Collision::AddMobileObject(this);
}

void MobileObject::SetVelocity(Vector vel) {
	_velocity = vel;

}

void MobileObject::SetWeight(float weight) {
	//Reset velocity
	_acceleration.y += _weight;
	//Set new weight
	_weight = weight;
	//Apply new weight
	_acceleration.y -= weight;
}

void MobileObject::Interact(Object* object) {
}

void MobileObject::Die() {
}

void MobileObject::Move(Vector dir) {
	//Normalize direction vector
	Normalize(&dir);

	//Update move vector. It will bre used in Update()
	_move += dir * _speed;
}


void MobileObject::Update(float timeDelta) {
	//
	//Set new position(Use SetPos())
	///

	switch (_platformType) {
	case ICE_PLATFORM:
		//Object is sliding
		_velocity += _acceleration * timeDelta;
		if (ABS(_velocity.x) < _speed) {
			//Increase velocity
			_velocity.x += _move.x * timeDelta;
		}
		_velocity -= _velocity * OBJ_ICE_RESISTANCE;
		
		SetPosition(_position + _velocity * timeDelta);
		break;
	case JUMP_PLATFORM:
		//Object is pushed up

		_velocity += _acceleration * timeDelta;
		_velocity.x = _move.x;
		_velocity.y = JUMP_PL_ACCEL;
		
		SetPosition(_position + _velocity * timeDelta);

		break;
	case NOTHING:
		//Object is in air
		_velocity += _acceleration * timeDelta;
	//if (_move.x == 0.0f)
	//	_velocity.x -= _velocity.x * RESISTANCE;
	//else
			_velocity.x = _move.x;
		SetPosition(_position + _velocity * timeDelta);
		break;
	default:
		//Object is moving clear
		_velocity += _acceleration * timeDelta;
		_velocity.x = _move.x;
		SetPosition(_position + _velocity * timeDelta);
		break;
	}



	//Handle collision
	if (_collRegister == MOBILE_COLL_REG)
		if (!Collision::Update(this)) {
			_platformType = ObjType::NOTHING;
		}

	//_position += _velocity * timeDelta;

	//Reset move vector
	_move = { 0.0f, 0.0f };
}

float MobileObject::GetMaxHeight() { return _position.y; }

void MobileObject::Release() {
	//If the object is registered in collision system remove it
	if (_collRegister == MOBILE_COLL_REG)
		Collision::RemoveMobileObject(this);
}

MobileObject::~MobileObject() {
	Release();
}
