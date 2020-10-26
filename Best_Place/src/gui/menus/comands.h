//
//File: comands.h
//
//Desc: Here are described all comands used in game (I think so)
//


#pragma once
#include "../../components/objects/world.h"

namespace Comands {

#define OBJECT_SPAWN_SIZE {2.0f, 1.0f}

	//Comands texture
#define SPAWNPL_TEX		"src/data/comand1.png"
#define SPAWNIPL_TEX	"src/data/comand4.png"
#define SPAWNDPL_TEX	"src/data/comand2.png"
#define SPAWNJPL_TEX	"src/data/comand3.png"

	void SpawnPlatform(Vector pos);
	void SpawnIcePlatform(Vector pos);
	void SpawnDummyPlatform(Vector pos);
	void SpawnJumpPlatform(Vector pos);

}