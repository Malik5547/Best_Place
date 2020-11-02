#include "player.h"

//RENDER TEST
#include "../../render/render.h"


namespace World {

	PlayerClass player;

	PlayerClass* Player() {
		return &player;
	}

	void PlayerInit(Vector pos, IDirect3DDevice9* device) {
		player.Init(pos, device);
	}

	void PlayerUpdate(float timeDelta) {
		player.Update(timeDelta);
	}

	void PlayerDraw() {
		player.Draw();
	}

	float PlayerGetWidth() {
		return player.GetWidth();
	}

	float PlayerGetHeight() {
		return player.GetHeight();
	}

	Vector PlayerGetPos() {
		return player.GetPosition();
	}

	Vector PlayerGetAcceleration() {
		return player.GetAcceleration();
	}

	void PlayerRelease() {
		player.Release();
	}

	PlayerClass::PlayerClass() :
		MobileObject() {	}

	void PlayerClass::Init(Vector pos, IDirect3DDevice9* device)
	{
		//Load texture
		player_texture = new Texture(PLAYER_TEXTURE_SRC, device);

		//Create object
		MobileObject::Init(pos.x, pos.y, PLAYER_WIDTH, PLAYER_HEIGHT, player_texture, device);
		//Set weight
		SetWeight(PLAYER_WEIGHT);
		
		//Set animations
		int animNumber = CreateAnimation(143, 150, 0, 143, 24, 30.0f);
		SetAnimation(animNumber);

		//Set upgrades
		PlayerSp::InitUpgradeList(device);
		_upgrades = PlayerSp::GetUpgradeList();
	}

	void PlayerClass::Jump() {
		if (_platformType != NOTHING) {
			//If the player is on the platform, then he jumps, and we set jumped flag
			SetVelocityY(PLAYER_JUMP_MAX);
			_jumped = true;
		}
		else if (_velocity.y < 0.0f)
			//The player is still pressing space, but he is already falling
			_jumped = false;
	}

	void PlayerClass::Interact(Object* object) {
		_platformType = object->GetType();

		if (_platformType == ObjType::DUMMY_PLATFORM) {
			if (!object->IsTriggered())
				object->Trigger();
		}
	}

	void PlayerClass::Die() {
		if (lifes > 0)
			lifes--;

		//Spawn player on the last height
		SetPosition({ 0.0f, max_height });
	}
	
	void PlayerClass::Update(float timeDelta) {
		static bool PhisicType = false;
		static float jump_accel = 0.0f;		//Jump deacceleration, when player release space
		
		//								
		//Jump update
		//
		if (_jumped) {
			if (!IS_PRESSED(Input::SPACE)) {
				//If player has released space, set deacceleration
				jump_accel = _velocity.y / PLAYER_DEAC_TIME;
				_jumped = false;
			}
		}

		//Update Y velocity
		SetVelocityY(_velocity.y -= jump_accel * timeDelta);
		
		//Reset deacceleration
		if (_platformType != NOTHING) {
			jump_accel = 0.0f;
		}


		if (::GetAsyncKeyState('T') & 0x8000f) {
			PhisicType = true;
		}
		if (::GetAsyncKeyState('Y') & 0x8000f) {
			PhisicType = false;
		}
		
		//
		//Update position
		//
		if (PhisicType)
			UpdatePos(timeDelta);
		else
			UpdatePosAlt(timeDelta);

		//Show velocity
		std::string vel = "Velocity {X}: ";
		std::string v = "Velocity {Y}: ";
		vel += std::to_string(_velocity.x);
		v += std::to_string(_velocity.y);
		GUI::TextDraw(vel);
		GUI::TextDraw(v);

		//Handle collision
		if (_collRegister == MOBILE_COLL_REG)
			if (!Collision::Update(this)) {
				_platformType = ObjType::NOTHING;
			}

		//Reset move vector
		_move = { 0.0f, 0.0f };

		//Update max height
		if (_position.y > max_height)
			max_height = _position.y;
		else if (_position.y < max_height - PLAYER_EDGE_DIST) {
			Die();
		}
	}

	void PlayerClass::UpdatePos(float timeDelta) {
		static float ice_timer = 0.0f;	//Player can't move some time after falling from ice platform

		//
		//Set new position(Use SetPos())
		///

		switch (_platformType) {
		case ICE_PLATFORM:
			//Object is sliding
			_velocity += _acceleration * timeDelta;
			if (ABS(_velocity.x) < _speed) {
				//Increase velocity
				_velocity.x += _move.x * timeDelta;
			}
			_velocity -= _velocity * OBJ_ICE_RESISTANCE;

			SetPosition(_position + _velocity * timeDelta);

			//Set timer for falling
			ice_timer = ICE_TIMER_VAL;
			break;
		case JUMP_PLATFORM:
			//Object is pushed up

			_velocity += _acceleration * timeDelta;
			_velocity.x = _move.x;
			_velocity.y = JUMP_PL_ACCEL;

			SetPosition(_position + _velocity * timeDelta);

			break;
		case NOTHING:
			//Object is in air
			_velocity += _acceleration * timeDelta;

			//Check if the object fall from ice platform
			if (ice_timer <= 0.0f)
				_velocity.x = _move.x;
			else
				ice_timer -= timeDelta;

			SetPosition(_position + _velocity * timeDelta);
			break;
		default:
			//Object is moving clear
			_velocity += _acceleration * timeDelta;
			_velocity.x = _move.x;
			SetPosition(_position + _velocity * timeDelta);
			break;
		}
	}

	void PlayerClass::UpdatePosAlt(float timeDelta) {

		switch (_platformType) {
		case ICE_PLATFORM:
			//Object is sliding
			_velocity += _acceleration * timeDelta;

			if (ABS(_velocity.x) < _speed) {
				//Increase velocity
				_velocity.x += _move.x * timeDelta;
			}
			_velocity -= _velocity * OBJ_ICE_RESISTANCE;

			SetPosition(_position + _velocity * timeDelta);
			break;
		case JUMP_PLATFORM:
			//Object is pushed up

			_velocity += _acceleration * timeDelta;
			_velocity.x = _move.x;
			_velocity.y = JUMP_PL_ACCEL;

			SetPosition(_position + _velocity * timeDelta);

			break;
		case NOTHING:
			//Object is in air
			_velocity += _acceleration * timeDelta;

			//Set X speed
			if (ABS(_velocity.x) < _speed)
				_velocity.x += _move.x * timeDelta * PLAYER_MOBILITY;

			_velocity.x -= AIR_RESISTANCE * _velocity.x;

			SetPosition(_position + _velocity * timeDelta);
			break;
		default:
			//Object is moving clear
			_velocity += _acceleration * timeDelta;
			_velocity.x = _move.x;
			SetPosition(_position + _velocity * timeDelta);
			break;
		}
	}

	void PlayerClass::Release() {
		MobileObject::Release();
		delete player_texture;
	}
}