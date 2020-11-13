//
//File: object.h
//Desc: Define class object. Objects are a basic part of game.
//

#pragma once

#include "../../math/vector.h"
#include "../../render/data/sprite.h"
#include "mesh.h"


#define NO_COLL_REG		0	//Do not register collision
#define STATIC_COLL_REG 1	//Register static collision
#define MOBILE_COLL_REG 2	//Register mobile collision

#define NO_SPRITE		-1	//No sprite error


//Type of object
#define TYPE_COUNT	4	//Number of platform types
enum ObjType {
	PLATFORM = 0, ICE_PLATFORM, DUMMY_PLATFORM, JUMP_PLATFORM, NOTHING, PLAYER, ENEMY
};


class Object {
	ObjType _type;					//Object type
	Mesh* _mesh;				//Object mesh. Object must have mesh

protected:
	Sprite* _sprite = nullptr;	//Object texture(sprite). Null by default
	Vector	_position;				//Object position
	float _width, _height;			//Object width and height
	char _collRegister;			//Is object registered in colision system
	bool _alive = true;			//Is object alive

public:
	Object() {}
	Object(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type = PLATFORM, char regCollision = STATIC_COLL_REG);	//Construct a object with mesh
	void Init(float x, float y, float width, float height, Texture* texture, IDirect3DDevice9* device, ObjType type = PLATFORM, char regCollision = STATIC_COLL_REG);

	//Animations
	int CreateAnimation(int height, int width, int x, int y, int count, float speed);	//Create animation
	char SetAnimation(int order);						//Set animation

	//Set functions
	void SetPosition(Vector position);	//Change position

	//Get fucntions
	inline Vector GetPos() {return _position; }		//Get position
	Mesh* GetMesh() { return _mesh; }
	Vector GetPosition() { return _position; }	//Get position
	float GetWidth() { return _width; }		//Get width
	float GetHeight() { return _height; }	//Get height
	inline Vector GetSize() {return Vector{ _width, _height }; }	//Get size
	ObjType GetType() { return _type; }		//Get type
	bool IsAlive() { return _alive; }		//Is object alive
	virtual float GetMaxHeight();	//Max height for player class

	virtual bool IsTriggered();	//Is the object triggered
	virtual void Trigger();		//Use this function to triger platform from player

	virtual void Update(float timeDelta) {}		//Update
	void Draw();								//Draw the object

	char IsCollided(Object* second, Vector padding = {0.0f, 0.0f});	//Check if the object collide with other object

	void Release();	//Release all values

	~Object();	//Destruct object
};

