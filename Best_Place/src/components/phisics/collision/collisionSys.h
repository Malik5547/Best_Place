//
//File: collisionSys.h
//
//Desc: Static Collision system check all collision betwen objects and fix them
//

#pragma once

#include "../../objects/movObject.h"
#include <forward_list>

namespace Collision {

#define COLL_SYS		CollisionSystem
#define COLL_SYS_STATIC COLL_SYS._staticObjects
#define COLL_SYS_MOBILE COLL_SYS._mobileObjects

	class{
		std::forward_list<MobileObject*> _mobileObjects;	//List of mobile objects
		std::forward_list<Object*>		 _staticObjects;	//List of static objects

		friend void AddMobileObject(MobileObject* object);	
		friend void AddStaticObject(Object* object);

		friend bool Update(MobileObject* object);								

		friend void RemoveMobileObject(MobileObject* object);		
		friend void RemoveStaticObject(Object* object);			

	} CollisionSystem;

	void AddMobileObject(MobileObject* object);				//Add an mobile object to system
	void AddStaticObject(Object* object);					//Add an static object to system

	char Detect(MobileObject* object, Object* second);					//Detect colision and return side of collision
	void Margin(MobileObject* object, Object* other, const char side);	//Margin an object to another object

	bool Update(MobileObject* object);								//Handle all collision

	void RemoveMobileObject(MobileObject* object);		//Remove an mobile object from system
	void RemoveStaticObject(Object* object);			//Remove an static object from system

}