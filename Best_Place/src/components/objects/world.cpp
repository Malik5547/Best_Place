#include "world.h"

namespace World {

	//Platform textures
	Texture* pltfm_default_texture;
	Texture* pltfm_sliding_texture;
	Texture* pltfm_dummy_texture;
	Texture* pltfm_jump_texture;
	
	//Platform type probabilities
	struct {
		float default_prob = PL_DEF_PROB;
		float ice_prob = PL_ICE_PROB;
		float dummy_prob = PL_DUMMY_PROB;
		float jump_prob = PL_JUMP_PROB;
		float total;
	} type_probs;

	float clamp(float x, float lowerlimit, float upperlimit)
	{
		if (x < lowerlimit)
			x = lowerlimit;
		if (x > upperlimit)
			x = upperlimit;
		return x;
	}

	float smoothstep(float edge0, float edge1, float x)
	{
		// Scale, bias and saturate x to 0..1 range
	    //x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0); 
		// Evaluate polynomial
		return x * x * (edge1 - edge0 * x);
	}

	void InitWorld(IDirect3DDevice9* device) {
		WorldClass._device = device;

		//Load platform textures
		pltfm_default_texture = new Texture(PLTFM_DEF_TEX, device);
		pltfm_sliding_texture = new Texture(PLTFM_ICE_TEX, device);
		pltfm_dummy_texture = new Texture(PLTFM_DUM_TEX, device);
		pltfm_jump_texture = new Texture(PLTFM_JMP_TEX, device);

		//Spawn basic objects

		Object* platform = SpawnObject({ -5.0f, -5.0f }, { 10.0f, 2.0f });
		SpawnObject({ -4.0f, 1.0f }, { 3.0f, 1.0f }, ObjType::ICE_PLATFORM);
		SpawnObject({ 2.0f, 3.0f }, { 4.0f, 1.0f }, ObjType::DUMMY_PLATFORM);
		SpawnObject({ 4.0f, 5.0f }, { 5.0f, 1.0f }, ObjType::JUMP_PLATFORM);

		//Test enemy
		SimpleEnemyInit(WorldClass._device);
		SpawnEnemy(platform);

		//Init player
		Player()->Init(PLAYER_POS, device);

		//Init background
		WorldClass.w_back = new Background(BACKGROUND_TEXTURE, device);
		WorldClass.w_back->SetFollow(Player());
	}

	Object* SpawnObject(Vector pos, Vector size, ObjType type) {
		Object* obj;

		switch (type) {
		case ObjType::PLATFORM:
			obj = new Object(pos.x, pos.y, size.x, size.y, pltfm_default_texture, WorldClass._device, type);
			break;
		case ObjType::ICE_PLATFORM:
			obj = new Object(pos.x, pos.y, size.x, size.y, pltfm_sliding_texture, WorldClass._device, type);
			break;
		case ObjType::DUMMY_PLATFORM:
			obj = new DummyPlatform(pos.x, pos.y, size.x, size.y, pltfm_dummy_texture, WorldClass._device);
			break;
		case ObjType::JUMP_PLATFORM:
			obj = new Object(pos.x, pos.y, size.x, size.y, pltfm_jump_texture, WorldClass._device, type);
			break;
		}

		//Save object in world
		WorldClass.w_objects.push_front(obj);

		return obj;
	}

	Object* SpawnPlatform(Vector pos) {
		ObjType type = PlatformType(pos.y);
		//Spawn platform
		Object* platform = SpawnObject(pos, PLATFORM_SIZE, type);
		
		if (type != JUMP_PLATFORM && type != DUMMY_PLATFORM) {
			//If the platform is not jump platform, it may spawn an enemy
			//Probability of enemy spawning. Depends by height of platform and max height.
			float enemyProb = (1 - smoothstep(0, 1, (float)((float)(MAXY - pos.y) / (float)MAXY))) / 2;

			if ((float)rand() / RAND_MAX < enemyProb) {
				//If the rand fit the probability, then spawn enemy
				SpawnEnemy(platform);
			}
		}

		return platform;
	}

	void SpawnEnemy(Object* platform) {
		SimpleEnemy* enemy = new SimpleEnemy(platform, WorldClass._device);

		WorldClass.w_movObjects.push_front((MobileObject*)enemy);
	}

	Vector NewPlatformPos(Object* platform) {
		//Object* platform = *WorldClass.w_objects.begin();

		float jumpTime;	//Time that object can be in air
		Vector maxpos;

		switch (platform->GetType()) {
		case JUMP_PLATFORM:
			jumpTime = JUMP_PL_ACCEL / ABS(PlayerGetAcceleration().y);
			maxpos.y = (JUMP_PL_ACCEL * JUMP_PL_ACCEL) / ABS(2 * PlayerGetAcceleration().y) - PLATFORM_HEIGHT;
			maxpos.x = PLAYER_SPEED * jumpTime;
			break;
		default:
			jumpTime = PLAYER_JUMP_MAX / ABS(PlayerGetAcceleration().y);
			maxpos.y = (PLAYER_JUMP_MAX * PLAYER_JUMP_MAX) / ABS(2 * PlayerGetAcceleration().y) - PLATFORM_HEIGHT;
			maxpos.x = PLAYER_SPEED * jumpTime;
			break;
		}

		//Position for new platform
		Vector p_size = { PlayerGetWidth(), PlayerGetHeight() };
		Vector pos = platform->GetPosition();
		char x_side = (rand() < static_cast <float> (RAND_MAX / 2)) ? 1 : -1;
		pos.x += x_side * (p_size.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxpos.x - p_size.x))));
		pos.y = p_size.y + PLATFORM_DIST_Y + platform->GetPosition().y + platform->GetHeight() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxpos.y - p_size.y - PLATFORM_DIST_Y)));

		if (ABS(pos.x) > PLATFORM_X_RANGE)
			pos.x -= pos.x > 0.0f ? PLATFORM_X_RANGE : -PLATFORM_X_RANGE;

		return pos;
	}
	
	ObjType PlatformType(float height) {
		//Return type using probabilities and the height of platform

		type_probs.default_prob = PL_DEF_PROB * (float)sqrt(sqrt(height));
		type_probs.ice_prob = PL_ICE_PROB * (float)sqrt(sqrt(height));
		type_probs.dummy_prob = PL_DUMMY_PROB * (float)sqrt(sqrt(height));
		type_probs.jump_prob = PL_JUMP_PROB * (float)sqrt(sqrt(height));
		type_probs.total = type_probs.default_prob + type_probs.ice_prob + type_probs.dummy_prob + type_probs.jump_prob;

		float val = static_cast<float>(rand()) / RAND_MAX * type_probs.total;

		if (val < type_probs.default_prob)
			return PLATFORM;
		else if (val < type_probs.default_prob + type_probs.ice_prob)
			return ICE_PLATFORM;
		else if (val < type_probs.default_prob + type_probs.ice_prob + type_probs.dummy_prob)
			return DUMMY_PLATFORM;
		else
			return JUMP_PLATFORM;
	}

	void GeneratePlatforms() {
		Vector platformPos = NewPlatformPos(*WorldClass.w_objects.begin());

		//Generate adjective platforms
		AdjectivePlatforms(platformPos);

		//Generate last platform
		SpawnPlatform(platformPos);
	}

	void AdjectivePlatforms(Vector newPos) {
		Object* lastPlatform = *WorldClass.w_objects.begin();

		//Number of platform to generate
		float number = (smoothstep(MAXY_DENSITY, MINY_DENSITY, (float)((float)(MAXY - lastPlatform->GetPosition().y) / (float)MAXY)) + 1);
		
		//Save new platforms , for colision detection
		Object** platforms = new Object*[(unsigned int)number + 1];
		platforms[0] = lastPlatform;

		for (int n = 1; n < static_cast<int>(number); n++) {
			//Calculate new platform position
			float x = MINX +  static_cast<float> (rand() / static_cast<float> (RAND_MAX / (MAXX - MINX)));
			float y = lastPlatform->GetPosition().y + static_cast<float>(rand() / static_cast<float>(RAND_MAX / (newPos.y - lastPlatform->GetPosition().y)));

			SpawnPlatform({ x,y });
			platforms[n] = *WorldClass.w_objects.begin();
			platforms[0]->IsCollided(platforms[n]);

			HandleCollisions(platforms, n);
		}

		delete[] platforms;
	}

	void HandleCollisions(Object** platforms, int count) {
		Object* platform = *WorldClass.w_objects.begin();
		char side;	//Side of colision
		
		for (int i = 1; i < count; i++) {
			if (side = platform->IsCollided(platforms[i], { PLATFORM_DIST_X, PLATFORM_DIST_Y })) {
				WorldClass.w_objects.pop_front();			//First remove created platform from world
				delete platform;							//Delete this platform

				platforms[count] = CreateNearPlatform(platforms[i], side);		//Create new platform that doesn't collide
				
				break;
			}
		}

	}

	Object* CreateNearPlatform(Object* platform, char side) {
		Vector pos;
		
		//Calculate the new position
		switch (side) {
		case COLLISION_LB:
			pos.x = platform->GetPosition().x - PLATFORM_DIST_X - PLATFORM_WIDTH;
			pos.y = platform->GetPosition().y - PLATFORM_DIST_Y - PLATFORM_HEIGHT;
		case COLLISION_LT:
			pos.x = platform->GetPosition().x - PLATFORM_DIST_X - PLATFORM_WIDTH;
			pos.y = platform->GetPosition().y + PLATFORM_DIST_Y + PLATFORM_HEIGHT;
		case COLLISION_RB:
			pos.x = platform->GetPosition().x + PLATFORM_DIST_X + PLATFORM_WIDTH;
			pos.y = platform->GetPosition().y - PLATFORM_DIST_Y - PLATFORM_HEIGHT;
		case COLLISION_RT:
			pos.x = platform->GetPosition().x + PLATFORM_DIST_X + PLATFORM_WIDTH;
			pos.y = platform->GetPosition().y + PLATFORM_DIST_Y + PLATFORM_HEIGHT;
		}

		//Spawn platform
		return SpawnPlatform(pos);
	}

	void Update(float timeDelta) {
		//Check the state of the world
		if (WorldClass.w_state == SHOP_STATE) {
			//Draw the world
			DrawWorld();
			
			//Update and draw upgrade list
			PlayerSp::UpdateUpgradeList();

			//Check if the state is changed
			if (::GetAsyncKeyState('J') & 0x8000f) 
				WorldClass.w_state = WORLD_STATE;
		}
		else {
			UpdateWorld(timeDelta);

			//Check if the state is changed
			if (::GetAsyncKeyState('H') & 0x8000f)
				WorldClass.w_state = SHOP_STATE;
		}
	}

	void UpdateWorld(float timeDelta) {
		auto object = WorldClass.w_objects.begin();
		auto movObject = WorldClass.w_movObjects.begin();

		//
		//Spawn new platforms
		//
		if (WorldClass.w_objects.front()->GetPosition().y < PlayerGetPos().y + PLAYER_EDGE_DIST) {
			GeneratePlatforms();
		}

		//
		//Update static objects
		//
		while (object != WorldClass.w_objects.end()) {
			//Update every object
			if ((*object)->IsAlive()) {
				(*object)->Update(timeDelta);
				object++;
			}
			else {
				//Remove non active objects
				auto temp = object;
				if (object == WorldClass.w_objects.end())
					object--;
				else
					object++;
				delete* temp;
				WorldClass.w_objects.remove(*temp);
			}
		}

		//
		//Update mobile objects
		//
		while (movObject != WorldClass.w_movObjects.end()) {
			//Update every object
			if ((*movObject)->IsAlive()) {
				(*movObject)->Update(timeDelta);
				movObject++;
			}
			else {
				//Remove non active objects
				auto temp = movObject;
				if (movObject == WorldClass.w_movObjects.end())
					movObject--;
				else
					movObject++;
				delete* temp;
				WorldClass.w_movObjects.remove(*temp);
			}
		}

		PlayerUpdate(timeDelta);

		//Remove old platforms(that are above player)
		RemoveLowerPlatforms();

		//Draw world
		DrawWorld();
	}

	void RemoveLowerPlatforms() {
		Object* platform = WorldClass.w_objects.back();


		while (platform->GetPosition().y < (Player()->GetPosition().y - PLAYER_EDGE_DIST)) {
			WorldClass.w_objects.pop_back();
			delete platform;

			platform = WorldClass.w_objects.back();
		}
	}

	void DrawWorld() {
		//First draw background
		WorldClass.w_back->Draw();
		//Draw static objects
		for (auto object = WorldClass.w_objects.begin(); object != WorldClass.w_objects.end(); object++) {
			//Draw every object
			(*object)->Draw();
		}
		//Draw mobile objects
		for (auto movObject = WorldClass.w_movObjects.begin(); movObject != WorldClass.w_movObjects.end(); movObject++) {
			//Draw every object
			(*movObject)->Draw();
		}

		PlayerDraw();
	}

	void ClearWorld() {
		//Clear all objects
		for(auto object = WorldClass.w_objects.begin(); object != WorldClass.w_objects.end(); object++){
			delete* object;
		}

		WorldClass.w_objects.clear();

		//Release textures
		delete pltfm_default_texture;
		delete pltfm_sliding_texture;
		delete pltfm_dummy_texture;
		delete pltfm_jump_texture;

		//Release player
		PlayerRelease();
		
		//Delete background
		delete WorldClass.w_back;
	}
	
}