//
//File: background.h
//
//Desc: Background is a sprite. It is drawed on the screen space. We change just UV coord of texture.
//

#pragma once

#include "../objects/movObject.h"
#include "../../render/shaders/vertexShader.h"
#include "../../render/camera/camera.h"

		//Background sprite
class Background_Sprite : public Sprite {
public:
	Background_Sprite(IDirect3DDevice9* device, float x1, float y1, float x2, float y2, Texture* texture);

	void SetFollow(MobileObject* obj);					//Set follwed object
	void UpdateUV(Camera* cam);			//Update UV

	void Draw();					//Send to background 
	void DrawImpl(IDirect3DDevice9* device, VertexShader* vShader, PixelShader* pShader, Camera* cam);	//Draw implimentation

	~Background_Sprite() {}
private:
	MobileObject* follow_obj = nullptr;	//Followed object
};

class Background {
	Background_Sprite* bkg_sprite;		//Background sprite
	Texture* bkg_texture;	//Background texture

public:
	Background(const char* src, IDirect3DDevice9* device);		//Create background

	void SetFollow(MobileObject* obj);	//Set followed object

	void Draw();		//Draw background

	void Release();		//Release background

	~Background() { Release(); }		//Delete background
};