#include "enemy.h"

Enemy::Enemy(Vector pos, Vector size, Texture* texture, IDirect3DDevice9* device) :
	MobileObject(pos.x, pos.y, size.x, size.y, texture, device, ObjType::ENEMY)
{
}

void Enemy::Interact(Object* object, CollisionSide side){}

void Enemy::Die() {}