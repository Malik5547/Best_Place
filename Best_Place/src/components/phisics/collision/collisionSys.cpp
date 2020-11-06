#include "collisionSys.h"

namespace Collision {

	void AddMobileObject(MobileObject* object) {
		COLL_SYS_MOBILE.push_front(object); 
	}

	void AddStaticObject(Object* object) { 
		COLL_SYS_STATIC.push_front(object); 
	}

	char Detect(MobileObject* object, Object* second) {

		if (char side = object->IsCollided(second)) {
			//If the objects collide

			Vector firstCorner;	//Corner of fierst object
			Vector secondCorner; //Corner of second object
			Vector dist;			//Distance from corners

			switch(side){
			case COLLISION_RB:
					//Second object is right-bottom
					firstCorner = object->GetPosition();	//Right-bottom dot
					firstCorner.x += object->GetWidth();

					secondCorner = second->GetPosition();	//Left-top dot
					secondCorner.y += second->GetHeight();

					dist = firstCorner - secondCorner;	//Distance between corners

					if ((ABS(dist.x)) < (ABS(dist.y)))
						return COLLISION_R;
					else
						return COLLISION_B;

					break;
			case COLLISION_RT:
					//Second object is right-top
					firstCorner = object->GetPosition();		//Right-top dot
					firstCorner.x += object->GetWidth();

					firstCorner.y += object->GetHeight();
					secondCorner = second->GetPosition();	//Left-bottom dot

					dist = (firstCorner - secondCorner);	//Distance between corners

					Vector vel = object->GetVelocity();

					if ((ABS(dist.x)) < (ABS(dist.y)))
						return COLLISION_R;
					else
						return COLLISION_T;

					break;
			case COLLISION_LT:
				//Collision is on left-top	
					firstCorner = object->GetPosition();		//Left-top dot
					firstCorner.y += object->GetHeight();	

					secondCorner = second->GetPosition();	//Right-bottom dot
					secondCorner.x += second->GetWidth();

					dist = firstCorner - secondCorner;	//Distance between corners

					if ((ABS(dist.x)) < (ABS(dist.y)))
						return COLLISION_L;
					else
						return COLLISION_T;

					break;
			case COLLISION_LB:
					//Second object is left-bottom
					firstCorner = object->GetPosition();		//Left-bottom dot

					secondCorner = second->GetPosition();	//Right-top dot
					secondCorner.x += second->GetWidth();
					secondCorner.y += second->GetHeight();

					dist = firstCorner - secondCorner;	//Distance between corners

					if ((ABS(dist.x)) < (ABS(dist.y)))
						return COLLISION_L;
					else
						return COLLISION_B;
				
					break;
			}
		}

		return COLLISION_NO;
	}

	void Margin(MobileObject* object, Object* other, const char side) {
		Vector newPostition = object->GetPosition();	//New positon

		switch (side) {
		case COLLISION_R:
			//Set position to left
			newPostition.x = other->GetPosition().x - object->GetWidth();
			//Reset X velocity
			object->SetVelocityX(0.0f);
			break;
		case COLLISION_L:
			//Set position to right
			newPostition.x = other->GetPosition().x + other->GetWidth();
			//Reset X velocity
			object->SetVelocityX(0.0f);
			break;
		case COLLISION_B:
			//Set position to top
			newPostition.y = other->GetPosition().y + other->GetHeight();
			//Reset Y velocity
			object->SetVelocityY(0.0f);
			//Object is on the platform
			//object->Interact(other);
			break;
		case COLLISION_T:
			//Set position to bottom
			newPostition.y = other->GetPosition().y - object->GetHeight();
			//Reset Y velocity
			object->SetVelocityY(0.0f);
			break;
		}

		//Set new position
		object->SetPosition(newPostition);
	}

	bool Update(MobileObject* object) {
		bool ColDet = false;
		
		//
		//Static collision
		//
		for (auto other = COLL_SYS_STATIC.begin(); other != COLL_SYS_STATIC.end(); other++) {
			//For each static object, check collision

			if (char side = Detect(object, *other)) {
				//Objects are collided, we have to margin first object
				Margin(object, *other, side);
				object->Interact(*other, side);
				ColDet = true;
			}
		}

		//
		//Mobile collision
		//
		for (auto other = COLL_SYS_MOBILE.begin(); other != COLL_SYS_MOBILE.end(); other++) {
			//For each mobile object, check collision

			if (object != *other) {
				if (char side = Detect(object, *other)) {
					//Objects are collided, we do not margin them, just interact
				//	Margin(object, *other, side);
					object->Interact(*other, side);
					ColDet = true;
				}
			}
		}

		return ColDet;
	}

	void RemoveMobileObject(MobileObject* object) {
		//Remove mobile object
		COLL_SYS_MOBILE.remove(object);
	}

	void RemoveStaticObject(Object* object) {
		//Remove static object
		COLL_SYS_STATIC.remove(object);
	}

}