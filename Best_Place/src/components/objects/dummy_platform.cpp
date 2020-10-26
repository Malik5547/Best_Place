#include "dummy_platform.h"

DummyPlatform::DummyPlatform(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, char regCollision) :
	Object(x, y, width, height, texture, device, ObjType::DUMMY_PLATFORM, regCollision)
{
	
}

bool DummyPlatform::IsTriggered() {
	if (_lifeTime == -1.0f)
		return false;
	else
		return true;
}

void DummyPlatform::Trigger() {
	if(_lifeTime == -1.0f)
		_lifeTime = 0.0f; //Reset life time
}

void DummyPlatform::Update(float timeDelta) {
	if (_lifeTime >= 0.0f) {
		if (_lifeTime > DUMMYPL_LIFETIME) {
			//Platform isn't more alive
			_alive = false;
			_lifeTime = -1.0f;
		}
		else {
			_lifeTime += timeDelta;
		}
	}
}