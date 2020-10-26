#pragma once

#include "../window.h"
#include "shaders/vertexShader.h"
#include "shaders/pixelShader.h"
#include "../components/objects/movObject.h"
#include "../components/objects/world.h"
#include "../components/background/background.h"
#include "../gui/menus/debugMenus.h"
#include "camera/camera.h"
#include "../input/input.h"
#include "../gui/gui.h"
#include <queue>

class Render {
	IDirect3DDevice9* _device;
	Window* _wnd;
	VertexShader* _vShader = nullptr;	//Vertex shader
	PixelShader* _pShader = nullptr;	//PixelShader
	Camera* _cam = nullptr;				//Camera object

	
public:
	Render(Window* wind);

	void SetCamPos(float x, float y);	//Set camera position
	void SetCamDist(float dist);		//Set camera distantion

	void CameraUpdate();				//Update camera datas
	void CameraFollow(Object* object);		//Set camera to follow
	float GetCamX() { return _cam->GetX(); }						//Get camera X position
	float GetCamY() { return _cam->GetY(); }						//Get camera X position

	void RenderWorld(float timeDelta);

	IDirect3DDevice9* GetDevice() { return _device; }	//Get render device

	void Release();

	~Render();
};

void RenderPush(Sprite* sprite);						//Push the sprite to render queue
void BackgroundPush(Background_Sprite* background);		//Push the background to queue