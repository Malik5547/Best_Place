#include "simpleEnemy.h"
#include "AI/simpleAI.h"

Texture* SimpleEnemyTexture = nullptr;

SimpleEnemy::SimpleEnemy(Object* platform, IDirect3DDevice9* device) :
	Enemy({ platform->GetPos().x, platform->GetPos().y + platform->GetHeight() }, ENEMY_SIMPLE_SIZE, SimpleEnemyTexture, device)
{
	_platform = platform;
}

void SimpleEnemy::Interact(MobileObject* obj) {
	if (obj->GetType() == ObjType::PLAYER) {
		if (obj->GetPosition().y > _position.y + _height)
			Die();
		else
			obj->Die();
	}
}

void SimpleEnemy::Update(float timeDelta) {
	SimpleAI::Handle(this);

	if (_direction == ENEMY_DIR_LEFT)
		Move({ -1.0f, 0.0f });
	else
		Move({ 1.0f, 0.0f });

	MobileObject::Update(timeDelta);
}

void SimpleEnemy::Die() {
	_alive = false;
}

void SimpleEnemyInit(IDirect3DDevice9* device) {
	SimpleEnemyTexture = new Texture(ENEMY_SIMPLE_TEXTURE, device);
}