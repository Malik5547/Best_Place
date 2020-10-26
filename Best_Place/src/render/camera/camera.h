//
//File: camera.h
//Desc: Camera object for render
//

#pragma once
#include "../../components/objects/object.h"

#define CAM_DIST	20.0f

class Camera {
	Vector _position;			//Camera position	(0.0, 0.0)
	Vector _relativePos;	//Relative position from followed object
	float _dist;			//Camera distance for scene size changing	(1.0)

	Object* _followObj = nullptr;	//Object followed by camera
public:
	Camera(float x = 0.0f, float y = 0.0f, float dist = CAM_DIST);	//Constructor with delault fields

	
	void SetPos(float x, float y);	//Set new position to camera
	void SetDist(float dist);		//Set new distance to camera

	void Follow(Object* followObject) { _followObj = followObject; }	//Set a object for following
	void StopFollowing() { _followObj = nullptr; }				//Stop following

	float GetX() { return _position.x; }		//Get x position
	float GetY() { return _position.y; }		//Get x position
	float GetDist() { return _dist; }		//Get x position

	void Update();	//Update camera when follow an object

	~Camera() {} //Empty destructor
};