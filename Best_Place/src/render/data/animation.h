//
//File: animation.h
//
//Desc: Class animation contains all animation data 
//


#pragma once
#include "../../math/vector.h"

#define ANIMATION_TIME	100000

class Animation {
	int _width, _height;	//Width and height of all sprites
	int _x, _y;			//First sprite position
	int _count;			//Number of sprites
	float _speed;		//Speed of animation
	float _time;			//Animation time

	static float _currentTime;	//Static time handle for animations
public:
	Animation(int height, int width, int x, int y, int count, float speed);	//Create an animation

	void Set() { _time = 0; }	//Set curent animation

	void const GetSpriteUV(int texWidth, int texHeight, Vector* uv1, Vector* uv2);		//Get upadated uv position

	static void Update(float timeDelta);	//Update time handle

	~Animation() {}	//Empty destructor
};

