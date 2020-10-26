#pragma once

#include "object.h"

#define DUMMYPL_LIFETIME	1

class DummyPlatform : public Object{
	float _lifeTime = -1;	//Life time of platform

public:
	DummyPlatform(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, char regCollision = STATIC_COLL_REG);	//Create a platform

	virtual bool IsTriggered() override;	//Is the object triggered
	virtual void Trigger() override;		//Activate platform timer
	
	virtual void Update(float timeDelta);	//Update platform timer
};