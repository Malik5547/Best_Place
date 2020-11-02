//
//File: movObject.h
//Desc: Contain class MovingObject that describes mobile objects
//

#pragma once

#include "object.h"

#define MAX_VELOCITY	10.0f

//Platform constants
#define RESISTANCE	0.1f
#define PLATFORM_RESISTANCE	0.0002f
#define OBJ_ICE_RESISTANCE	0.002f

#define JUMP_PL_ACCEL		30.0f

class MobileObject : public Object {
protected:
	Vector _acceleration = { 0.0f, 0.0f };	//Object acceleration
	Vector _velocity = { 0.0f, 0.0f };		//Object velocity (vector)
	Vector _move = { 0.0f, 0.0f };			//Object mooving 
	float _speed = 4.0f;					//Object speed (scalar)
	float _weight = 0.0f;					//Object weight

	ObjType _platformType = ObjType::NOTHING;						//Type of platform above object

public:
	MobileObject();
	MobileObject(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type = ObjType::PLATFORM, char collRegister = MOBILE_COLL_REG);	//Constructor with arguments
	void Init(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type = ObjType::PLATFORM, char collRegister = MOBILE_COLL_REG);

	//Set functions
	void SetVelocity(Vector vel);	//Set velocity
	void SetVelocityY(float vel) { _velocity.y = vel; }	//Set Y velocity
	void SetVelocityX(float vel) { _velocity.x = vel; }	//Set Y velocity
	void SetAcceleration(Vector acc) { _acceleration = acc; };	//Set acceleration
	void SetSpeed(float speed) { _speed = speed; }	//Set speed
	void SetWeight(float weight);			//Set weight

	//Get functions
	Vector GetAcceleration() { return _acceleration; }
	Vector GetVelocity() { return _velocity; }
	float GetVelocityY() { return _velocity.y; }
	virtual float GetMaxHeight();	//Max height for player class

	virtual void Interact(Object* object);		//Interaction betwen objects when they collide
	virtual void Die();							//When player or enemy dies

	void Move(Vector direction);	//Move the object in direction with setted speed

	virtual void Update(float timeDelta) override;	//Update the position

	void Release();			//Release resources

	~MobileObject();		//Destructor
};

