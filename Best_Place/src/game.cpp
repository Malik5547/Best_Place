#include "game.h"


void Game::Init(Window* wnd) {
	_rend = new Render(wnd);

	//Set vSync
	VSync::SetMaxFPS(60);

	//Test world
	World::InitWorld(_rend->GetDevice());

	//Set camera to follow the player
	_rend->CameraFollow(World::Player());
}

void Game::Run(float timeDelta) {
	//Check vSync
	if (VSync::Passed(timeDelta)) {
		//Apply vSync
		timeDelta = VSync::GetPassedTime();

		//Update world
		World::Update(timeDelta);

		//
		//Input test
		//
		if (IS_PRESSED(Input::RIGHT)) {
			//SetCamPos(_cam->GetX() - 0.001f, _cam->GetY());
			World::Player()->Move({ 1.0f, 0.0f });
		}
		if (IS_PRESSED(Input::LEFT)) {
			//SetCamPos(_cam->GetX() + 0.001f, _cam->GetY());
			World::Player()->Move({ -1.0f, 0.0f });
		}
		if (IS_PRESSED(Input::UP)) {
			//SetCamPos(_cam->GetX(), _cam->GetY() - 0.001f);
			World::Player()->Move({ 0.0f, 1.0f });
		}
		if (IS_PRESSED(Input::DOWN)) {
			//SetCamPos(_cam->GetX(), _cam->GetY() + 0.001f);
			World::Player()->Move({ 0.0f, -1.0f });
		}
		if (::GetAsyncKeyState(' ') & 0x8000f) {
			World::Player()->Jump();
		}
		if (::GetAsyncKeyState('O') & 0x8000f) {
			World::Player()->SetBoots(true);
		}
		if (::GetAsyncKeyState('P') & 0x8000f) {
			World::Player()->SetBoots(false);
		}


		World::Player()->Update(timeDelta);

		//Update FPS
		FPSTimer::Update(timeDelta);
		
		if (_rend)
			_rend->RenderWorld(timeDelta);
	}
}

void Game::Release() {
	if (_rend){
		_rend->Release();
		_rend = nullptr;
	//Release world
		World::ClearWorld();
	}
}

Game::~Game() {
	Release();
}