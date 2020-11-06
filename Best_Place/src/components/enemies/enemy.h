#pragma once

#include "../objects/movObject.h"

	//Enemy desc
#define ENEMY_DIR			bool	//Enemy direction type
#define ENEMY_DIR_LEFT		false	//Left direction value
#define ENEMY_DIR_RIGHT		true	//Right direction value

enum class EnemyType {
	Undefined, SimpleEnemy
};

class Enemy : public MobileObject {
public:
	inline ENEMY_DIR GetDir() {return _direction; }		//Get direction
	inline Object* GetPlatform() {return _platform; }	//Get platform

	inline void SetDir(ENEMY_DIR dir) {_direction = dir; }	//Set direction

	virtual void Interact(Object* object, CollisionSide side) override;

protected:

	Enemy(Vector pos, Vector size, Texture* texture, IDirect3DDevice9* device);


	inline virtual EnemyType GetType() {return EnemyType::Undefined; }

	virtual void Die();


	Object* _platform = nullptr;			//The platform under enemy
	ENEMY_DIR _direction = ENEMY_DIR_LEFT;	//Enemy direction
};
