#include "comands.h"

namespace Comands {

	void SpawnPlatform (Vector pos) {
		World::SpawnObject(pos, OBJECT_SPAWN_SIZE);
	}

	void SpawnIcePlatform(Vector pos) {
		World::SpawnObject(pos, OBJECT_SPAWN_SIZE, ICE_PLATFORM);
	}

	void SpawnDummyPlatform(Vector pos) {
		World::SpawnObject(pos, OBJECT_SPAWN_SIZE, ObjType::DUMMY_PLATFORM);
	}

	void SpawnJumpPlatform(Vector pos) {
		World::SpawnObject(pos, OBJECT_SPAWN_SIZE, ObjType::JUMP_PLATFORM);
	}

}