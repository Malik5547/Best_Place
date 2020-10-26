#include "object.h"
#include "../phisics/collision/collisionSys.h"	//Colision system


Object::Object(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type, char regCollision) {
	Init(x, y, width, height, texture, device, type, regCollision);
}

void Object::Init(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type, char regCollision) {
	//Set position
	_position = { x, y };

	//Set the width and height
	_width = width;
	_height = height;

	//Set type
	_type = type;

	//Set the mesh
	_mesh = new Mesh({ x, y }, width, height);

	//Set the sprite
	_sprite = new Sprite(device, x, y, x + width, y + height, texture);

	//Register object in collisiont system
	_collRegister = regCollision;
	if (regCollision == STATIC_COLL_REG) {
		//Register as a static collision
		Collision::AddStaticObject(this);
	}
}

void Object::SetPosition(Vector position) {
	_position = position;
	_mesh->SetPosition(position);

	//If there is a sprite, change it's position
	if (_sprite != nullptr)
		_sprite->SetPos(position.x, position.y, position.x + _width, position.y + _height);
}

int Object::CreateAnimation(int height, int width, int x, int y, int count, float speed) {
	//Check sprite and create animetion
	if (_sprite != nullptr)
		return _sprite->CreateAnimation(height, width, x, y, count, speed);

	return NO_SPRITE;
}

char Object::SetAnimation(int order) {
	//Check sprite and set Animation
	if (_sprite != nullptr)
		return _sprite->SetAnimation(order);

	return NO_SPRITE;
}

bool Object::IsTriggered() { return false; }
void Object::Trigger() {}

void Object::Draw() {
	//If there is a sprite, draw it
	if (_sprite != nullptr)
	_sprite->Draw();
}

char Object::IsCollided(Object* other, Vector padding) {
	//Check if the object collide with other object
	return _mesh->IsCollided(other->_mesh, padding);
}

float Object::GetMaxHeight() { return _position.y; }

void Object::Release() {
	//Release sprite
	if (_sprite != nullptr) {
		_sprite->Release();
	}

	//Remove sprite from collision system
	if (_collRegister == STATIC_COLL_REG)
		Collision::RemoveStaticObject(this);
}

Object::~Object() {
	Release();

	//Delete sprite
	delete _sprite;
	//Delete mesh
	delete _mesh;
}
