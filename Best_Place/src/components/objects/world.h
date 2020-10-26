//
//File: world.h
//
//Desc: All objects are saved in world class
//

#pragma once

#include "../player/player.h"
#include "../player/upgrade_list.h"
#include "dummy_platform.h"
#include "../background/background.h"

#include <list>

	//Platform textures path
#define PLTFM_DEF_TEX	"src/data/platform_default.png"
#define PLTFM_ICE_TEX	"src/data/platform_sliding.png"
#define PLTFM_DUM_TEX	"src/data/platform_dummy.png"
#define PLTFM_JMP_TEX	"src/data/platform_jump.png"


#define PLATFORM_WIDTH	4.0f
#define PLATFORM_HEIGHT	1.0f
#define PLATFORM_SIZE	{PLATFORM_WIDTH, PLATFORM_HEIGHT}

	//Platform generation
#define MAXY			1000.0f
#define MAXY_DENSITY	0	
#define MINY_DENSITY	4
#define MAXX			30.0f
#define MINX			-30.0f
#define PLATFORM_DIST_X	5.0f	//Minimal distance between platforms
#define PLATFORM_DIST_Y	2.0f
#define PLATFORM_X_RANGE	10		//Distance from 0 X coord where platforms are spawned 	
	//Type probabilities
#define PL_DEF_PROB		0.6f	//Probability that platform will be default
#define PL_ICE_PROB		0.2f	//Probability that platform will be ice
#define PL_DUMMY_PROB	0.1f	//Probability that platform will be dummy
#define PL_JUMP_PROB	0.1f	//Probability that platform will be jump

	//Background
#define BACKGROUND_TEXTURE "src/data/back.png"		//Background texture

namespace World {

	enum WorldState {
		WORLD_STATE, SHOP_STATE
	};

	class {
		friend void InitWorld(IDirect3DDevice9* device);
		friend void SpawnObject(Vector pos, Vector size, ObjType type);
		friend void SpawnPlatform(Vector pos);
		
		friend Vector NewPlatformPos(Object* platform);
		friend void CreateNearPlatform(Object* platform, char side);
		friend void AdjectivePlatforms(Vector newPos);
		friend void GeneratePlatforms();
		friend void HandleCollisions(Object** platforms, int count);

		friend void Update(float timeDelta);
		friend void UpdateWorld(float timeDelta);				//Update function of the world

		friend void RemoveLowerPlatforms();
		friend void DrawWorld();
		
		friend void ClearWorld();

	private:

		IDirect3DDevice9* _device;						//Device ptr
		std::list<Object*> w_objects;			//World objects
		Background* w_back;						//World background
		WorldState w_state = WORLD_STATE;		//State of the world(is player in the shop)
	} WorldClass;


	void InitWorld(IDirect3DDevice9* device);	//Generate world
	void SpawnObject(Vector pos, Vector size, ObjType type = ObjType::PLATFORM);	//Spawn an object

	Vector NewPlatformPos(Object* platform);		//Get new platform position
	ObjType PlatformType(float height);					//Calculate the platform type
	void AdjectivePlatforms(Vector newPos);		//Generate adjective platforms before last platform
	void CreateNearPlatform(Object* platform, char side);		//Spawn platform near to other platform 
	void GeneratePlatforms();		//Random spawn new platforms
	void HandleCollisions(Object** platforms, int count);			//Handle collisions between platforms

	void Update(float timeDelta);		//Update world
	static void UpdateWorld(float timeDelta);				//Update function of the world

	void RemoveLowerPlatforms();		//Remove platforms that are far from player
	void DrawWorld();	//Draw world

	void ClearWorld();							//Clear world
}