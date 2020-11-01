
#pragma once

#include "../objects/movObject.h"
#include "../phisics/collision/collisionSys.h"
#include "upgrade_list.h"
#include "../../input/input.h"

#define PLAYER_EDGE_DIST	20.0f	//Distance from player to upper and bottom edge

	//Player constants
#define PLAYER_POS			{0.0f, 1.0f}
#define PLAYER_WIDTH		1.0f
#define PLAYER_HEIGHT		1.0f
#define PLAYER_SIZE			{PLAYER_WIDTH, PLAYER_HEIGHT}
#define PLAYER_LIFES		3
#define PLAYER_TEXTURE_SRC	"src/data/player.png"
#define PLAYER_WEIGHT		20.0f
#define PLAYER_SPEED		4.0f
#define PLAYER_JUMP_MAX		16.0f	
#define PLAYER_DEAC_TIME	0.5f		//Player deacceleration time
#define PLAYER_MOBILITY		2.0f		//The mobility of player in the air

#define ICE_TIMER_VAL		0.1f  //

	//Upgrades
#define JUMP_BOOTS_ACCELERATION		15.0f	

#define AIR_RESISTANCE		0.01f

namespace World {

	class PlayerClass : public MobileObject{
	public:
		PlayerClass();

		void Init(Vector pos, IDirect3DDevice9* device);

		void SetBoots(bool val) { _upgrades->jump_boots = val; }

		void Jump();
		void Die();			//Player dies

		virtual void Update(float timeDelta) override;	//Update the position

		virtual float GetMaxHeight() override { return max_height; };
		unsigned char GetLifes() { return lifes; }

		void Release();		//Release player data		
	private:
		float max_height = 0.0f;						//Maximum height that player got
		unsigned char lifes = PLAYER_LIFES;				//Player lifes
		Texture* player_texture = nullptr;					//Player texture

		bool _canjump = true;
		bool _jumped = false;
		float jump_time = 0.0f;
		
		PlayerSp::UpgradesStruct* _upgrades;						//Upgrade list
		
		void UpdatePos(float timeDelta);				//Update position
		void UpdatePosAlt(float timeDelta);				//Update position (alternative)
	};

	void PlayerInit(Vector pos, IDirect3DDevice9* device);	//Init player

	PlayerClass* Player();									//Get player ptr							

	void PlayerUpdate(float timeDelta);						//Update player
	void PlayerDraw();

	float PlayerGetWidth();									//Get player width
	float PlayerGetHeight();								//Get player height
	Vector PlayerGetPos();									//Get player position
	Vector PlayerGetAcceleration();							//Get player acceleration

	void PlayerRelease();									//Release player

}