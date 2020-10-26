#pragma once

#include "render/render.h"
#include "components/objects/world.h"
#include "config/vSync.h"

class Game {
	Render* _rend = nullptr;
public:
	Game() {}

	void Init(Window* wnd);

	void Run(float timeDelta);

	void Release();
	~Game();
};