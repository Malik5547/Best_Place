#pragma once

#include "enemy.h"

	//Enemy params
#define ENEMY_SIMPLE_TEXTURE	"src/data/enemy.png"
#define ENEMY_SIMPLE_WIDTH	1.0f
#define ENEMY_SIMPLE_HEIGHT	1.0f
#define ENEMY_SIMPLE_SIZE	{ENEMY_SIMPLE_WIDTH, ENEMY_SIMPLE_HEIGHT}

class SimpleEnemy : protected Enemy {
public:
	SimpleEnemy(Object* platform, IDirect3DDevice9* device);

	virtual void Interact(Object* object, CollisionSide side) override;

	virtual void Update(float timeDelta) override;

	virtual void Die() override;

	~SimpleEnemy() {}

};

void SimpleEnemyInit(IDirect3DDevice9* device);		//Init simple enemy(load texture)
